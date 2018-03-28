/******************************************************************************
 *                               IME-USP (2018)                               *
 *           MAC0219 - Programacao Concorrente e Paralela - MiniEP2           *
 *                                                                            *
 *                                   Lagoa                                    *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP 9297641                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/

#include <bits/stdc++.h>
#include "lake.h"
#include "frog.h"
using namespace std;

static pthread_barrier_t barrier; // Barreira de sincronizacao
static pthread_mutex_t mutex;     // Semaforo

/******************************************************************************/
Lake::Lake (int _N, int _M)
{
    N = _N;
    M = _M;
    length = N + M + 1;
    stone = new int[length];
    for (int i = 0; i < length; i++) {
        stone[i] = -1;
    }
    if (pthread_barrier_init(&barrier, NULL, length-1)){
       cout << YELLOW << "Error initializing barrier" << END << endl;
       exit(-1);
    }
    if (pthread_mutex_init(&mutex, NULL)){
       cout << YELLOW << "Error initializing mutex" << END << endl;
       exit(-1);
    }
}

/******************************************************************************/
void Lake::show ()
{
    cout << endl;
    for (int i = 0; i < length; i++) {
        if (stone[i] < 0) {
            cout << UNDERLINE << " " << END << " ";
        } else {
            if (frogs[stone[i]].gender == 0) {
                cout << UNDERLINE << PINK << stone[i] << END << " ";
            } else {
                cout << UNDERLINE << GREEN << stone[i] << END << " ";
            }
        }
    }
    cout << endl;
    for (int i = 0; i < length; i++) cout << i << " ";
    cout << endl;
}

/******************************************************************************/
void Lake::set_frogs (vector<Frog> &_frogs)
{
    frogs = _frogs;
}

/******************************************************************************/
void Lake::set_position (int id, int pos)
{
    stone[pos] = id;
}

/******************************************************************************/
int Lake::wait ()
{
    return pthread_barrier_wait(&barrier);
}

/******************************************************************************/
void Lake::lock ()
{
    pthread_mutex_lock(&mutex);
}

/******************************************************************************/
void Lake::unlock ()
{
    pthread_mutex_unlock(&mutex);
}

/******************************************************************************/
