#include "../include/escalonador.hpp"
    
    Escalonador::Escalonador(std::deque<Processo*>&processos) : tempo_atual(0), processo_execucao(nullptr) {
        processos_todos = processos;
    };
    Escalonador::~Escalonador(){

    };
    void Escalonador::chegada(){
        auto t = processos_todos.begin();
        while ((t) != processos_todos.end()) {
            if ((*t)->tempo_chegada == tempo_atual) {
                processos_prontos.push_back(*(t));
                t = processos_todos.erase(t);
            } else {
                t++;
            }
        }
    }
    void Escalonador::aging(){
        for (auto p : processos_prontos){
            p->ciclos_espera++;
            if (p->ciclos_espera >= tempo_atual) {
                p->prioridade++; // incrementa a prioridade caso tenha atingido a cota de ciclos
                p->ciclos_espera = 0; //reseta
            }
        }
    }

    void Escalonador::bloqueado(){
        auto p = processos_bloqueados.begin();
        while (p != processos_bloqueados.end()) {
            p->second--; //decrementa o tempo de bloqueio do primeiro processo da lista
            if (p->second == 0){
                processos_prontos.push_back(p->first); // adiciona o processo bloqueado a fila de processos prontos
                p = processos_bloqueados.erase(p); // .erase apaga o elemento apontado por it e faz it apontar pro proximo da lista
            } else {
                p++;
            }
        }
    }
    void Escalonador::escalonar() 
    {   
        if (processos_prontos.empty()){
            return;
        }
        std::sort(processos_prontos.begin(), processos_prontos.end(),
            [](const Processo& p1, Processo& p2){
                if(p1.prioridade != p2.prioridade) {
                    return p1.prioridade > p2.prioridade;
                }
                return p1.tempo_chegada < p2.tempo_chegada;
            }
        );
        Processo* proximo = processos_prontos.front();
        if (processo_execucao != proximo) {
            if (processo_execucao != nullptr){
                processos_prontos.push_back(processo_execucao);
            }
            processo_execucao = proximo;
            processos_prontos.erase(processos_prontos.begin());
        }

    }
    void Escalonador::execucao()
    {
        if (processo_execucao == nullptr){
            return;
        }
        processo_execucao->tempo_exec--;
        processo_execucao->tempo_restante--;

        // if (processo_execucao->perfil == MEMORY_BOUND) {
        //     int* memoria = (int*)malloc(sizeof(int)*100);
        //     for (int i = 0; i<100; i++){
        //         memoria[i] = i;
        //     }
        //     free(memoria);
        // }
        if (processo_execucao->tempo_restante == 0){
            delete processo_execucao;
            processo_execucao = nullptr;
        } else if (processo_execucao->tempo_exec <= 0) {
            if (processo_execucao->perfil == IO_BOUND){
                std::cout<<"Processo "<<processo_execucao->id<<" bloqueado por I/O"<<std::endl;
            }
            processos_bloqueados.push_back({processo_execucao, processo_execucao->tempo_block});
            processo_execucao = nullptr;
        }


    }
    void Escalonador::simulacao(){
        while (!processos_todos.empty() || !processos_prontos.empty() || !processos_bloqueados.empty() || processo_execucao != nullptr) {
            chegada();
            aging();
            bloqueado();
            escalonar();
            execucao();

            tempo_atual--;
        } 
    }
    

