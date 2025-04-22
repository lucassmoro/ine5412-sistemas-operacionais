#include "../include/escalonador.hpp"

int main(){

    std::deque<Processo> processos;
    Processo processo1 {1,5,"CPU-Bound",6};
    Processo processo2 {2,2,"CPU-Bound",3};
    Processo processo3 {3,7,"CPU-Bound",7};
    processos.push_back(processo1);
    processos.push_back(processo2);
    processos.push_back(processo3);
    Escalonador escalonador;
    Processo processo4 {5,3,"Memory-Bound",9};
    escalonador.escalonar(processos);
    // for (const auto& p : processos) {
    //     std::cout<<p.id<<std::endl;
    // }
    //processo1.processo_info();

}