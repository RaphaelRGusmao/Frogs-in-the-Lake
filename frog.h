/******************************************************************************
 *                               IME-USP (2018)                               *
 *           MAC0219 - Programacao Concorrente e Paralela - MiniEP2           *
 *                                                                            *
 *                                    Sapo                                    *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP ???????                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/

#ifndef FROG_H
#define FROG_H

#include "lake.h"
class Lake;

// Sapo
class Frog {
public:
    Lake *lake; // Lagoa
    int id;     // ID do sapo
    int gender; // Genero (Ra:1, Sapo:-1)
    int pos;    // Posicao do sapo na lagoa
    /**************************************************************************/
    Frog (int _id, int _gender, int _pos); // Construtor
    void set_lake (Lake *_lake);           // Define a lagoa
    int can_move ();                       // Devolve a distancia da pedra de destino
    void move (int dist);                  // Move o sapo dist pedras
};

// Thread do sapo p_frog
void *FROG_thread (void *p_frog);

#endif

/******************************************************************************/
