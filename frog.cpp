/******************************************************************************
 *                               IME-USP (2018)                               *
 *           MAC0219 - Programacao Concorrente e Paralela - MiniEP2           *
 *                                                                            *
 *                                    Sapo                                    *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP 9297641                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/

#include <bits/stdc++.h>
#include "lake.h"
#include "frog.h"
using namespace std;

static int contador = 0;  // Contador global
// static const int max_dead_lock;
static int game_over = 0; // Indicador de fim de jogo

/******************************************************************************/
Frog::Frog (int _id, int _gender, int _pos)
{
    id = _id;
    gender = _gender;
    pos = _pos;
}

/******************************************************************************/
void Frog::set_lake (Lake *_lake)
{
    lake = _lake;
}

/******************************************************************************/
int Frog::can_move ()
{
    if (gender == 0) { // Ra ->
        if (pos+1 < lake->length && lake->stone[pos+1] < 0)
            return 1; // Pode andar uma pedra para a direita
        if (pos+2 < lake->length && lake->stone[pos+2] < 0)
            return 2; // Pode andar duas pedras para a direita
    } else { // Sapo <-
        if (pos-1 >= 0 && lake->stone[pos-1] < 0)
            return -1; // Pode andar uma pedra para a esquerda
        if (pos-2 >= 0 && lake->stone[pos-2] < 0)
            return -2; // Pode andar duas pedra para a esquerda
    }
    return 0; // Nenhum movimento disponivel
}

/******************************************************************************/
void Frog::move (int dist)
{
    lake->stone[pos+dist] = id;
    lake->stone[pos] = -1;
    pos += dist;
}

/******************************************************************************/
void FROG_move_sync (Lake *lake)
{
    // Somente a ultima thread a sincronizar entra no if
    if (lake->wait() == PTHREAD_BARRIER_SERIAL_THREAD) {
        V(cout << "------------------------------------------" << endl;)

        // Arbitro global
        game_over = 1;
        for (int i = 0; i < lake->length-1; i++) {
            if (lake->frogs[i].can_move()) game_over = 0;
        }

        if (contador > (lake->length-2)*2) {
            game_over = 1;
            if (!silent) {
                printf("Número de tentativas que o programa ficou em deadlock: %d\n", (lake->length-2)*2);
            }
        }
    }
    lake->wait();
}

/******************************************************************************/
void *FROG_thread (void *p_frog)
{
    Frog frog = *((Frog*)p_frog);
    while (1) {
        frog.lake->lock(); // --------------------------- Inicio da area critica
        V(cout << endl << "* Sapo " << frog.id << endl;)                           // TODO
        int dist = frog.can_move();
        if (dist != 0) {
            V(cout << "  De " << frog.pos << " para " << frog.pos+dist << endl;)   // TODO
            frog.move(dist);
            V(frog.lake->show();)
            contador = 0;
        } else {
            contador++;
            V(cout << "  Parado - contador: " << contador << endl;)                // TODO
        }
        frog.lake->unlock(); // ---------------------------- Fim da area critica

        // Espera todos os sapos chegarem neste trecho para prosseguir
        FROG_move_sync(frog.lake);

        if (game_over) break;
    }
    pthread_exit(0);
}

/******************************************************************************/
