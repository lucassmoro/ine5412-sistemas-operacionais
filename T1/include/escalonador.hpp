#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include <vector>
#include <queue>
#include "../src/processo.cpp"  

class Escalonador {
public:
    Escalonador();
    ~Escalonador();
    void escalonar(std::vector<Processo>& processos);
    void escalonar_prioridade(std::vector<Processo>& processos);
};

#endif
