#!/usr/bin/env bash
cpus=0
cpus=$(lscpu | grep ^'CPU(s):' | cut -s -d ' ' -f2-)

#cat /sys/devices/system/cpu/cpu*/topology/thread_siblings_list
#for cpunum in $(cat /sys/devices/system/cpu/cpu*/topology/thread_siblings_list | cut -s -d, -f2- | tr ',' '\n' | sort -un)

#desabilita todas as CPUs menos uma 
cpunum=1
while [ $cpunum -lt $cpus ];
do
	echo $cpunum
	echo 0 > /sys/devices/system/cpu/cpu$cpunum/online
	let cpunum=cpunum+1
done

#TODO colocar um argumento -ht para indicar quando o programa
#	deve rodar com uma ou com duas threads

#TODO rodar o programa (single thread)
#./desafio2


#cat /sys/devices/system/cpu/cpu0/topology/thread_siblings_list | cut -s -d- -f2-

#habilitar somente a CPU virtual da CPU 0 (isto é, habilita a HT da CPU 0)
cpu0ht=$(cat /sys/devices/system/cpu/cpu0/topology/thread_siblings_list | cut -s -d- -f2-)
echo $cpu0ht
echo 1 > /sys/devices/system/cpu/cpu$cpunum/online

#TODO rodar o programa (multi (2) thread)
#./desafio2 -ht


#habalita novamente as CPUs
#cpunum=1
#while [ $cpunum -lt $cpus ];
#do
	#echo 1 > /sys/devices/system/cpu/cpu$cpunum/online
#	let cpunum=cpunum+1
#done

#rodar o programa (multi thread)
