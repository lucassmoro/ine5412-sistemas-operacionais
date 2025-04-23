 #include "../include/escalonador.hpp"

int main() {
    std::deque<Processo*> processos = {
        new Processo(1, 5, CPU_BOUND, 2, 0),   // CPU-bound, prioridade 2, chega em t=0
        new Processo(2, 6, IO_BOUND, 1, 0),     // I/O-bound, prioridade 1, chega em t=2
        new Processo(3, 4, MEMORY_BOUND, 3, 2), // Memory-bound, prioridade 3, chega em t=4
        new Processo(4, 2, CPU_BOUND, 1, 5),   
        new Processo(5, 3, IO_BOUND, 3, 9),
        new Processo(6, 3, MEMORY_BOUND, 2, 14)
    };

    Escalonador escalonador(processos);
    escalonador.simulacao();

    return 0;
}