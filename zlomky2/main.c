#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* Napište v jazyku C funkci zlomek soucet(const char *vstup),
 která čte ze vstupního textového souboru vstup zlomky (resp. dvojice celých čísel),
  vypočítává a vrací součet všech zlomků zapsaných ve vstupním souboru.
   Pro snadnější práci se zlomky si definujte strukturovaný typ zlomek.
   Výsledný zlomek by měl být upraven do základního tvaru.
   Vykrácení zlomku do základního tvaru docílíte vydělením čitatele i jmenovatele jejich největším společným dělitelem,
   který můžete určit například použitím Euklidova algoritmu.
*/


// sčítání zlomků
typedef struct Zlomek { int citatel; int jmenovatel; } Zlomek ;

int gcd (int u, int v) {
    int r;

    while ( v != 0) {
    r = u % v;
    u = v;
    v = r;
    }
    return u;
}

Zlomek kraceni_zlomku (Zlomek z){
    int delitel;
    delitel = gcd(z.citatel, z.jmenovatel);
    z.citatel = z.citatel / delitel;
    z.jmenovatel = z.jmenovatel / delitel;
    return z;
}

//makro pro printf zlomku
#define print_zlomek(z) printf("%s: %d/%d\n",#z,(z).citatel, (z).jmenovatel)

Zlomek soucet_zlomku (Zlomek z1, Zlomek z2)
{
    Zlomek vysledek;
    vysledek.jmenovatel = z1.jmenovatel * z2.jmenovatel;
    vysledek.citatel = (z1.citatel * z2.jmenovatel) + (z2.citatel * z1.jmenovatel);
//  return vysledek;
    return kraceni_zlomku (vysledek);
    }

int soucty(const char *vstup) {
  FILE* fvstup;
  int n;
  Zlomek z1;
  Zlomek zsum={0,0};
  int done = 0;
  int rc=0;

  fvstup = fopen(vstup, "r+");
  if ( fvstup == NULL ) {
     perror("otevreni vstupu");
     exit(EXIT_FAILURE);
  }

while (!done) {
	//fgets(buf, 1024, fvstup)  ;
	//printf("%s \n", buf)  ; continue;
	n = fscanf(fvstup, "%d%*[ \t/]%d", &z1.citatel, &z1.jmenovatel);
	switch (n) {
	case 2: //zlomek
	    //print_zlomek(z1);//ladeni
	    //pokud jdeme poprve: zsum inicializujem na z1, jinak pricitame
	    zsum = (zsum.citatel==0) ? z1 : soucet_zlomku(z1, zsum);
	    break;
	case EOF:
	     done = 1; break;
	case 0:
	default:
	     fprintf(stderr, "err: n = %d\n", n);
	     rc=1;
	     goto err;//spatny format vstupniho souboru!
	     //tady to zpusobi chybu!!! done=1 => zapise zsum treba doprostred fvstup!!!
	     //pripadne pozor na return bez fclose()! pouzijeme goto
	}
  }
  fprintf(fvstup, "soucet je: %d/%d\n", zsum.citatel, zsum.jmenovatel);
err:
  fclose(fvstup);
  return rc;
}

/*int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("usage: %s vstup\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    soucty(argv[1]);
    return 0;//EXIT_SUCCESS
}*/

int main ()
{
	soucty("vstup.txt");
    return 0;

}
