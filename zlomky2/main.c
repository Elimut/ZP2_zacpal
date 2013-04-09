#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct {int citatel; int jmenovatel} zlomek ;

int gcd (int u, int v) {
    int r;

    while ( v != 0) {
    r = u % v;
    u = v;
    v = r;
    }
    return u;
}

zlomek soucet(const char *vstup)
{
    int znak = 'a';
	int i = 0;
	zlomek vysledek = {0, 0};
    int temp;

    FILE *f_read = fopen(vstup, "r");
    if (f_read == NULL) {
        if (errno) {
            perror("Chyba pri otevirani");
        }
        fclose(f_read);
        return vysledek;
    }

	int citatel_puvodni = 0;
	int jmenovatel_puvodni = 0;

    while (znak != EOF) {
		i++;
		printf("%i) ", i);
		int citatel_temp = 0;
		int jmenovatel_temp = 0;


		// 1 radek --------------------------------------------------
		while (znak != '/') {
			fscanf(f_read, "%i", &temp);
            citatel_temp = temp;
			znak = fgetc(f_read);
		}
		while (!((znak == '\n') || (znak == EOF) )) {
			fscanf(f_read, "%i", &temp);
            jmenovatel_temp = temp;
            znak = fgetc(f_read);
		}

		// vypocet
		if ((citatel_puvodni == 0) && (jmenovatel_puvodni == 0)) {
			vysledek.citatel = citatel_temp;
			vysledek.jmenovatel = jmenovatel_temp;
		} else {
			vysledek.citatel = (jmenovatel_temp * citatel_puvodni) + (jmenovatel_puvodni * citatel_temp);
			vysledek.jmenovatel = (jmenovatel_puvodni * jmenovatel_temp);
		}

		citatel_puvodni = vysledek.citatel;
		jmenovatel_puvodni = vysledek.jmenovatel;

        // dalsi --------------------------------------------------
        if (znak == '\n') {
            znak = fgetc(f_read);
            if ( isdigit(znak) ) ungetc(znak, f_read);
        }

        printf("%i/%i\n", citatel_temp, jmenovatel_temp);
    }

    fclose(f_read);

	// pred zkracenim
	//printf("%i/%i\n", vysledek.citatel, vysledek.jmenovatel);
	int spolecny_delitel = gcd(vysledek.citatel, vysledek.jmenovatel);
	printf("\nVYSLEDEK PO ZKRACENI: %i/%i: \n", vysledek.citatel/spolecny_delitel,vysledek.jmenovatel/spolecny_delitel);

}
int main ()
{
	soucet("vstup.txt");
    return 0;

}
