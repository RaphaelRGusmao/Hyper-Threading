// #include <stdlib.h>
// #include <stdio.h>
#include <time.h>
// #include <pthread.h>
#include <stdint.h>
#include "trabalhador.h"

#define n_contas 10000
#define n_threads 4

// Retorna o tempo atual em nanossegundos
uint64_t getTime () {
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return (uint64_t)(time.tv_sec)*1000000000 + (uint64_t)(time.tv_nsec);
}


int main() {
	long conta_um;

    // Execucao com uma thread
    uint64_t inicio_um = getTime();

    // Inicializando rand com uma semente definida para garantir que cada
    // execucao fara as mesmas operacoes
    srand((unsigned) 1);
    
    conta_um = funcao_cpu_dominante(0, n_contas);

    // Calcula e mostra o tempo de execucao da simulacao
    uint64_t fim_um = getTime();
    uint64_t tempo_total_um = fim_um - inicio_um;
    printf("Tempo total de execucao com uma thread: %lu nanossegundos\n", tempo_total_um);



    /* Execucao com quatro threads                                            */

    // Inicializando rand com uma semente definida para garantir que cada
    // execucao fara as mesmas operacoes
    srand((unsigned) 1);


    Trabalhador **trabs; // = malloc(n_threads * sizeof(Trabalhador*));
    trabs = malloc(n_threads * sizeof(Trabalhador*));
    if (trabs == NULL) {
		printf("falta de memoria ao criar vetor de trabalhador\n");
		exit(-1);
    }
    for (int i = 0; i < n_threads; i++) {
    	trabs[i] = cria_trab(0, n_contas); // TODO dividir o trabalho igualmente
    }

    // Contando o tempo de execucao de n threads
	uint64_t inicio_threads = getTime();

	printf("antes de iniciar as threads\n");
	printf("trabs 0    %lu      %lu\n", trabs[2]->M, trabs[2]->N);

    for (int i = 0; i < n_threads; i++) {
	    int error = pthread_create(&trabs[i]->thread, NULL, trabalhador_thread, trabs[i]);
	    if (error) {
	        printf("Erro ao criar pthread %d\n", error);
	        exit(EXIT_FAILURE);
	    }
    }

    printf("threads iniciadas\n");


    // pthread join
    for (int i = 0; i < n_threads; i++) {
    	pthread_join(trabs[i]->thread_id, NULL);
    }

    for (int i = 0; i < n_threads; ++i) {
    	destroi_trab(trabs[i]);
    }
    free(trabs);

    // Calcula e mostra o tempo de execucao da simulacao
    uint64_t fim_threas = getTime();
    uint64_t tempo_total_threads = fim_threas - inicio_threads;
    printf("Tempo total de execucao com %d thread: %lu nanossegundos\n",n_threads, tempo_total_threads);

    printf("fim %lu \n", conta_um);

}