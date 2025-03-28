#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include <vector>
#include <queue>
#include "processo.hpp"  

class Escalonador {
public:
    Escalonador();
    ~Escalonador();
    void escalonar(std::vector<Processo>& processos);
    void escalonar_prioridade(std::vector<Processo>& processos);
};

#endif
