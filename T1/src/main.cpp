#include "../include/escalonador.hpp"

int main(){

    std::vector<Processo> processos;
    Processo processo1 {1,5,"CPU-Bound",6};
    Processo processo2 {2,5,"CPU-Bound",3};
    Processo processo3 {3,5,"CPU-Bound",7};
    processos.push_back(processo1);
    processos.push_back(processo2);
    processos.push_back(processo3);
    Escalonador escalonador;
    escalonador.escalonar(processos);
    for (const auto& p : processos) {
        std::cout<<p.id<<std::endl;
    }
    //processo1.processo_info();

}