# MiniEP2 - Verificação usando pthreads
O MiniEP2 recebe como argumentos o número de rãs (N) e o número de sapos (M), nesta ordem.
___
Para executar o MiniEP2 no terminal, digite:

    $ make
    $ ./miniep2 3 3
ou

    $ make run
___
Exemplo de saída:

    Estado final da lagoa:

      0 1 2 3 4 5
    0 1 2 3 4 5 6

    Tempo de execucao: 1997666 nanossegundos
___
Para executar os testes do MiniEP2 no terminal, digite:

    $ ./teste.sh
___
Exemplo de saída dos testes:

    Rodando o MiniEP2 com 2 ras e 2 sapos
    Numero de execucoes: 10000
    Vezes que chegou no final ideal: 31
    Peso percentual de cada execucao: .01000%
    Porcentagem de vezes no final ideal: .31000%
___
**Obs:**
- A primeira linha da lagoa mostra os animais (Sapos em verde, Ras em rosa)
- A segunda linha mostra os numeros das pedras da lagoa
- Existe um modo verbose que imprime cada passo da execução do programa.
- O modo verbose pode ser ativado descomentando o #define VERBOSE no arquivo *lake.h*. 
