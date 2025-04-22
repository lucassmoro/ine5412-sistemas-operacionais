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
            std::cout<<"Fila de execucao: Processo em execucao: "<<processo_execucao.id<<std::endl;
            execucao_processo(processos);
        }
    }
    void Escalonador::escalonar_prioridade(std::deque<Processo>& processos) //escalonamento por prioridade
    {
        std::sort(processos.begin(), processos.end(),
            [](const Processo& p1, Processo& p2){
                return p1.prioridade > p2.prioridade;
            }
        );
    }

    void Escalonador::execucao_processo(std::deque<Processo>& processos)
    {
        int ciclos_executados = 0;
        while (processo_execucao.tempo_estimado > 0) {
            std::cout<<"processo execucao tempo estimado "<<processo_execucao.tempo_estimado<<std::endl;
            sleep(1);
            processo_execucao.tempo_estimado--;
            ciclos_executados++;

            // I/O-Bound
            if (processo_execucao.perfil == "IO-Bound" && ciclos_executados == 2) {
                std::cout << "Processo " << processo_execucao.id << " bloqueado por I/O\n";
                ciclos_executados = 0;
                processos.push_back(processo_execucao);
                return;
            }

            for (size_t i = 0; i < processos.size(); i++){
                if (processos[i].prioridade > processo_execucao.prioridade){
                    processos.push_back(processo_execucao);
                    escalonar_prioridade(processos);
                    processo_execucao = processos[0];
                    return;
                };
            }
        }
    }



