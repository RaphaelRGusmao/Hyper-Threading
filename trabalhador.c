#include "trabalhador.h"


Trabalhador *cria_trab(long _M, long _N) {
	Trabalhador *trab = malloc(sizeof(Trabalhador));
	if (trab == NULL) {
		printf("falta de memoria ao criar trabalhador\n");
		exit(-1);
	}
	trab->M = _M;
	trab->N = _N;
	return trab;
}

// M inicio, N fim
long funcao_cpu_dominante(long M, long N) {
    long pseudo_soma = 0;
    while(M++ < N) {
    	// Contas para ocupar a ULA
    	pseudo_soma += ((rand() % 3) * 4) - 4;
    }	
    return pseudo_soma;
}

void *trabalhador_thread(void *arg) {
    Trabalhador *trab = (Trabalhador *)arg;
    // trab->thread_id = pthread_getthreadid_np();

    trab->thread_id = pthread_self();

	long conta_th = funcao_cpu_dominante(trab->M, trab->N);
	// TODO somar conta_th numa variavel global controlada por um mutex

	printf("thread_id: %d, conta_th: %lu\n", trab->thread_id, conta_th);
    pthread_exit(0);
}

void destroi_trab(Trabalhador *trab) {
	free(trab);
}