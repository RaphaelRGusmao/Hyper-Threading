#!/usr/bin/env bash
cpus=0
#descobre o número de CPUs do processador
cpus=$(lscpu | grep ^'CPU(s):' | cut -s -d ' ' -f2-)
#descobre qual CPU é HT da CPU0
cpu0ht=$(cat /sys/devices/system/cpu/cpu0/topology/thread_siblings_list | cut -s -d- -f2-)

#desabilita todas as CPUs menos uma (a CPU0)
cpunum=1
while [ $cpunum -lt $cpus ];
do
	echo 'desabilitando CPU'$cpunum
	echo 0 > /sys/devices/system/cpu/cpu$cpunum/online
	let cpunum=cpunum+1
done

#espera um pouco para ter certeze de que ao rodar o programa
#as CPUs vão estar desabilitadas
sleep 10s

echo 'rodando o calculos com uma thread (sem HT)'
lscpu --extended
#roda o programa com uma única CPU
./desafio2

#habilita somente a CPU virtual da CPU0 (isto é, habilita a HT da CPU0)
echo 'habilitando CPU'$cpu0ht
echo 1 > /sys/devices/system/cpu/cpu$cpu0ht/online

#espera um pouco
sleep 10s

echo 'rodando o calculos com duas threads (uma física e uma HT)'
lscpu --extended
#roda o programa com duas threads (uma thread física e uma thread HT)
./desafio2 2

#habalita novamente as CPUs
cpunum=1
while [ $cpunum -lt $cpus ];
do
	echo 'habilitando CPU'$cpunum
	echo 1 > /sys/devices/system/cpu/cpu$cpunum/online
	let cpunum=cpunum+1
done
#fim dos testes e as CPUs estão de volta online =]
echo 'fim'
