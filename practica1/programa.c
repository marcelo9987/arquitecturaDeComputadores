#include <stdio.h>
#include <stdlib.h>
#include <pmmintrin.h>
#include <time.h>
#include <float.h>
#include <math.h>

#define S1 768
#define L1 64

#define S2 20480
#define L2 64

void aleatorizarValores(double *array, const int tamanho_array)
{
    srand(time(NULL));
    
    for (int i = 0; i < tamanho_array; i++)
    {
        
        array[i] = (double) rand() / RAND_MAX;
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
//    int L[]={(int)0.5*S1,(int)1.5*S1,(int)0.5*S2,(int)0.75*S2,2*S2,4*S2,8*S2};
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
    double *A =(double *)_mm_malloc((R-1) * D * sizeof(double),64);
    aleatorizarValores(A,(R-1) * D);
    int indice
    
    
    
}
    

