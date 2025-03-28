#include "../include/escalonador.hpp"

    //Escalonador();
    //~Escalonador();
    void escalonar(std::vector<Processo>& processos)
    {
        escalonar_prioridade(processos);
        std::queue<Processo> processos_execucao;
        std::cout<<"Executando Processo:"<<processos.front().prioridade;
        while (!processos.empty()) {
            processos_execucao.push(processos.front());
            processos.erase(processos.begin()); 
        }
    }
    void escalonar_prioridade(std::vector<Processo>& processos)
    {
        std::sort(processos.begin(), processos.end(),
            [](const Processo& p1, Processo& p2){
                return p1.prioridade > p2.prioridade;
            }
        );
    }



