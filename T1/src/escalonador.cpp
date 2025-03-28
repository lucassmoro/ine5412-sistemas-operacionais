#include "../include/escalonador.hpp"

    Escalonador::Escalonador(){

    };
    Escalonador::~Escalonador(){

    };
    void Escalonador::escalonar(std::vector<Processo>& processos)
    {   std::cout<<"Processo antes do escalonamento: "<<processos.front().id<<std::endl;
        escalonar_prioridade(processos);
        std::queue<Processo> processos_fila;
        std::cout<<"Processo depois do escalonamento: "<<processos.front().id<<std::endl;
        while (!processos.empty()) {
            processos_fila.push(processos.front());
            processos.erase(processos.begin()); 
        }
        std::cout<<"Fila de execucao: Processo em execucao:"<<processos_fila.front().id<<std::endl;
    }
    void Escalonador::escalonar_prioridade(std::vector<Processo>& processos)
    {
        std::sort(processos.begin(), processos.end(),
            [](const Processo& p1, Processo& p2){
                return p1.prioridade > p2.prioridade;
            }
        );
    }



