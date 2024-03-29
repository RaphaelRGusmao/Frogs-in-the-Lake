/******************************************************************************
 *                               IME-USP (2018)                               *
 *           MAC0219 - Programacao Concorrente e Paralela - MiniEP2           *
 *                                                                            *
 *                                   Lagoa                                    *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP 9297641                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/

#ifndef LAKE_H
#define LAKE_H

// #define VERBOSE

#ifdef VERBOSE
    #define V(X) X
#else
    #define V(X)
#endif

#include "frog.h"
using namespace std;

// Fonte
#define UNDERLINE "\033[4m"    // Underline_
#define CYAN      "\033[36;1m" // Azul claro
#define GREEN     "\033[32;1m" // Verde
#define PINK      "\033[35;1m" // Rosa
#define YELLOW    "\033[33;1m" // Amarelo
#define END       "\033[0m"    // Para de pintar

// Lagoa
class Lake {
public:
    vector<Frog> frogs;    // Vetor de sapos
    int *stone;            // Vetor de pedras
    int N;                 // Numero de ras
    int M;                 // Numero de sapos
    int length;            // Tamanho da lagoa
    int silent;            // Se nao deve imprimir informacoes adicionais
    /**************************************************************************/
    Lake (int N, int M);                   // Construtor
    void show ();                          // Exibe a lagoa
    void set_frogs (vector<Frog> &_frogs); // Define o vetor de sapos
    void set_position (int id, int pos);   // Coloca o sapo id na posicao pos
    int wait ();                           // Barreira de sincronizacao
    void lock ();                          // Tranca a lagoa
    void unlock ();                        // Destranca a lagoa
    int is_silent();                       // Retorna se esta no modo silencioso
    void set_silent(int _silent);          // Define modo silencioso
};

#endif

/******************************************************************************/
