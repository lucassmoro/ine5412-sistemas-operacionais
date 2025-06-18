#include "page_replacement.h"

std::vector<bool> Page_Replacement::frame_table;           // Tabela de frames livres/ocupados
std::vector<int> Page_Replacement::frame_to_page;          // Mapeia frame para página
std::queue<int> Page_Replacement::fifo_queue;              // Fila FIFO para substituição
std::string Page_Replacement::current_algorithm;           // Algoritmo atual
Disk* Page_Replacement::disk_ptr = nullptr;                // Ponteiro para o disco
bool Page_Replacement::initialized = false;                // Flag de inicialização
int Page_Replacement::page_faults = 0;
int Page_Replacement::disk_reads = 0;
int Page_Replacement::disk_writes = 0;


//custom algorithm
bool Page_Replacement::eh_fifo = 1;
deque<int> Page_Replacement::custom_deque;

// Função para inicializar estruturas de dados
void Page_Replacement::initialize_data_structures(Page_Table *pt, const std::string& algorithm) {
    if (initialized) return;
    
    int nframes = pt->page_table_get_nframes();
    frame_table.resize(nframes, false);
    frame_to_page.resize(nframes, -1);
    current_algorithm = algorithm;
    
    // Criar disco virtual
    disk_ptr = new Disk("virtual_disk.dat", pt->page_table_get_npages());
    
    initialized = true;
}

// Função para encontrar um frame livre
int Page_Replacement::find_free_frame() {
    for (size_t i = 0; i < frame_table.size(); i++) {
        if (!frame_table[i]) {
            return i;
        }
    }
    return -1; // Nenhum frame livre
}

// Algoritmo de substituição Random
int Page_Replacement::random_replacement(int nframes) {
    return rand() % nframes; 
}

// Algoritmo de substituição FIFO
int Page_Replacement::fifo_replacement() {
    if (fifo_queue.empty()) {
        // Se a fila está vazia, retorna o primeiro frame
        return 0;
    }
    int frame = fifo_queue.front();
    fifo_queue.pop();
    return frame;
}

// Algoritmo de substituição Custom (LRU - Least Recently Used)
int Page_Replacement::custom_replacement() {
    // Encontra o frame com menor contador (menos recentemente usado)
    if(eh_fifo){
        if (custom_deque.empty()) {
            // Se a fila está vazia, retorna o primeiro frame
            return 0;
        }
        int frame = custom_deque.front();
        custom_deque.pop_front();
        eh_fifo=!eh_fifo;
        return frame;
    }
    else{
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

// Função para escolher frame para substituição
int Page_Replacement::choose_frame_for_replacement(int nframes) {
    if (current_algorithm == "rand") {
        return random_replacement(nframes); 
    } else if (current_algorithm == "fifo") {
        return fifo_replacement();
    } else if (current_algorithm == "custom") {
        return custom_replacement();
    }
    return 0; // Fallback
}

// Função para carregar página do disco
void Page_Replacement::load_page_from_disk(int page, int frame) {
    char* physmem = (char*) Page_Table::the_page_table->page_table_get_physmem();
    disk_ptr->read(page, physmem + frame * Page_Table::PAGE_SIZE);
    disk_reads++;
}

// Função para salvar página no disco
void Page_Replacement::save_page_to_disk(int page, int frame) {
    char* physmem = (char*)Page_Table::the_page_table->page_table_get_physmem();
    disk_ptr->write(page, physmem + frame * Page_Table::PAGE_SIZE);
    disk_writes++;
}

// Função principal de tratamento de page fault
void Page_Replacement::page_fault_handler(Page_Table *pt, int page) {
    // Inicializa estruturas se necessário    
    
    if (!initialized) {
        // Precisa determinar o algoritmo - por ora, usa "rand" como padrão
        initialize_data_structures(pt, current_algorithm);
    }

    page_faults++;
    
    int frame, bits;
    pt->page_table_get_entry(page, &frame, &bits);
    
    // Caso 1: Página não tem permissões (primeira vez acessada)
    if (bits == 0) {
        // Procura um frame livre
        int free_frame = find_free_frame();
        
        if (free_frame != -1) {
            // Há frame livre disponível
            frame_table[free_frame] = true;
            frame_to_page[free_frame] = page;
            
            // Carrega página do disco
            load_page_from_disk(page, free_frame);
            
            // Atualiza tabela de páginas
            pt->page_table_set_entry(page, free_frame, PROT_READ);
            
            // Atualiza estruturas dos algoritmos
            if (current_algorithm == "fifo") {
                fifo_queue.push(free_frame);
            } else if (current_algorithm == "custom") {
                //dps fazer fifo lifo alternado
                custom_deque.push_front(free_frame);
            }
        } else {
            // Não há frame livre - precisa substituir
            int victim_frame = choose_frame_for_replacement(pt->page_table_get_nframes());
            int victim_page = frame_to_page[victim_frame];

            // Verifica se a página vítima foi modificada
            int victim_frame_temp, victim_bits;
            pt->page_table_get_entry(victim_page, &victim_frame_temp, &victim_bits);
            
            if (victim_bits & PROT_WRITE) {
                //se o bit de escrita = 1, a pagina vitima foi modificada e deve ser escrita no disco
                save_page_to_disk(victim_page, victim_frame);
            }

            // Remove mapeamento da página vítima
            //pt->page_table_set_entry(victim_page, -1, 0); // SERÁ?
                        
            // Carrega nova página
            load_page_from_disk(page, victim_frame);
            frame_to_page[victim_frame] = page;
            
            // Atualiza tabela de páginas
            pt->page_table_set_entry(page, victim_frame, PROT_READ);
            pt->page_table_set_entry(victim_page, victim_frame, 0);
            // Atualiza estruturas dos algoritmos
            if (current_algorithm == "fifo") {
                fifo_queue.push(victim_frame);
            } else if (current_algorithm == "custom") {
                custom_deque.push_front(victim_frame);//DPS MUDAR
            }
        }
    }
    // Caso 2: Página tem PROT_READ, mas precisa de PROT_WRITE
    else if ((bits & PROT_READ) && !(bits & PROT_WRITE)) {
        // Adiciona permissão de escrita
        pt->page_table_set_entry(page, frame, PROT_READ | PROT_WRITE);
        
    }
}

// Função para configurar o algoritmo
void Page_Replacement::set_algorithm(const std::string& algorithm) {
    current_algorithm = algorithm;
}

// Função para obter estatísticas
void Page_Replacement::print_statistics() {
    std::cout << "Page faults: " << page_faults << std::endl;
    std::cout << "Disk reads: " << disk_reads << std::endl;
    std::cout << "Disk writes: " << disk_writes << std::endl;
}

// Função para resetar estatísticas
void Page_Replacement::reset_statistics() {
    page_faults = 0;
    disk_reads = 0;
    disk_writes = 0;
}

// Função para limpeza
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