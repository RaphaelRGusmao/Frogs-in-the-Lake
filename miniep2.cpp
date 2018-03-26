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
int main ()
{
    int N = 3; // Ras   (gender: 0)
    int M = 3; // Sapos (gender: 1)

    simulate(N, M);

    return 0;
}

/******************************************************************************/
