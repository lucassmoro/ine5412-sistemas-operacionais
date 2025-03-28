#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include <vector>
#include <queue>
#include "processo.hpp"

class Escalonador {
private:
    Processo processo_execucao;
public:
    Escalonador();
    ~Escalonador();
    void escalonar(std::deque<Processo>& processos);
    void escalonar_prioridade(std::deque<Processo>& processos);
    void execucao_processo(std::deque<Processo>& processos);
};

#endif
