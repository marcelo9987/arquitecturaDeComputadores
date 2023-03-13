#!/bin/bash
# Solicitamos un nodo con 64 cores y 256 GB de memoria durante 2 horas
SBATCH -n 1 -c 64 -t 02:00:00 --mem=256G
# Ponemos nombre a nuestro trabajo para poder identificarlo.
# ATENCIÓN - Debes sustituir el NN por el número de equipo.
SBATCH --job-name p1acg03

# Sustituir los valores de Di y Li por los calculados para la realización de la práctica.

D1=$((2 ** 0))
D2=$((2 ** 1))
D3=$((2 ** 2))
D4=$((2 ** 5))
D5=$((2 ** 8))


# Para el portátil de Marcelo:
#S1=$((32768/64))
#S2=$((262144/64))

# Para el Finisterrae III:
S1=$((49152/64))
S2=$((1310720/64))

L1=$(($S1 / 2))
L2=$(($S1 + $S1 / 2))
L3=$(($S2 / 2))
L4=$(($S2 * 3 / 4))
L5=$(($S2 * 2))
L6=$(($S2 * 4))
L7=$(($S2 * 8))

gcc acp1.c -o acp1 -msse3 -O0

mkdir -p resultados

for i in {1..10}
#for i in {1}
do
  echo "D:, L:, R:, ciclos:, accesos:, ciclos/acc:" > resultados/datos.$i.csv
  #echo "D:, L: , R: , ciclos: , accesos: , ciclos/acc:"
	#for D in {$D1,$D2,$D3,$D4,$D5}
	for D in {$D1,$D2,$D3,$D4,$D5}
	do
		for L in {$L1,$L2,$L3,$L4,$L5,$L6,$L7}
		do
		 # echo "#### Ejecución $i con D=$D y L=$L"
			./acp1 $D $L >> resultados/datos.$i.csv
		done
	done
done


#formula de excel en español que busca el segundo numero más pequeños de una celda en varias páginas distintas las hojas se llaman datos $numero y la celda es F2:
=MINIFS(F2;datos1!$A$2:$A$1000;datos1!$B$2:$B$1000;datos1!$C$2:$C$1000;datos1!$D$2:$D$1000;datos1!$E$2:$E$1000;datos1!$F$2:$F$1000;datos1!$G$2:$G$1000;datos1!$H$2:$H$1000;datos1!$I$2:$I$1000;datos1!$J$2:$J$1000;datos1!$K$2:$K$1000;datos1!$L$2:$L$1000;datos1!$M$2:$M$1000;datos1!$N$2:$N$1000;datos1!$O$2:$O$1000;datos1!$P$2:$P$1000;datos1!$Q$2:$Q$1000;datos1!$R$2:$R$1000;datos1!$S$2:$S$1000;datos1!$T$2:$T$1000;datos1!$U$2:$U$1000;datos1!$V$2:$V$1000;datos1!$W$2:$W$1000;datos1!$X$2:$X$1000;datos1!$Y$2:$Y$1000;datos1!$Z$2:$Z$1000;datos1!$AA$2:$AA$1000;datos1!$AB$2:$AB$1000;datos1!$AC$2:$AC$1000;datos1!$AD$2:$AD$1000;datos1!$AE$2:$AE$1000;datos1!$AF$2:$AF$1000;datos1!$AG$2:$AG$1000;datos1!$AH$2:$AH$1000;datos1!$AI$2:$AI$1000;datos1!$AJ$2:$AJ$1000;datos1!$AK$2:$AK$1000;datos1!$AL$2:$AL$1000;
