#ifndef PROCESSO_HPP
#define PROCESSO_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
#include <unistd.h>
#include <list>
#include <utility>
#include <set>
enum Profile { CPU_BOUND, IO_BOUND, MEMORY_BOUND };

struct Processo {
    int id;
    int tempo_estimado;
    Profile perfil;
    int prioridade;
    int tempo_chegada;
    int ciclos_espera;
    int tempo_exec;
    int tempo_block;
    int tempo_restante;
    
    Processo() : id(0), tempo_estimado(0), perfil(), prioridade(0) {}
    Processo(int id, int tempo_estimado, Profile p, int prioridade, int t_chegada);
    void reset_burst();
    void processo_info() const;
};

#endif 
