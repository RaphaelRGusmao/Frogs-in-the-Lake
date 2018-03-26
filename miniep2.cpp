/******************************************************************************
 *                               IME-USP (2018)                               *
 *           MAC0219 - Programacao Concorrente e Paralela - MiniEP2           *
 *                                                                            *
 *                                 Principal                                  *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP ???????                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/

#include <bits/stdc++.h>
#include "lake.h"
#include "frog.h"
using namespace std;

/******************************************************************************/
// Realiza a simulacao
void simulate (int N, int M)
{
    cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Inicio ]" << END << endl;

    // Inicializa a lagoa e cria os sapos
    Lake lake(N+M+1);
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

    lake.show();                                                                // TODO

    // Cria as threads
    vector<pthread_t> threads(N+M);
    for (int i = 0; i < N+M; i++) {
        if (pthread_create(&threads[i], NULL, FROG_thread, &frogs[i])) {
           cout << YELLOW << "Error creating thread " << i << END << endl;
           exit(-1);
        }
    }

    // Espera as threads terminarem de executar
    for (int i = 0; i < N+M; i++) {
        if (pthread_join(threads[i], NULL)) {
           cout << YELLOW << "Error joining thread " << i << END << endl;
           exit(-1);
        }
    }

    lake.show();                                                                // TODO

    cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Fim ]" << END << endl;
}

/******************************************************************************/
// Funcao principal
// Recebe o número de rãns (N) e o número de sapos (M)
int main (int argc, char const *argv[])
{
    if (argc < 2) {
        printf("Número insuficientes de argumentos\n");
        return -1;
    }
    int nm[2];
    char *p;
    for (int i = 0; i < 2; i++) {
        errno = 0;
        long conv = strtol(argv[i+1], &p, 10);
        if (errno != 0 || *p != '\0' || conv > INT_MAX) {
            printf("Erro ao converter argumentos para int\n");
            return(1);
        } else {
            nm[i] = conv;    
        }
    }

    // nm[0]  Ras   (gender: 0)
    // nm[1]  Sapos (gender: 1)

    simulate(nm[0], nm[1]);

    return 0;
}

/******************************************************************************/
