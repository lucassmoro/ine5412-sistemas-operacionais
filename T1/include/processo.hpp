#ifndef PROCESSO_HPP
#define PROCESSO_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
#include <unistd.h>

struct Processo {
    int id;
    int tempo_estimado;
    std::string perfil;
    int prioridade;

    Processo(int id, int tempo_estimado, std::string perfil, int prioridade);
    void processo_info() const;
};

#endif 
