#include <iostream>
#include <queue>
#include <unistd.h>

struct Processo
{
    int id;
    int tempo_estimado;
    std::string perfil;
    int prioridade;

    Processo(int id, int tempo_estimado, std::string perfil,
        int prioridade):
        id(id), tempo_estimado(tempo_estimado), perfil(perfil),
        prioridade(prioridade){}


    void processo_info()
    {
        std::cout<<"ID: "<<id<<std::endl
        <<"Tempo estimado de execucao: "<<tempo_estimado<<std::endl
        <<"Perfil: "<<perfil<<std::endl<<"Prioridade: "
        <<prioridade<<std::endl;
    }
};