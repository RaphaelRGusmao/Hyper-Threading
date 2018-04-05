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
Worker WORKER_new (int id, int type, long A, long B)
{
	Worker worker = malloc(sizeof(*worker));
	if (worker == NULL) {
		printf(YELLOW "Error creating worker\n" END);
		exit(EXIT_FAILURE);
	}
	worker->id = id;
	worker->type = type;
	worker->A = A;
	worker->B = B;
	return worker;
}

/******************************************************************************/
long funcao_cpu_dominante_long (long A, long B)
{
    long tmp_sum = 0;
    while (A++ < B) {
    	// Contas para ocupar a ULA
    	tmp_sum += (((15 % 4) * 5) - 2) / 6;
    }
    return tmp_sum;
}

/******************************************************************************/
long funcao_cpu_dominante_long_rand (long A, long B)
{
    long tmp_sum = 0;
    while (A++ < B) {
    	// Contas para ocupar a ULA
    	tmp_sum += (((rand() % 5) * 6) - 4) / 3;
    }
    return tmp_sum;
}

/******************************************************************************/
long double funcao_cpu_dominante_long_double (long A, long B)
{
    long double tmp_sum = 0;
    while (A++ < B) {
    	// Contas para ocupar a FPU
    	tmp_sum += (((17 % 4) * 5) - 2)*1.0 / 6;
    }
    return tmp_sum;
}

/******************************************************************************/
void *WORKER_thread (void *p_worker)
{
    Worker worker = *((Worker*)p_worker);

	if (worker->type == 0) {
		long result = funcao_cpu_dominante_long(worker->A, worker->B);

		printf("\tThread %3d - Result: %lu\n", worker->id, result);
		// Soma o result numa variavel global controlada por um mutex
		WORKER_add_to_long_sum(result);
	} else if (worker->type == 1) {
		long result = funcao_cpu_dominante_long_rand(worker->A, worker->B);

		printf("\tThread %3d - Result: %lu\n", worker->id, result);
		// Soma o result numa variavel global controlada por um mutex
		WORKER_add_to_long_sum(result);
	} else {
		long double result = funcao_cpu_dominante_long_double(worker->A, worker->B);

		printf("\tThread %3d - Result: %.2Lf\n", worker->id, result);
		// Soma o result numa variavel global controlada por um mutex
		WORKER_add_to_long_double_sum(result);
	}

    pthread_exit(0);
}

/******************************************************************************/
void WORKER_add_to_long_sum (long quantitie)
{
	pthread_mutex_lock(&mutex);
	long_pseudo_sum += quantitie;
	pthread_mutex_unlock(&mutex);
}

/******************************************************************************/
void WORKER_add_to_long_double_sum (long double quantitie)
{
	pthread_mutex_lock(&mutex);
	long_double_pseudo_sum += quantitie;
	pthread_mutex_unlock(&mutex);
}

/******************************************************************************/
long double WORKER_get_long_double_pseudo_sum ()
{
	return long_double_pseudo_sum;
}

/******************************************************************************/
long WORKER_get_long_pseudo_sum ()
{
	return long_pseudo_sum;
}

/******************************************************************************/
