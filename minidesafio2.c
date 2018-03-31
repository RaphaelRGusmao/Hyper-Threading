#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>


#define n_contas 1000
#define n_threads 4

// Retorna o tempo atual em nanossegundos
uint64_t getTime ()
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return (uint64_t)(time.tv_sec)*1000000000 + (uint64_t)(time.tv_nsec);
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

// void *cyclist_thread(void *arg) {
//     Cyclist *cyclist = (Cyclist *)arg;
//     Simulator *sim = cyclist->sim;

//     pthread_barrier_wait(cyclist->barrier);
//     while (TRUE) {
//         update_position(cyclist, sim, sim->refresh_rate);

//         if (update_lap(cyclist, sim)) {
//             int placing = 0;
//             if (cyclist->lap > 0) {
// 				placing = complete_lap(cyclist, sim);
//                 update_speed(cyclist, FALSE);
//                 if (cyclist->speed == 90)
//                     sim->refresh_rate = 20;
// 			}

//             if (complete_finish(sim, cyclist, placing)) {
//                 remove_cyclist(cyclist);
//                 pthread_exit(0);
//             }

//             if (cyclist->lap > 0 
//                     && sim->n - sim->n_broken_cyc - sim->n_finished_cyc > 5 
//                     && cyclist->lap % BREACK_PERIOD == 0)
//                 if (try_break_cyclist(cyclist, placing)) {
//                     pthread_exit(0);
//                 }
//         }
//     }
//     pthread_exit(0);

// }

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

    // Execucao com quatro threads

    // Inicializando rand com uma semente definida para garantir que cada
    // execucao fara as mesmas operacoes
    // srand((unsigned) 1);


    // int error = pthread_create(&cyclist->thread, NULL, cyclist_thread, cyclist);
    // if (error) {
    //     printf("Erro ao criar pthread %d\n", error);
    //     exit(EXIT_FAILURE);
    // }



    printf("fim %lu \n", conta_um);

}