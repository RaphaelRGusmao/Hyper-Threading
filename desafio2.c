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
#include <string.h>
#include <pthread.h>
#include <limits.h>
#include <errno.h>
#include "worker.h"

#define n_contas 10000000

/******************************************************************************/
// Retorna o tempo atual em nanossegundos
uint64_t getTime () {
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return (uint64_t)(time.tv_sec)*1000000000 + (uint64_t)(time.tv_nsec);
}

/******************************************************************************/
// Funcao principal
// Recebe como argumento opcional o numero de threads que devem ser usadas.
// Se o argumento nao estiver presente executa com uma unica thread.
int main (int argc, char const *argv[])
{

    int n_threads = 1;

    if (argc > 1) {
        char *p;
        errno = 0;
        int conv = strtol(argv[1], &p, 10);
        if (errno != 0 || *p != '\0' || conv > INT_MAX) {
            printf("Erro ao converter argumentos para int\n");
            return(1);
        } else {
            n_threads = conv;
        }
    }

    // Poderiamos ter feito um if aqui para executar apenas o trecho de uma 
    // thread ou o trecho de mais threads mas achamos interessante executar
    // ambos para visualizar se as contas feitas pelas varias threads foram
    // as mesmas que uma unica thread faria e também para ter sempre visivel
    // uma amostra do tempo que uma unica thread tomaria para executar.
    // Mesmo assim na hora de realizar os testes levamos em conta os
    // resultados de uma thread quando apenas uma CPU estava ativa e os
    // resultados com n threads quando exatamente n CPUs estavam ativas.
    // Verificamos isso com o comando lscpu --extended no shell.

    // Um resultado interessante de ser observado eh rodar o programa sem 
    // argumento opcional e comparar os tempos de execucao para uma thread
    // e para n = 1 thread(s). O tempo da primeira execucao eh sempre 
    // ligeiramente menor devido a nao precisar da estrutura de multitred
    // (alocar memoria para a thread, criar uma thread separada da main para
    // calcular, usar o mutex).

    printf(CYAN "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Inicio ]\n\n" END);


    //Uma execucao fazendo contas com variavel do tipo long,
    //uma execucao fazendo contas com variavel do tipo long a chamadas a rand(),
    //uma execucao fazendo contas com variavel do tipo long double
    for (int type = 0; type < 3; type++) {
        if (type == 0) {
            printf(YELLOW "Execucao fazendo contas com variavel do tipo long\n" END);
        } else if (type == 1) {
            printf(YELLOW "Execucao fazendo contas com variavel do tipo long e chamadas a rand()\n" END);
        } else {
            printf(YELLOW "Execucao fazendo contas com variavel do tipo long double\n" END);
        }


        // Inicializando rand com uma semente definida para garantir que cada
        // execucao fara as mesmas operacoes
        srand((unsigned) 1);

        // --------------------------------------------------- Execucao com 1 thread
        printf(GREEN "Execucao com 1 thread:\n" END);
        printf("Contas feitas com variavel do tipo \n");
        uint64_t beginning_single = getTime();
        if (type == 0) {
            long result = funcao_cpu_dominante_long(0, n_contas);
            uint64_t finish_single = getTime();
            printf("\tThread Main - Result: %lu\n", result);
            printf("\tTempo total de execucao: %lu nanossegundos\n\n", finish_single - beginning_single);
        } else if (type == 1) {
            long result = funcao_cpu_dominante_long_rand(0, n_contas);
            uint64_t finish_single = getTime();
            printf("\tThread Main - Result: %lu\n", result);
            printf("\tTempo total de execucao: %lu nanossegundos\n\n", finish_single - beginning_single);
        } else {
            long double result = funcao_cpu_dominante_long_double(0, n_contas);
            uint64_t finish_single = getTime();
            printf("\tThread Main - Result: %.2Lf\n", result);
            printf("\tTempo total de execucao: %lu nanossegundos\n\n", finish_single - beginning_single);
        }

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
            workers[i] = WORKER_new(i, type, i*interval, (i+1)*interval);
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
        }

        // Calcula e mostra o tempo de execucao da simulacao
        uint64_t finish_threads = getTime();

        if (type == 0) {
            printf("\t%d threads - Result: %lu\n", n_threads, WORKER_get_long_pseudo_sum());
        } else if (type == 1) {
            printf("\t%d threads - Result: %lu\n", n_threads, WORKER_get_long_pseudo_sum());
        } else {
            printf("\t%d threads - Result: %.2Lf\n", n_threads, WORKER_get_long_double_pseudo_sum());
        }

        printf("\tTempo total de execucao com %d threads: %lu nanossegundos\n",
                n_threads, finish_threads - beginning_threads);
        
        // Libera a memoria alocada
        for (int i = 0; i < n_threads; i++) {
            free(workers[i]);
        }
        free(workers);
    }

    pthread_mutex_destroy(&mutex);


    printf(CYAN "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Fim ]\n\n" END);
}

/******************************************************************************/
