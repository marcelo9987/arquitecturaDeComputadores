#include <stdio.h>
#include <stdlib.h>
#include <pmmintrin.h>
#include <time.h>
#include <float.h>
#include <math.h>
//getconf -a --> comando utilizado para saber los tamaños de las caches
/*
 *
 */
#define S1 768
#define L1 64

#define S2 20480
#define L2 64

//todo {
//Tomar la medida de ciclos (utilizando las rutinas que aparecen en el programa C adjunto) totales de las 10
//repeticiones (no incluir la impresión de los resultados en esta medida), y obtener el número de ciclos medio
//por acceso a memoria.
//}




/**
 * Calculamos el valor de R para los casos en que D sea menor a 3 (2^D < 8) y por tanto debamos calcular la distribución de las líneas
 * para cada valor de D hay que tomar 7 medidas(L: 0.5*S1, 1.5*S1, 0.5*S2, 0.75*S2, 2*S2,4*S2, 8*S2)
 * @param D
 * @return
 */
int calcular_R(double D, int L) {
    //Hay que ver de donde saco 8 xd que no me acuerdo, pero se que es asi(A ver se que es el tamaño de línea pero no me acuerdo de donde sale)
    //sustituir 8 por valor calculado todo
    int R = ceil((8 * L) / (int) D) - 1;
    return R;


}

/**
 * Para generar valores aleatorios para A[]
 * @param argc
 * @param argv
 * @return
 */

double generarNumero(double min, double max) {
    double rango = (max - min);
    double div = RAND_MAX / rango;
    int aleatorio;
    while ((aleatorio = rand()) ==
           RAND_MAX); // Así evito dar el valor máximo (Se ha pedido intervalo abierto por la derecha)
    return min + (aleatorio / div);
}

int main(int argc, char *argv[]) {
    int L[] = {(int) 0.5 * S1, (int) 1.5 * S1, (int) 0.5 * S2, (int) 0.75 * S2, 2 * S2, 4 * S2, 8 * S2};

    /*
     * Repetir 10 veces la opeación de reducción y guardar el resultado en S[]
     */
    double S[10];

    int D = atoi(argv[1]);
    //int L = atoi(argv[2]);//L no cambia, no hay que pasarlo por consola
    int R = 0;
    if (D < 3) {
        switch (D) {
            case 0:
            case 1:
            case 2:
                //calcular_R
                //hacemos con el primer L(L[0]) todo array de L
                R = calcular_R(D, L[0]);
                break;
            default:
                fprintf(stdout, "[error]: tamaño incorrecto");
                exit(-1);
                break;


        }
    } else {
        R = L[0];
    }

    srand((time(NULL)));//?


    //Repetir 10 veces
    for (int repeticion = 0; repeticion < 10; ++repeticion) {
        /**
        * 1-RESERVAR MEMORIA DINÁMICA PARA EL VECTOR A[]
        */
        double *A = (double *) _mm_malloc((R - 1) * D * sizeof(double), 64);//todo: LIBERAME!


        int *indice = (int *) malloc(R * sizeof(int)); //todo: LIBERAME!
        /*for (int i_indice_asignacionVariableIndice = 0;i_indice_asignacionVariableIndice < R; i_indice_asignacionVariableIndice++)
        {
            indice[R] = i_indice_asignacionVariableIndice * D;
        }*/ //NI PUTA IDEA DE QUE COÑO ES ESTO

        for (int i = 0; i < R; ++i) {
            indice[i] = i * D;
        }

        //Recorremos A y le asignamos valores aleatorios
        for (int i = 0; i < R; ++i) {
            A[indice[i]]= generarNumero(0,DBL_MAX);
        }

        //Sumamos los valores de A y los guardamos en S, hay que ir imprimiendo S todo
        for (int i = 0; i < R; ++i) {
            S[repeticion]+=A[indice[i]];
        }

        //Imprimimos S[]
        printf("El valor de S en la repeticion %d es %f",repeticion, S[repeticion]);


        free(A);
        free(indice);
    }

}

