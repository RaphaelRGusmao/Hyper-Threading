/******************************************************************************
 *                               IME-USP (2018)                               *
 *          MAC0219 - Programacao Concorrente e Paralela - Desafio2           *
 *                                                                            *
 *                                 Principal                                  *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP 9297641                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <pthread.h>
#include "worker.h"

#define n_contas 10000
#define n_threads 4

/******************************************************************************/
// Retorna o tempo atual em nanossegundos
uint64_t getTime () {
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return (uint64_t)(time.tv_sec)*1000000000 + (uint64_t)(time.tv_nsec);
}

/******************************************************************************/
// Funcao principal
int main ()
{
    printf(CYAN "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Inicio ]\n\n" END);
    // Inicializando rand com uma semente definida para garantir que cada
    // execucao fara as mesmas operacoes
    srand((unsigned) 1);

    // --------------------------------------------------- Execucao com 1 thread
    printf(GREEN "Execucao com 1 thread:\n" END);
    uint64_t inicio_um = getTime();
    long result = funcao_cpu_dominante(0, n_contas);
    uint64_t fim_um = getTime();
    printf("\tThread Main - Result: %lu\n", result);
    printf("\tTempo total de execucao: %lu nanossegundos\n\n", fim_um - inicio_um);

    // -------------------------------------------------- Execucao com n threads
    printf(GREEN "Execucao com %d threads:\n" END, n_threads);
    Worker *workers = malloc(n_threads * sizeof(Worker));
    if (workers == NULL) {
		printf(YELLOW "Error creating workers array\n" END);
		exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n_threads; i++) {
    	workers[i] = WORKER_new(i, 0, n_contas);                                // TODO dividir o trabalho igualmente
    }

    // Contando o tempo de execucao de n threads
	uint64_t inicio_threads = getTime();

    // Cria as threads
    pthread_t *threads = malloc(n_threads * sizeof(pthread_t));
    if (threads == NULL) {
		printf(YELLOW "Error creating threads array\n" END);
		exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n_threads; i++) {
	    if (pthread_create(&threads[i], NULL, WORKER_thread, &workers[i])) {
	        printf(YELLOW "Error creating thread %d\n" END, i);
	        exit(EXIT_FAILURE);
	    }
    }

    // Espera as threads terminarem de executar
    for (int i = 0; i < n_threads; i++) {
        if (pthread_join(threads[i], NULL)) {
	        printf(YELLOW "Error joining thread %d\n" END, i);
	        exit(EXIT_FAILURE);
	    }
    }

    // Libera toda a memoria alocada
    for (int i = 0; i < n_threads; i++) {
    	free(workers[i]);
    }
    free(workers);

    // Calcula e mostra o tempo de execucao da simulacao
    uint64_t fim_threads = getTime();
    printf("\tTempo total de execucao com %d thread: %lu nanossegundos\n",
            n_threads, fim_threads - inicio_threads);

    printf(CYAN "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Fim ]\n\n" END);
}

/******************************************************************************/
