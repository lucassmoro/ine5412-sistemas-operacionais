# Trabalho Prático 1
## Algoritmo de Escalonamento com Prioridades Dinâmicas e Aging

## Objetivo
O objetivo deste trabalho é implementar um algoritmo de escalonamento de processos
baseado em prioridades dinâmicas com mecanismo de aging para evitar a postergação
indefinida de processos. O algoritmo deverá simular um ambiente multitarefa, considerando
diferentes perfis de processos: CPU-bound, I/O-bound e Memory-bound.

## Descrição
O seu grupo deverá desenvolver um simulador que implemente:
- Escalonamento preemptivo baseado em prioridades dinâmicas;
- Mecanismo de aging, em que processos que aguardam muito tempo na fila de prontos
têm sua prioridade aumentada gradualmente;
- Suporte a três perfis de processos:
  - CPU-bound: requerem muito tempo de CPU e fazem pouca ou nenhuma E/S.
  - I/O-bound: executam operações de entrada/saída frequentemente, com pouco
uso contínuo da CPU.
  - Memory-bound: fazem uso intensivo de memória (simulação aceitável com
operações de alocação e liberação de memória, por exemplo).

## Requisitos da Implementação
1. O simulador deve aceitar uma lista de processos como entrada, com informações como:
  - Identificador
  - Tempo estimado de execução
  - Perfil (CPU-bound, I/O-bound, Memory-bound)
  - Prioridade inicial

2. O algoritmo de escalonamento deve:
  - Escolher o processo de maior prioridade (com desempate por ordem de
chegada);
  - Suportar preempção caso um processo de maior prioridade fique pronto;
  - Aplicar aging para promover processos que estão esperando por tempo
excessivo.

3. O aging pode ser simulado, por exemplo, aumentando a prioridade do processo a cada
n ciclos sem execução.

