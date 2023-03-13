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
//#define L1 64

#define S2 20480
//#define L2 64
#define kTamanoLineaCache 64

#define kTotalRepeticiones 10

//todo:
//Tomar la medida de ciclos (utilizando las rutinas que aparecen en el programa C adjunto) totales de las kTotalRepeticiones
//repeticiones (no incluir la impresión de los resultados en esta medida), y obtener el número de ciclos medio
//por acceso a memoria.
//}



/**
 * Calcula el valor de R para los casos en que i_exponenteDeD sea menor a 3 (2^i_exponenteDeD < 8) y por tanto debamos calcular la distribución de las líneas
 * para cada valor de i_exponenteDeD hay que tomar 7 medidas(L: 0.5*S1, 1.5*S1, 0.5*S2, 0.75*S2, 2*S2,4*S2, 8*S2)
 * @param i_exponenteDeD
 * @return
 */
int calcular_R_casoEspecial(int i_exponenteDeD, int L)
{
    //Hay que ver de donde saco 8 xd que no me acuerdo, pero se que es asi(A ver se que es el tamaño de línea pero no me acuerdo de donde sale)
    //sustituir 8 por valor calculado todo
    int R = ceil((8 * L) / i_exponenteDeD) - 1;
    return R;
    
    
}

/**
 * @brief Calcula el valor de R para los casos en que i_exponenteDeD sea mayor o igual a 3 (2^i_exponenteDeD >= 8)
 * @param i_exponenteDeD   Exponente de D
 * @return 
 */
int calcular_R(int i_exponenteDeD)
{
    //Total de líneas cache a las que hay que acceder
    int ai_valoresDeL[] = {(int) 0.5 * S1, (int) 1.5 * S1, (int) 0.5 * S2, (int) 0.75 * S2, 2 * S2, 4 * S2, 8 * S2};
    
    int R = 0;
    if (i_exponenteDeD < 3)
    {
        switch (i_exponenteDeD)
        {
            case 0:
            case 1:
            case 2:
                //calcular_R_casoEspecial
                //hacemos con el primer ai_valoresDeL(ai_valoresDeL[0]) todo array de ai_valoresDeL
                R = calcular_R_casoEspecial(i_exponenteDeD, ai_valoresDeL[0]);
                break;
            default:
                fprintf(stdout, "[error]: tamaño incorrecto");
                exit(-1);
                break;
            
            
        }
    } else
    {
        R = ai_valoresDeL[0];
    }
    return R;
}

/**
 * @brief Genera un número aleatorio en el intervalo [d_min, d_max)
 * @param d_min 
 * @param d_max 
 * @return 
 */

double generarNumeroAleatorio(double d_min, double d_max)
{
    double rango = (d_max - d_min);
    double div = RAND_MAX / rango; 
    int aleatorio;
    
    do
    {
        aleatorio = rand();
    } while (aleatorio == RAND_MAX); //Así evito dar el valor máximo (Se ha pedido intervalo abierto por la derecha)
    
    return d_min + (aleatorio / div); 
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stdout, "[error]: número de argumentos incorrecto");
        exit(-1);
    }
    
    /*
     * Repetir kTotalRepeticiones veces la operación de reducción y guardar el resultado en S[]
     */
    double S[kTotalRepeticiones];
    
    int i_exponenteDeD = atoi(argv[1]); //exponente de D
    int D = 1 << i_exponenteDeD; //2^i_exponenteDeD
  
    
    int R = calcular_R(i_exponenteDeD);
    
    srand(time(NULL));
    
    
    //Repetir kTotalRepeticiones veces
    for (int repeticion = 0; repeticion < kTotalRepeticiones; ++repeticion)
    {
        /**
        * 1-RESERVAR MEMORIA DINÁMICA PARA EL VECTOR A[]
        */
    
        
        double *A = (double *) _mm_malloc(R * D * sizeof(double), kTamanoLineaCache);
        
        
        int *ind = (int *) _mm_malloc(R * sizeof(int), kTamanoLineaCache); //Reservamos memoria para el vector ind[]
        /*for (int i_indice_asignacionVariableIndice = 0;i_indice_asignacionVariableIndice < R; i_indice_asignacionVariableIndice++)
        {
            ind[R] = i_indice_asignacionVariableIndice * i_exponenteDeD;
        }*/ 
        
        for (int i = 0; i < R; ++i)
        {
            ind[i] = i * i_exponenteDeD;
        }
        
        // FASE DE CALENTAMIENTO (INICIO)
        
        //Recorremos A y le asignamos valores aleatorios
        for (int i = 0; i < R; ++i)
        {
            A[ind[i]] = generarNumeroAleatorio(1, 2); //Generamos un número aleatorio en el intervalo [1,2)
        }
        
        // FASE DE CALENTAMIENTO (FIN)
        
        //Sumamos los valores de A y los guardamos en S, hay que ir imprimiendo S todo
        for (int i = 0; i < R; ++i)
        {
            S[repeticion] += A[ind[i]];
        }
        
        //Imprimimos S[]
        printf("El valor de S en la repeticion %d es %f", repeticion, S[repeticion]);
        
        _mm_free(A);
        _mm_free(ind);
    }
    
}



