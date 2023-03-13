#include <stdio.h>
#include <stdlib.h>
#include <pmmintrin.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

//getconf -a --> comando utilizado para saber los tamaños de las caches

#define DEBUG 0

#define kBytesLineaCache 64

// Configuración para el Finisterrae III:
//#define S1 (49152/kBytesLineaCache)
//#define S2 (1310720/kBytesLineaCache)

// Configuración para ubuntu del portátil de Marcelo:
//#define S1 (32768/kBytesLineaCache)
//#define S2 (262144/kBytesLineaCache)



#define kTotalRepeticiones 10

/* Initialize the cycle counter */


static unsigned cyc_hi = 0;
static unsigned cyc_lo = 0;


/* Set *hi and *lo to the high and low order bits of the cycle counter.
Implementation requires assembly code to use the rdtsc instruction. */
void access_counter(unsigned *hi, unsigned *lo)
{
    asm("rdtsc; movl %%edx,%0; movl %%eax,%1" /* Read cycle counter */
            : "=r" (*hi), "=r" (*lo) /* and move results to */
            : /* No input */ /* the two outputs */
            : "%edx", "%eax");
}

/* Record the current value of the cycle counter. */
void start_counter()
{
    access_counter(&cyc_hi, &cyc_lo);
}

/* Return the number of cycles since the last call to start_counter. */
double get_counter()
{
    unsigned ncyc_hi, ncyc_lo;
    unsigned hi, lo, borrow;
    double result;
    
    /* Get cycle counter */
    access_counter(&ncyc_hi, &ncyc_lo);
    
    /* Do double precision subtraction */
    lo = ncyc_lo - cyc_lo;
    borrow = lo > ncyc_lo;
    hi = ncyc_hi - cyc_hi - borrow;
    result = (double) hi * (1 << 30) * 4 + lo;
    if (result < 0)
    {
        fprintf(stderr, "Error: counter returns neg value: %.0f\n", result);
    }
    return result;
}

double mhz(int verbose, int sleeptime)
{
    double rate;
    
    start_counter();
    sleep(sleeptime);
    rate = get_counter() / (1e6 * sleeptime);
    if (verbose)
    {
        printf("\n Processor clock rate = %.1f MHz\n", rate);
    }
    return rate;
}

//todo:
//Tomar la medida de ciclos (utilizando las rutinas que aparecen en el programa C adjunto) totales de las kTotalRepeticiones
//repeticiones (no incluir la impresión de los resultados en esta medida), y obtener el número de ciclos medio
//por acceso a memoria.
//}


/*

 * Calcula el valor de R para los casos en que D sea menor a 3 (2^D < 8) y por tanto debamos calcular la distribución de las líneas
 * para cada valor de D hay que tomar 7 medidas(L: 0.5*S1, 1.5*S1, 0.5*S2, 0.75*S2, 2*S2,4*S2, 8*S2)
 * @param D
 * @return
 */
/*
int calcular_R_casoEspecial(int D, int L)
{
    //todo: revisar
    //Hay que ver de donde saco 8 xd que no me acuerdo, pero se que es asi(A ver se que es el tamaño de línea pero no me acuerdo de donde sale)
    //sustituir 8 por valor calculado
    
    int R = (ceil(kBytesLineaCache/sizeof(double) * L) / D) - 1;
    return R;
    
}*/

/**
 * @brief
 * @param D
 * @return
 */
int calcular_R(int D, int L)
{
    
    int i_bytesSeparacionLecturas = D * sizeof(double);
    
    if (i_bytesSeparacionLecturas < kBytesLineaCache)
    {
        //calcular_R_casoEspecial
        int R = ceil((sizeof(double) * (L - 1)) / D) + 1;
        return R;
    } else
    {
        return L;
    }
}

/*int calcular_R(int D, int L)
{
    //Total de líneas cache a las que hay que acceder
    
    int R = 0;
    if (D < 3)
    {
        switch (D)
        {
            case 0:
            case 1:
            case 2:
                //calcular_R_casoEspecial
                //hacemos con el primer ai_valoresDeL(ai_valoresDeL[0]) todo array de ai_valoresDeL
                R = calcular_R_casoEspecial(D, L);
                break;
            default:
                fprintf(stdout, "[error]: tamaño incorrecto");
                exit(-1);
                break;
            
            
        }
    } else
    {
        R = L;
    }
    return R;
}*/

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
    
    double d_numero = d_min + (aleatorio / div);
    if (rand() >= RAND_MAX / 2)
    {
        return d_numero;
    } else
    {
        return -d_numero;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stdout, "[error]: número de argumentos incorrecto");
        exit(-1);
    }
    
    /*
     * Repetir kTotalRepeticiones veces la operación de reducción y guardar el resultado en S[]
     */
    double S[kTotalRepeticiones];
    
    
    int D = atoi(argv[1]); //distancia entre accesos consecutivos
    
    int L = atoi(argv[2]); //Numero de lineas de cache a acceder
    
    int R = calcular_R(D, L);
    
    srand(time(NULL));
    
    
    /*
    * 1.- RESERVAR MEMORIA DINÁMICA PARA EL VECTOR A[]
    */
    
    double *A = (double *) _mm_malloc((R - 1) * D * sizeof(double), kBytesLineaCache);
    
    int *ind = (int *) _mm_malloc(R * sizeof(int), kBytesLineaCache); //Reservamos memoria para el vector ind[]
    
    for (int i = 0; i < R; ++i)
    {
        ind[i] = i * D;
    }
    
    
    /*
     * 2.- Fase de Calentamiento
     */
    
    //Recorremos A y le asignamos valores aleatorios
    for (int i = 0; i < R; ++i)
    {
        A[ind[i]] = generarNumeroAleatorio(1, 2); //Generamos un número aleatorio en el intervalo [1,2)
    }
    
    
    /*
     * 3.- Medida de tiempos
     */
    
    start_counter();
    
    //Repetir kTotalRepeticiones veces
    for (int repeticion = 0; repeticion < kTotalRepeticiones; ++repeticion)
    {
        
        //Sumamos los valores de A y los guardamos en S, hay que ir imprimiendo S
        for (int i = 0; i < R; ++i)
        {
            S[repeticion] = S[repeticion] + A[ind[i]];
        }
    }
    
    double d_ciclos = get_counter();
    int i_numAccesosMemoria = 4 * R * kTotalRepeticiones; //4 accesos por cada iteración del bucle externo
    double d_ciclosPorAcceso = d_ciclos / i_numAccesosMemoria; //ciclos medios por acceso a memoria
    
    #if DEBUG
    fprintf(stdout, "D: %d, L: %d, R: %d, ciclos: %.0f, accesos: %d, ciclos/acc: %f\n", D, L, R, d_ciclos, i_numAccesosMemoria, d_ciclosPorAcceso);
    #elif !DEBUG
    fprintf(stdout, "%d, %d, %d, %.0f, %d, %f\n", D, L, R, d_ciclos, i_numAccesosMemoria, d_ciclosPorAcceso);
    #endif
    
    
    /*
     * 4.- Imprimir resultados
     */
    
    for (int repeticion = 0; repeticion < kTotalRepeticiones; ++repeticion)
    {
        //Imprimimos S[]
        fprintf(stderr, "El valor de S en la repeticion %d es %f\n", repeticion, S[repeticion]);
    }
    
    
    /*
     * 5.- Liberar memoria
     */
    
    _mm_free(A);
    _mm_free(ind);
    
    
}






