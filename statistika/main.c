#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <math.h>
#include <stdarg.h>

typedef struct{
    long double(*p)(int pocet,...);
    char typ; //identifikace funkce (prumer, median, rozptyl)
} tfce ;

typedef struct{
    long double(*p)(int pocet,...);
    char *name;
} nfce ;


long double prumer(int pocet, ...) {
    int i;
    long double suma = 0.0L;
    double arg;
    va_list args;

    va_start(args, pocet);
    for (i=0; i<pocet; i++) {
        arg = va_arg(args, double);
        suma += arg;
    }
    va_end(args);
    return suma/pocet;
}

static int compare_double (const void *pa,  const void *pb) {
    return *(double*)pa > *(double*)pb ? 1 : -1;
}

long double median(int pocet, ...) {
    int i;
    long double med;
    double *hodnoty;
    va_list args;

    va_start(args, pocet);
    hodnoty = malloc(sizeof(double)*pocet);
    for (i=0; i<pocet; i++) {
        hodnoty[i] = va_arg(args, double);
    }
    va_end(args);

    qsort(hodnoty, pocet, sizeof(double), compare_double);

    if (pocet % 2) { //liche
        med = hodnoty[pocet/2];
    }
    else { //sude
        i = pocet/2;
        med = (hodnoty[i-1] + hodnoty[i]) /2;
    }
    free(hodnoty);
    return med;
}
/* Rozptyl lze vypočítat jednodušeji podle tzv. výpočtového vzorce,
 který říká, že rozptyl je roven rozdílu aritmetického průměru druhých mocnin hodnot
 a druhé mocniny jejich aritmetického průměru. */
long double rozptyl(int pocet, ...) {
    int i;
    long double suma = 0.0L, suma2 = 0.0L, prum;
    va_list args;
    double arg;

    va_start(args, pocet);
    for (i=0; i<pocet; i++) {
        arg = va_arg(args, double);
        suma += arg;
        suma2 += arg*arg;
    }
    va_end(args);
    prum = suma/pocet;
    return suma2/pocet - prum*prum;
}

static tfce fce [] = { {prumer, 'p'}, {median, 'm'}, {rozptyl, 'r'}};

static
char *mesice [] =  {    "leden",
                        "unor",
                        "brezen",
                        "duben",
                        "kveten",
                        "cerven",
                        "cervenec",
                        "srpen",
                        "zari",
                        "rijen",
                        "listopad",
                        "prosinec"};

double udaje [] = {     9.7,
                        9.6,
                        9.2,
                        8.6,
                        8.2,
                        8.1,
                        8.2,
                        8.2,
                        8.0,
                        7.9,
                        8.0,
                        8.6 };


void statistika_roku(int pocet, tfce* fce, double *udaje) {
    int i;
    int mesicu = sizeof mesice/sizeof mesice[0];
    long double ld;

    printf("vyvoj nezamestnanosti v roce 2011 byl: \n");

    for (i = 0; i < mesicu; i++){
        printf("%s: %g\n", mesice[i], udaje[i]);
    }

    for (i = 0; i < pocet; i++){
        switch (fce[i].typ) {
            case 'p': printf("\nprumer je: ");
                break;
            case 'm': printf("median je: ");
                break;
            case 'r': printf("rozptyl je: ");
                break;
        }
        ld = fce[i].p(mesicu, udaje[0], udaje[1], udaje[2], udaje[3], udaje[4], udaje[5], udaje[6], udaje[7], udaje[8], udaje[9], udaje[10], udaje[11]);
        printf("%Lg\n", ld);
    }

    }



int main()
{
    statistika_roku(sizeof fce/sizeof *fce, fce, udaje);
    return 0;
}
