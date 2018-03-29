/******************************************************************************
 *                               IME-USP (2018)                               *
 *           MAC0219 - Programacao Concorrente e Paralela - MiniEP2           *
 *                                                                            *
 *                                 Principal                                  *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP 9297641                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/
#include <bits/stdc++.h>
#include <stdint.h>
#include <time.h>
#include "lake.h"
#include "frog.h"
using namespace std;

/******************************************************************************/
// Retorna o tempo atual em nanossegundos
uint64_t getTime ()
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return (uint64_t)(time.tv_sec)*1000000000 + (uint64_t)(time.tv_nsec);
}

/******************************************************************************/
// Realiza a simulacao
// Retorna 1 se o programa terminou em um estado ideal (solucao),
//         0 caso contrario
int simulate (int N, int M)
{
    uint64_t beginning = getTime();
    V(cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Inicio ]" << END << endl;)

    // Inicializa a lagoa e cria os sapos
    Lake lake(N, M);
    vector<Frog> frogs;
    for (int i = 0; i < N; i++) { // Ras
        Frog frog(i, 0, i);
        frog.set_lake(&lake);
        frogs.push_back(frog);
        lake.set_position(frog.id, frog.pos);
    }
    for (int i = N; i < N+M; i++) { // Sapos
        Frog frog(i, 1, i+1);
        frog.set_lake(&lake);
        frogs.push_back(frog);
        lake.set_position(frog.id, frog.pos);
    }
    lake.set_frogs(frogs);

    V(lake.show();)

    // Cria as threads
    vector<pthread_t> threads(N+M);
    for (int i = 0; i < N+M; i++) {
        if (pthread_create(&threads[i], NULL, FROG_thread, &frogs[i])) {
           V(cout << YELLOW << "Error creating thread " << i << END << endl;)
           exit(-1);
        }
    }

    // Espera as threads terminarem de executar
    for (int i = 0; i < N+M; i++) {
        if (pthread_join(threads[i], NULL)) {
           V(cout << YELLOW << "Error joining thread " << i << END << endl;)
           exit(-1);
        }
    }

    // Mostra as posições do lago e as posições em que estavam os sapos e rãs no fim da simulação
    if (!silent) {
        cout << "Estado final da lagoa:" << endl;
        lake.show();
        cout << endl;
    }


    // Checa se a lagoa está no estado ideal (ras e sapos trocaram de lugar)
    int ideal = 1;
    for (int i = 0; i < lake.length; i++) {
        if (i < lake.M) {
            // Parte esquerda da lagoa, onde deve haver apenas sapos
            if (lake.stone[i] == -1 || lake.frogs[lake.stone[i]].gender != 1) {
                ideal = 0;
                break;
            }
        }
        if (i == lake.M && lake.stone[i] != -1) {
            // Ha um animal no meio da lagoa
            ideal = 0;
            break;
        }
        if (i > lake.M) {
            // Parte direita da lagoa, onde deve haver apenas ras
            if (lake.stone[i] == -1 || lake.frogs[lake.stone[i]].gender != 0) {
                ideal = 0;
                break;
            }
        }
    }

    // Calcula e mostra o tempo de execucao da simulacao
    uint64_t finish = getTime();
    uint64_t total_time = finish - beginning;
    if (!silent) {
        printf("Tempo de execucao: %lu nanosegundos\n", total_time);
    }

    V(cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Fim ]" << END << endl;)

    /*
    De fato a gente ficou com a mesma dúvida, daí combinamos que seria legal se o programa também imprimisse a seguinte informação.

    1. Número de tentativas que o programa ficou em deadlock. Antes de encontrar a solução correta.
    2. O tempo total gasto do programa
    3. Tabela final com o Id de cada thread e a sua posição na tabela ou vector
    */

    /*

    Para esse segundo Mini EP, o programa deve aceitar um parâmetro de entrada, que seria o número de pedras ou sapos/râs no instancia do problema a ser executada. Daí o Makefile só vai compilar o programa e o usuário executaría o programa estabelecendo o parâmetro de entrada. Por exemplo.:

    ./frogPuzzle <Numero de Sapos | # Pedroas>, explicitar que clase de parâmetro deveria usar no README.

    Pro desafio o Makefile pode compilar e executar o programa.*/

    return ideal;
}

/******************************************************************************/
// Funcao principal
// Recebe o numero de ras (N) e o numero de sapos (M), nesta ordem
int main (int argc, char const *argv[])
{
    if (argc < 2) {
        printf("Número insuficientes de argumentos\n");
        return -1;
    }

    // printf("argv[1] %s\n", argv[1]);
    // int aux = 0;
    // while (argv[aux] != '\0') {
    //     printf(" %s\n", argv[aux++]);
    // }

    const char *silent_arg = "-s";
    int flags = 0;
    if (strcmp(argv[1], silent_arg) == 0) {
        silent = 1;
        flags++;
    }

    int nm[2];
    char *p;
    for (int i = 0; i < 2; i++) {
        errno = 0;
        long conv = strtol(argv[i+1+flags], &p, 10);
        if (errno != 0 || *p != '\0' || conv > INT_MAX) {
            printf("Erro ao converter argumentos para int\n");
            return(1);
        } else {
            nm[i] = conv;
        }
    }

    // nm[0]  Ras   (gender: 0)
    // nm[1]  Sapos (gender: 1)

    return simulate(nm[0], nm[1]);

    // return 0;
}

/******************************************************************************/
