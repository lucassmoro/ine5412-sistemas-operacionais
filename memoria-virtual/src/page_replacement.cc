#include "page_replacement.h"

std::vector<bool> Page_Replacement::frame_table;           // tabela de frames livres/ocupados
std::vector<int> Page_Replacement::frame_to_page;          // mapeia frame para página
std::queue<int> Page_Replacement::fifo_queue;              // fila FIFO para substituição
std::string Page_Replacement::current_algorithm;           // algoritmo atual
Disk* Page_Replacement::disk_ptr = nullptr;                // ponteiro para o disco
bool Page_Replacement::initialized = false;                // flag de inicialização
int Page_Replacement::page_faults = 0;
int Page_Replacement::disk_reads = 0;
int Page_Replacement::disk_writes = 0;


//custom algorithm
bool Page_Replacement::eh_fifo = 1;
deque<int> Page_Replacement::custom_deque;

// funcao para inicializar estruturas de dados
void Page_Replacement::initialize_data_structures(Page_Table *pt) {
    if (initialized) return;
    
    int nframes = pt->page_table_get_nframes(); //recebe a qtd de frames
    frame_table.resize(nframes, false); // expande para o tamanho nframes e seta todos para falso
    frame_to_page.resize(nframes, -1); // expande para o tamanho nframes e seta todos para -1 (nenhuma pagina associada)
    
    disk_ptr = new Disk("virtual_disk.dat", pt->page_table_get_npages()); // cria o disco virtual
    
    initialized = true; // seta o booleano pra true, agora as estruturas de dados nao serão mais inicializadas
}

// funcao para encontrar um frame livre
int Page_Replacement::find_free_frame() {
    for (size_t i = 0; i < frame_table.size(); i++) { //faz uma busca linear de 0 a nframes ate achar o frame livre
        if (!frame_table[i]) { 
            return i; 
        }
    }
    return -1; // nenhum frame livre
}

// algoritmo de substituição Random
int Page_Replacement::random_replacement(int nframes) {
    return rand() % nframes; // escolhe aleatoriamente um frame entre 0 e nframes - 1
}

// algoritmo de substituição FIFO
int Page_Replacement::fifo_replacement() {
    if (fifo_queue.empty()) {
        // se a fila está vazia, retorna o primeiro frame
        return 0;
    }
    int frame = fifo_queue.front(); // senao retorna o primeiro da fila
    fifo_queue.pop(); 
    return frame;
}

// algoritmo LIFO-FIFO (custom)
int Page_Replacement::custom_replacement() {
    // Encontra o frame com menor contador (menos recentemente usado)
    if(eh_fifo){ // se o comportamento do algoritmo agora é de FIFO, entao substitui a pagina primeira da fila
        if (custom_deque.empty()) {
            // Se a fila está vazia, retorna o primeiro frame
            return 0;
        }
        int frame = custom_deque.front();
        custom_deque.pop_front();
        eh_fifo=!eh_fifo;
        return frame;
    }
    else{ // se o comportamento for de LIFO, substitui a pagina atras da fila
        if (custom_deque.empty()) {
            // Se a fila está vazia, retorna o primeiro frame
            return 0;
        }
        int frame = custom_deque.back();
        custom_deque.pop_back();
        eh_fifo=!eh_fifo; 
        return frame;
    }
}

// funcao para escolher frame para substituição
int Page_Replacement::choose_frame_for_replacement(int nframes) {
    if (current_algorithm == "rand") {
        return random_replacement(nframes); //nframes é passado como argumento para poder calcular o numero randomico baseado na quantidade de frames
    } else if (current_algorithm == "fifo") { // escolhe o algoritmo FIFO 
        return fifo_replacement();
    } else if (current_algorithm == "custom") { // escolhe o algoritmo custom
        return custom_replacement();
    }
    return 0; // Fallback
}

// funcao para carregar página do disco
void Page_Replacement::load_page_from_disk(int page, int frame) {
    // ponteiro da base da mem fisica, recebe do ponteiro estatico (the_page_table) que acessa um getter
    char* physmem = (char*) Page_Table::the_page_table->page_table_get_physmem(); 
    disk_ptr->read(page, physmem + frame * Page_Table::PAGE_SIZE); // le o disco passando no argumento o endereço base somado com o frame * o tamanho do frame
    disk_reads++; // incrementa a estatistica
}

// funcao para salvar página no disco
void Page_Replacement::save_page_to_disk(int page, int frame) {
    char* physmem = (char*)Page_Table::the_page_table->page_table_get_physmem(); //ponteiro pro endereco base da memoria fisica
    disk_ptr->write(page, physmem + frame * Page_Table::PAGE_SIZE); // escreve no disco passando como argumento o enderço base + frame * o  tamanho do frame
    disk_writes++; // incrementa a estatistica
}

// funcao principal de tratamento de page fault
void Page_Replacement::page_fault_handler(Page_Table *pt, int page) {
    // inicializa estruturas se necessário    
    
    if (!initialized) {
        initialize_data_structures(pt);
    }

    page_faults++;
    
    int frame, bits;
    pt->page_table_get_entry(page, &frame, &bits);
    
    // caso 1: Pagina não tem permissões (primeira vez acessada)
    if (bits == 0) {
        // procura um frame livre
        int free_frame = find_free_frame();
        
        if (free_frame != -1) {
            // há frame livre disponível
            frame_table[free_frame] = true;
            frame_to_page[free_frame] = page;
            
            // carrega pagina do disco
            load_page_from_disk(page, free_frame);
            
            // atualiza tabela de páginas
            pt->page_table_set_entry(page, free_frame, PROT_READ);
            
            // atualiza estruturas dos algoritmos
            if (current_algorithm == "fifo") {
                fifo_queue.push(free_frame);
            } else if (current_algorithm == "custom") {
                custom_deque.push_back(free_frame);
            }
        } else {
            // nao há frame livre, precisa substituir
            int victim_frame = choose_frame_for_replacement(pt->page_table_get_nframes()); //
            int victim_page = frame_to_page[victim_frame];

            // Verifica se a página vítima foi modificada
            int victim_frame_temp, victim_bits;
            pt->page_table_get_entry(victim_page, &victim_frame_temp, &victim_bits);
            
            if (victim_bits & PROT_WRITE) {
                //se o bit de escrita = 1, a pagina vitima foi modificada e deve ser escrita no disco
                save_page_to_disk(victim_page, victim_frame);
            } 
            // Carrega nova página
            load_page_from_disk(page, victim_frame);
            frame_to_page[victim_frame] = page;
            
            // Atualiza tabela de paginas
            pt->page_table_set_entry(page, victim_frame, PROT_READ);
            pt->page_table_set_entry(victim_page, victim_frame, 0);
            // atualiza estruturas dos algoritmos
            if (current_algorithm == "fifo") {
                fifo_queue.push(victim_frame);
            } else if (current_algorithm == "custom") {
                custom_deque.push_back(victim_frame);
            }
        }
    }
    // caso 2: Pagina tem PROT_READ, mas precisa de PROT_WRITE
    else if ((bits & PROT_READ) && !(bits & PROT_WRITE)) {
        // adiciona permissão de escrita
        pt->page_table_set_entry(page, frame, PROT_READ | PROT_WRITE);
        
    }
}

// funcao para configurar o algoritmo
void Page_Replacement::set_algorithm(const std::string& algorithm) {
    current_algorithm = algorithm; // seta o algoritmo a ser usado
}

// funcao para obter estatísticas
void Page_Replacement::print_statistics() {
    std::cout << "Page faults: " << page_faults << std::endl;
    std::cout << "Disk reads: " << disk_reads << std::endl;
    std::cout << "Disk writes: " << disk_writes << std::endl;
}

// funcao para resetar estatísticas
void Page_Replacement::reset_statistics() {
    page_faults = 0;
    disk_reads = 0;
    disk_writes = 0;
}

// funcao para limpeza
void Page_Replacement::cleanup() {
    if (disk_ptr) {
        disk_ptr->close_disk();
        delete disk_ptr;
        disk_ptr = nullptr;
    }
    
    frame_table.clear();
    frame_to_page.clear();
    while (!fifo_queue.empty()) fifo_queue.pop();
    while (!custom_deque.empty()) custom_deque.pop_back(); // CUSTOM
    
    initialized = false;
}