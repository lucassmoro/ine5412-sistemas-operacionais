#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include <vector>
#include <queue>
#include "processo.hpp"
enum Profile { CPU_BOUND, IO_BOUND, MEMORY_BOUND };

class Escalonador {
private:
    Processo* processo_execucao;
    int tempo_atual;
    int const aging_intervalo = 3;
    std::deque<Processo*> processos_todos;
    std::deque<Processo*> processos_prontos;
    std::list<std::pair<Processo*, int>> processos_bloqueados;
public:
    Escalonador(std::deque<Processo*>& processos);
    ~Escalonador();
    void chegada();
    void aging();
    void bloqueado();
    void execucao();
    void simulacao();
    void escalonar();
    void escalonar_prioridade(std::deque<Processo>& processos);
    void execucao_processo(std::deque<Processo>& processos);
};

#endif
