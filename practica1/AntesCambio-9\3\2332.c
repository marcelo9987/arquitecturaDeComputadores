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
//    -int -L[]={(int)0.5*S1,(int)1.5*S1,(int)0.5*S2,(int)0.75*S2,2*S2,4*S2,8*S2};

    int D = atoi(argv[1]);
    int L = atoi(argv[2]);
    int R = 0;
    if (D < 3)
    {
        switch (D)
        {
            case 0:
            case 1:
            case 2:
                R = 8 * (int) ceil(L / pow(D, 2));
                R += 1;
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
    double *A =(double *)_mm_malloc((R-1) * D * sizeof(double),64);//todo: LIBERAME!
    aleatorizarValores(i_valores, (R - 1) * D);
    
    for (int i_indiceParaElIndice=0; i_indiceParaElIndice<R;i_indiceParaElIndice++)//Menudo plot-twist
    {
        A[indice[i_indiceParaElIndice]] = media(R, D, i_valores);
    }
    
    free(i_valores);
    free(A);
    free(indice);
    
    
}
