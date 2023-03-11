#include <stdio.h>
#include <stdlib.h>
#include <pmmintrin.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <unistd.h>
//getconf -a --> comando utilizado para saber los tamaños de las caches
/*
 *
 */
#define S1 768
#define L1 64

#define S2 20480
#define L2 64

/**
 * Copia de script tiempos de medida de CV
 */



void start_counter();
double get_counter();
double mhz();


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
    if (result < 0) {
        fprintf(stderr, "Error: counter returns neg value: %.0f\n", result);
    }
    return result;
}

double mhz(int verbose, int sleeptime)
{
    double rate;

    start_counter();
    sleep(sleeptime);
    rate = get_counter() / (1e6*sleeptime);
    if (verbose)
        printf("\n Processor clock rate = %.1f MHz\n", rate);
    return rate;
}
/**
 * Fin de script
 */



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
    //int L[] = {(int) 0.5 * S1, (int) 1.5 * S1, (int) 0.5 * S2, (int) 0.75 * S2, 2 * S2, 4 * S2, 8 * S2};
    //L no puede ser un vector

    /*
     * Repetir 10 veces la opeación de reducción y guardar el resultado en S[]
     */
    double S[10];

    int D = atoi(argv[1]);
    int L = atoi(argv[2]);//está bien, se pasará por consola el valor de entre los 7 posibles que tenemos [todo Especificar al inicio]
    // todo podriamos comprobar si L es alguno de estos L[] = {(int) 0.5 * S1, (int) 1.5 * S1, (int) 0.5 * S2, (int) 0.75 * S2, 2 * S2, 4 * S2, 8 * S2};
    int R = 0;
    if (D < 3) {
        switch (D) {
            case 0:
            case 1:
            case 2:
                //calcular_R
                //hacemos con el primer L(L[0]) todo array de L
                R = calcular_R(D, L);
                break;
            default:
                fprintf(stdout, "[error]: tamaño incorrecto");
                exit(-1);
                break;

        }
    } else {
        R = L;
    }

    srand((time(NULL)));//?


    //Medida de los ciclos
    double ck;
    start_counter();
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

        // Liberamos memoria
        _mm_free(A);
        free(indice);
    }

    ck=get_counter();

    printf("\n Clocks=%1.10lf \n",ck);

    /* Esta rutina imprime a frecuencia de reloxo estimada coas rutinas start_counter/get_counter */
    mhz(1,1);
    //fin de la medida de los ciclos

    for (int i = 0; i < 10; ++i) {
        //Imprimimos S[]
        printf("El valor de S en la repeticion %d es %f",i, S[i]);
    }

    return 0;

}

