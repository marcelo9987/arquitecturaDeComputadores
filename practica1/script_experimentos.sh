#!/bin/bash
# Solicitamos un nodo con 64 cores y 256 GB de memoria durante 2 horas
#SBATCH -n 1 -c 64 -t 02:00:00 --mem=256G
# Ponemos nombre a nuestro trabajo para poder identificarlo.
# ATENCIÓN - Debes sustituir el NN por el número de equipo.
#SBATCH --job-name p1acgNN

# Sustituir los valores de Di y Li por los calculados para la realización de la práctica.

D1=$((2 ** 0))
D2=$((2 ** 1))
D3=$((2 ** 2))
D4=$((2 ** 3))
D5=$((2 ** 4))

S1=768
S2=20480

L1=$(($S1 / 2))
L2=$(($S1 + $S1 / 2))
L3=$(($S2 / 2))
L4=$(($S2 * 3 / 4))
L5=$(($S2 * 2))
L6=$(($S2 * 4))
L7=$(($S2 * 8))

gcc acp1.c -o acp1 -msse3 -O0

for i in {1..10}
do
	for D in {$D1,$D2,$D3,$D4,$D5}
	do
		for L in {$L1,$L2,$L3,$L4,$L5,$L6,$L7}
		do
		  echo "Ejecución $i con D=$D y L=$L"
			#./acp1 $D $L
		done
	done
done


