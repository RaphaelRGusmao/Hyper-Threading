/******************************************************************************
 *                               IME-USP (2018)                               *
 *          MAC0219 - Programacao Concorrente e Paralela - Desafio2           *
 *                                                                            *
 *                                Trabalhador                                 *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP 9297641                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/
#ifndef WORKER_H
#define WORKER_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// Fonte
#define CYAN      "\033[36;1m" // Azul claro
#define GREEN     "\033[32;1m" // Verde
#define YELLOW    "\033[33;1m" // Amarelo
#define END       "\033[0m"    // Para de pintar

// Trabalhador
struct worker {
	int id;
	long A;
	long B;
	long result;
    pthread_t thread;															// TODO
};
typedef struct worker *Worker;

// Cria um trabalhador
Worker WORKER_new (int id, long A, long B);

// Faz contas para ocupar a ULA
long funcao_cpu_dominante(long A, long B);			    						// TODO

// Thread do trabalhador
void *WORKER_thread(void *arg);

#endif

/******************************************************************************/
