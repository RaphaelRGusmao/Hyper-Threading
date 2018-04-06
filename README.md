# Desafio 2 - Hyper-threading
O Desafio2 recebe como argumento opcional o numero de threads que  devem ser usadas. Se o argumento nao estiver presente executa com uma unica thread.
___
Para executar o Desafio2 no terminal, digite:

    $ make
    $ ./desafio2
ou

    $ make run
___
Exemplo de saída:

    Execucao fazendo contas com variavel do tipo long
    Execucao com 1 thread:
    	Thread Main - Result: 20000000
    	Tempo total de execucao: 43164766 nanossegundos
    Execucao com 2 threads:
    	Thread   1 - Result: 10000000
    	Thread   0 - Result: 10000000
    	Total              : 20000000
    	Tempo total de execucao: 28868148 nanossegundos

    Execucao fazendo contas com variavel do tipo long e chamadas a rand()
    Execucao com 1 thread:
    	Thread Main - Result: 22014952
    	Tempo total de execucao: 291335333 nanossegundos
    Execucao com 2 threads:
    	Thread   1 - Result: 11006119
    	Thread   0 - Result: 11008833
    	Total              : 42014952
    	Tempo total de execucao: 1184217784 nanossegundos

    Execucao fazendo contas com variavel do tipo long double
    Execucao com 1 thread:
    	Thread Main - Result: 5000000.00
    	Tempo total de execucao: 54665942 nanossegundos
    Execucao com 2 threads:
    	Thread   1 - Result: 2500000.00
    	Thread   0 - Result: 2500000.00
    	Total              : 5000000.00
    	Tempo total de execucao: 38860315 nanossegundos
