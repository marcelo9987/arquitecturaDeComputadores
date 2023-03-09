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

/**
 * Calculamos el valor de R para los casos en que D sea menor a 3 (2^D < 8) y por tanto debamos calcular la distribución de las líneas
 * para cada valor de D hay que tomar 7 medidas(L: 0.5*S1, 1.5*S1, 0.5*S2, 0.75*S2, 2*S2,4*S2, 8*S2)
 * @param D
 * @return
 */
int *calcular_R(double D, int L[7])
{
    //Hay que ver de donde saco 8 xd que no me acuerdo, pero se que es asi(A ver se que es el tamaño de línea pero no me acuerdo de donde sale)
    //sustituir 8 por valor calculado todo
    int R[7];
    for (int i = 0; i < 7; ++i) {
        R[i] = ceil((8*L[i])/(int)D)-1;
    }

}


double generarNumero(double min, double max)
{
    double rango = (max - min);
    double div = RAND_MAX / rango;
    int aleatorio;
    while ((aleatorio = rand()) == RAND_MAX); // Así evito dar el valor máximo (Se ha pedido intervalo abierto por la derecha)
    return min + (aleatorio / div);
}

void aleatorizarValores(double *array, const int tamanho_array)
{
    for (int i = 0; i < tamanho_array; i++)
    {
        array[i] = generarNumero(1,2);
    }
}

double media(int R, int D, const double *valores)
{
    double salida = 0;
    for (int i = 0; i < (R - 1); i++)
    {
        salida += valores[R * D];
    }

    salida /= R;
    return salida;
}

//

int main(int argc, char *argv[])
{
    int L[]={(int)0.5*S1,(int)1.5*S1,(int)0.5*S2,(int)0.75*S2,2*S2,4*S2,8*S2};

    int D = atoi(argv[1]);
    //int L = atoi(argv[2]);//L no cambia, no hay que pasarlo por consola
    int R = 0;
    if (D < 3)
    {
        switch (D)
        {
            case 0:
            case 1:
            case 2:
                //calcular_R
                break;
            default:
                fprintf(stdout, "[error]: tamaño incorrecto");
                exit(-1);
                break;


        }
    }
    else
    {
        R = L;
    }

    srand((time(NULL)));

    int  *indice = (int *) malloc(R * sizeof(int)); //todo: LIBERAME!
    for (int i_indice_asignacionVariableIndice =0; i_indice_asignacionVariableIndice < R; i_indice_asignacionVariableIndice++)
    {
        indice[R] = i_indice_asignacionVariableIndice * D;
    }


    double *i_valores =(double *)_mm_malloc((R - 1) * D * sizeof(double), 64);//todo: LIBERAME!

    /**
     * 1-RESERVAR MEMORIA DINÁMICA PARA EL VECTOR A[]
     */
    double *A =(double *)_mm_malloc((R-1) * D * sizeof(double),64);//todo: LIBERAME!

    /** todo
     * 2-OPERACIÓN DE REDUCCION DE SUMA DE PF SOBRE R ELEMENTOS
     * !!! HAY QUE ALMACENAR EL VALOR EN S[]
     * 4-!!!!!!! REPETIR ESTA OPERACION 10 VECES ALMACENANDO LOS VALORES EN S[], hay q ir imprimiendo S[]
     * en 4 MEDIR LOS CICLOS Y OBTENER MEDIA DE CICLOS POR ACCESO A MEMORIA
     */
    aleatorizarValores(i_valores, (R - 1) * D);

    for (int i_indiceParaElIndice=0; i_indiceParaElIndice<R;i_indiceParaElIndice++)//Menudo plot-twist
    {
        A[indice[i_indiceParaElIndice]] = media(R, D, i_valores);//hay que cambiar la forma para refererirse a los distintos valores de A[] TODO
        /**
         * 3-Crear otro vector ind[] para referencias de A[] TODO
         */
    }

    free(i_valores);
    free(A);
    free(indice);


}