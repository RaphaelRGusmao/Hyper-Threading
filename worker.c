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
long funcao_cpu_dominante (long A, long B)
{
    long pseudo_soma = 0;
    while (A++ < B) {
    	pseudo_soma += ((rand() % 3) * 4) - 4;
    }
    return pseudo_soma;
}

/******************************************************************************/
void *WORKER_thread (void *p_worker)
{
    Worker worker = *((Worker*)p_worker);

	long result = funcao_cpu_dominante(worker->A, worker->B);
	// TODO somar result numa variavel global controlada por um mutex

	printf("\tThread%d - Result: %lu\n", worker->id, result);

    pthread_exit(0);
}

/******************************************************************************/
