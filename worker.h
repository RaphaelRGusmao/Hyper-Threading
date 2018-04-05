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

// Variavel compartilhada entre as threads (para testes com long double)
static long double long_double_pseudo_sum = 0.0;

// Variavel compartilhada entre as threads (para testes com long)
static long long_pseudo_sum = 0;

// Mutex para controlar o acesso a variavel compartilhada
pthread_mutex_t mutex;

// Fonte
#define CYAN      "\033[36;1m" // Azul claro
#define GREEN     "\033[32;1m" // Verde
#define YELLOW    "\033[33;1m" // Amarelo
#define END       "\033[0m"    // Para de pintar

// Trabalhador
struct worker {
	int id;
	int type;                 // 0 long, 1 long com rand, 2 long double
	long A;
	long B;
	long double result;
	long long_result;

};
typedef struct worker *Worker;

// Cria um trabalhador
Worker WORKER_new (int id, int type, long A, long B);

// Faz contas para ocupar a ULA
long funcao_cpu_dominante_long(long A, long B);

// Faz contas para ocupar a ULA
long funcao_cpu_dominante_long_rand(long A, long B);

// Faz contas para ocupar a FPU
long double funcao_cpu_dominante_long_double(long A, long B);

// Thread do trabalhador
void *WORKER_thread(void *arg);

// Funcao para controlar o acesso a variavel compartilhada
void WORKER_add_to_long_double_sum (long double quantitie);

// Funcao para controlar o acesso a variavel compartilhada
void WORKER_add_to_long_sum (long quantitie);

long double WORKER_get_long_double_pseudo_sum();

long WORKER_get_long_pseudo_sum();

#endif

/******************************************************************************/
