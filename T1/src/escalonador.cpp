#include "../include/escalonador.hpp"

    Escalonador::Escalonador(){

    };
    Escalonador::~Escalonador(){

    };
    void Escalonador::escalonar(std::deque<Processo>& processos)
    {   
        std::cout<<"Processo antes do escalonamento: "<<processos.front().id<<std::endl;
        escalonar_prioridade(processos);
        std::cout<<"Processo depois do escalonamento: "<<processos.front().id<<std::endl;
        std::cout<<"Primeiro processo da fila: "<<processos.front().id<<std::endl;
        while (!processos.empty()){
            processo_execucao = processos.front();
            processos.pop_front();
            execucao_processo(processos);
            std::cout<<"Fila de execucao: Processo em execucao: "<<processo_execucao.id<<std::endl;
        }
    }
    void Escalonador::escalonar_prioridade(std::deque<Processo>& processos)
    {
        std::sort(processos.begin(), processos.end(),
            [](const Processo& p1, Processo& p2){
                return p1.prioridade > p2.prioridade;
            }
        );
    }
    void Escalonador::execucao_processo(std::deque<Processo>& processos)
    {
        while (processo_execucao.tempo_estimado > 0) {
            std::cout<<"processo execucao tempo estimado "<<processo_execucao.tempo_estimado<<std::endl;
            sleep(1);
            processo_execucao.tempo_estimado--;
            for (size_t i = 0; i < processos.size(); i++){
                if (processos[i].prioridade > processo_execucao.prioridade){
                    escalonar_prioridade(processos);
                    processo_execucao = processos[0];
                };
            }
        }
    }



