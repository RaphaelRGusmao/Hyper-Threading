#ifndef TRAB_H
#define TRAB_H
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


typedef struct st_trabalhador Trabalhador;
struct st_trabalhador {
	int thread_id;
	long M;
	long N;
	long resultado;
    pthread_t thread;
};

Trabalhador *cria_trab(long _M, long _N);
void *trabalhador_thread(void *arg);
long funcao_cpu_dominante(long M, long N);
void destroi_trab(Trabalhador *trab);

#endif