################################################################################
#                                IME-USP (2018)                                #
#            MAC0219 - Programacao Concorrente e Paralela - MiniEP2            #
#                                                                              #
#                                  README                                      #
#                                                                              #
#                       Marcelo Schmitt   - NUSP 9297641                       #
#                       Raphael R. Gusmao - NUSP 9778561                       #
################################################################################

O MiniEP2 recebe como argumentos o numero de ras (N) e o numero de sapos (M), 
nesta ordem.

Para executar o MiniEP2 no terminal, digite:
    $ make
    $ ./miniep2 3 3
    ou
    $ make run

Exemplo de saida:
________________________________________________________________________________
Estado final da lagoa:

  0 1 2 3 4 5
0 1 2 3 4 5 6

Tempo de execucao: 1997666 nanosegundos
________________________________________________________________________________

Para executar os testes do MiniEP2  no terminal, digite:
    $./teste.sh

Exemplo de saida dos testes:
________________________________________________________________________________
rodando o mini-ep2 com 2 ras e 2 sapos
numero de execucoes: 10000
vezes que chegou no final ideal: 31
peso percentual de cada execucao: .01000%
porcentagem de vezes no final ideal: .31000%
________________________________________________________________________________


Obs:
    A primeira linha da lagoa mostra os animais (Sapos em verde, Ras em rosa)
    A segunda linha mostra os numeros das pedras da lagoa
    Existe um modo verbose que imprime cada passo da execução do programa.
    O modo verbose pode ser ativado descomentando o #define VERBOSE no arquivo
    lake.h.

################################################################################
