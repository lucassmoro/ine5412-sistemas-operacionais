# Memória Virtual

O presente trabalho tem por objetivo praticar o conceito de memória virtual, aprender a
mecânica do código dos sistemas operacionais modernos no tratamento de interrupções/exceções e
desenvolver capacidade de avaliação quantitativa a nível de sistemas. Esse trabalho tem como base
o trabalho do Prof. Douglas Thain da Universidade de Notre Dame, EUA, disponível em
https://github.com/dthain/opsys-sp22/blob/main/project5/index.md.

Neste trabalho você deverá criar um sistema simples mas funcional de memória virtual
paginada sob demanda. Embora sabemos que a memória virtual é implementada dentro do código
de sistemas operacionais (a nível de kernel), essa técnica também pode ser implementada em nível
de usuário. Isso é exatamente a forma como máquinas virtuais modernas fazem. Desta forma, não
precisamos escrever código em nível de kernel, o que é geralmente difícil de depurar, e nos dá a
possibilidade de aprender e praticar conceitos avançados.

A Figura abaixo apresenta os principais componentes do sistema de memória virtual deste trabalho:

Um código base em C++ está disponível juntamente com essa descrição. Esse código base
implementa a tabela de páginas virtual e um disco virtual. A tabela de páginas virtual cria uma
pequena memória virtual e física, juntamente com os métodos para atualizar as entradas na tabela de
página e os bits de proteção para cada página. Quando uma aplicação usar a memória virtual não
mapeada, faltas de páginas (page faults) serão geradas e um tratador será chamado para realizar as
atividades associadas.

Seu trabalho será implementar esse tratador de faltas de páginas e
identificar a correta lista de ações a serem realizadas: atualizar a tabela de páginas, mover
dados de volta para o disco ou trazer dados do disco de/para a memória física, além de
implementar algortimos de substituição de páginas.

Uma vez que o sistema esteja funcional, seu trabalho será avaliar o desempenho dos
algoritmos de substituição de páginas usando 4 programas simples que são disponibilizados
juntamente com o código, sendo que tais programas têm diferentes demandas em relação ao
tamanho de memória utilizada. Você deverá escrever um breve relatório explicando os
experimentos, os resultados obtidos e as conclusões para cada programa.

