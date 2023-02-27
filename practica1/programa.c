#include <stdio.h>
#include <stdlib.h>
#include <pmmintrin.h>

#define S1 768
#define L1 64

#define S2 20480
#define L2 64


double media(int R, int D, double *valores)
{
    double Salida = 0;
    for (int i = 0; i < (R - 1); i++)
    {
        Salida += valores[R * D];
    }
    
    salida /= R;
    return salida;
}

//

int main(int argc, char *argcv[])
{
//        size_t D = 2;
//        size_t R = 4;
//        double* A = _mm_malloc(R*D*sizeof(double),64);
//        A[0]=1;
//        A[1]=2;
//        A[2]=3;
//        A[3]=4;
//        for(int iter=0;iter<4;iter++)
//        {
//                printf("%lf\n",A[iter]);
//        }
//        _mm_free(A);
}
