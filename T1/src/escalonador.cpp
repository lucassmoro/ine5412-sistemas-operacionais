#include "processo.cpp"

class Escalonador
{
private:
    
public:
    Escalonador(/* args */);
    ~Escalonador();
    void escalonar(std::vector<Processo>& processos)
    {
        std::queue<Processo> processos_execucao;
        escalonar_prioridade(processos);
        std::cout<<"Executando Processo:"<<processos.begin()->prioridade;
        processos_execucao.push(*processos.begin());
        processos.pop_back();
    }
    void escalonar_prioridade(std::vector<Processo>& processos)
    {
        std::sort(processos.begin(), processos.end(),
            [](const Processo& p1, Processo& p2){
                return p1.prioridade > p2.prioridade;
            }
        );
    }
};


