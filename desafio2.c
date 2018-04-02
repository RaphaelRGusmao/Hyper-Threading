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

#define n_contas 1000000
#define n_threads 4 //n_threads deve dividir n_contas de forma exata

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
    uint64_t beginning_single = getTime();
    long result = funcao_cpu_dominante(0, n_contas);
    uint64_t finish_single = getTime();
    printf("\tThread Main - Result: %lu\n", result);
    printf("\tTempo total de execucao: %lu nanossegundos\n\n", finish_single - beginning_single);

    // -------------------------------------------------- Execucao com n threads
    printf(GREEN "Execucao com %d threads:\n" END, n_threads);
    Worker *workers = malloc(n_threads * sizeof(Worker));
    if (workers == NULL) {
		printf(YELLOW "Error creating workers array\n" END);
		exit(EXIT_FAILURE);
    }
    
    // Supomos que n_threads divide n_contas
    long interval = n_contas / n_threads;
    for (long i = 0; i < n_threads; i++) {
    	workers[i] = WORKER_new(i, i*interval, (i+1)*interval);                                // TODO dividir o trabalho igualmente
    }

    // Inicializando rand com uma semente definida para garantir que cada
    // execucao fara as mesmas operacoes
    srand((unsigned) 1);

    // Aloca memória para as threads
    pthread_t *threads = malloc(n_threads * sizeof(pthread_t));
    if (threads == NULL) {
        printf(YELLOW "Error creating threads array\n" END);
        exit(EXIT_FAILURE);
    }

    pthread_mutex_init(&mutex, 0);
    
    // Contando o tempo de execucao de n threads
	uint64_t beginning_threads = getTime();

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
        // printf("pseudo soma no meio: %lu\n", pseudo_sum);
    }
    // Calcula e mostra o tempo de execucao da simulacao
    uint64_t finish_threads = getTime();
    printf("\tTempo total de execucao com %d threads: %lu nanossegundos\n",
            n_threads, finish_threads - beginning_threads);

    printf("\t%d threads - Result: %lu\n", n_threads, WORKER_get_pseudo_sum());

    // Libera toda a memoria alocada
    for (int i = 0; i < n_threads; i++) {
        free(workers[i]);
    }
    free(workers);
    pthread_mutex_destroy(&mutex);


    printf(CYAN "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Fim ]\n\n" END);
}

/******************************************************************************/
