#include "../include/processo.hpp"


Processo::Processo(int id, int est, Profile p, int prio, int t_chegada) :
                id(id), tempo_estimado(est), perfil(p), prioridade(prio),
                tempo_chegada(t_chegada), tempo_exec(0), tempo_block(0), tempo_restante(est) {}
void Processo::reset_burst() {
        switch (perfil) {
            case CPU_BOUND:
                tempo_exec = tempo_estimado; // Burst único
                tempo_block = 0;
                break;
            case IO_BOUND:
                tempo_exec = 2; // Burst curto
                tempo_block = 3;  // Bloqueio longo
                break;
            case MEMORY_BOUND:
                tempo_exec = tempo_estimado; // Burst moderado
                tempo_block = 2;  // Bloqueio curto
                break;
        }
    }

void Processo::processo_info()const
{
    std::cout<<"ID: "<<id<<std::endl
        <<"Tempo estimado de execucao: "<<tempo_estimado<<std::endl
        <<"Perfil: "<<perfil<<std::endl<<"Prioridade: "
        <<prioridade<<std::endl;
}