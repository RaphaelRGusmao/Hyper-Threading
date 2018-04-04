/******************************************************************************
 *                               IME-USP (2018)                               *
 *          MAC0219 - Programacao Concorrente e Paralela - Desafio2           *
 *                                                                            *
 *                                Trabalhador                                 *
 *                                                                            *
 *                      Marcelo Schmitt   - NUSP 9297641                      *
 *                      Raphael R. Gusmao - NUSP 9778561                      *
 ******************************************************************************/
#include "worker.h"


/******************************************************************************/
Worker WORKER_new (int id, long A, long B)
{
	Worker worker = malloc(sizeof(*worker));
	if (worker == NULL) {
		printf(YELLOW "Error creating worker\n" END);
		exit(EXIT_FAILURE);
	}
	worker->id = id;
	worker->A = A;
	worker->B = B;
	return worker;
}

/******************************************************************************/
long double funcao_cpu_dominante (long A, long B)
{
    long double tmp_sum = 0;
    while (A++ < B) {
    	// tmp_sum += ((rand() % 3) * 4) - 4;
    	// tmp_sum += ((rand() % 5) * 2) - 4;
    	// tmp_sum += 1;
    	// Contas para ocupar a FPU
    	tmp_sum += (((17 % 4) * 5) - 2)*1.0 / 6;
    }
    return tmp_sum;
}

/******************************************************************************/
void *WORKER_thread (void *p_worker)
{
    Worker worker = *((Worker*)p_worker);

	long double result = funcao_cpu_dominante(worker->A, worker->B);

	printf("\tThread%d - Result: %.2Lf\n", worker->id, result);
	// Soma o result numa variavel global controlada por um mutex
	WORKER_add_to_sum(result);

    pthread_exit(0);
}

/******************************************************************************/
void WORKER_add_to_sum (long double quantitie) {
	// printf("quantitie %lu   pseudo_sum %lu\n", quantitie, pseudo_sum);
	pthread_mutex_lock(&mutex);
	pseudo_sum += quantitie;
	pthread_mutex_unlock(&mutex);
	// printf("quantitie %lu   pseudo_sum %lu\n", quantitie, pseudo_sum);
}

/******************************************************************************/
long double WORKER_get_pseudo_sum() {
	return pseudo_sum;
}

/******************************************************************************/
