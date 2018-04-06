################################################################################
#                                IME-USP (2018)                                #
#           MAC0219 - Programacao Concorrente e Paralela - Desafio2            #
#                                                                              #
#                                    Testes                                    #
#                                                                              #
#                       Marcelo Schmitt   - NUSP 9297641                       #
#                       Raphael R. Gusmao - NUSP 9778561                       #
################################################################################

#!/usr/bin/env bash
cpus=0
# Descobre o número de CPUs do processador
cpus=$(lscpu | grep ^'CPU(s):' | cut -s -d ' ' -f2-)
# Descobre qual CPU eh HT da CPU0
cpu0ht=$(cat /sys/devices/system/cpu/cpu0/topology/thread_siblings_list | cut -s -d- -f2-)

# Desabilita todas as CPUs menos uma (a CPU0)
cpunum=1
while [ $cpunum -lt $cpus ];
do
	echo 'desabilitando CPU'$cpunum
	echo 0 > /sys/devices/system/cpu/cpu$cpunum/online
	let cpunum=cpunum+1
done

# Espera um pouco para ter certeza de que ao rodar o programa, as  CPUs  estarao
# desabilitadas
sleep 5s

echo 'rodando o calculos com uma thread (sem HT)'
lscpu --extended
# Roda o programa com uma unica CPU
./desafio2

# Habilita somente a CPU virtual da CPU0 (isto eh, habilita a HT da CPU0)
echo 'habilitando CPU'$cpu0ht
echo 1 > /sys/devices/system/cpu/cpu$cpu0ht/online

# Espera um pouco
sleep 5s

echo 'rodando o calculos com duas threads (uma física e uma HT)'
lscpu --extended
# Roda o programa com duas threads (uma thread fisica e uma thread HT)
./desafio2 2

# Habilita novamente as CPUs
cpunum=1
while [ $cpunum -lt $cpus ];
do
	echo 'habilitando CPU'$cpunum
	echo 1 > /sys/devices/system/cpu/cpu$cpunum/online
	let cpunum=cpunum+1
done
# Fim dos testes e as CPUs estao de volta online =]
echo 'fim'

################################################################################
