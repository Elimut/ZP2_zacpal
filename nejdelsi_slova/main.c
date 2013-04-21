#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>


int getWord (FILE* fin, char** pSlovo) {
    int c;
    int i = 0;
    char* slovo = *pSlovo;
    //přeskočit nealfanumerické znaky
    while (!isalpha(c = getc(fin)) && c != EOF); //prázdné body

    if (c == EOF) {
        return 0;
    }
    else {
        slovo[i] = c;
        i++;
    }

    while (isalpha(c = getc(fin))) {
        slovo[i] = c;
        i++;
    }
    slovo[i] = '\0';

    return i;
}

int topten (int pocet, char* zebricek[], char* slovo) {
    int len = strlen(slovo);
    int i, j;

    for (i=0; i<pocet ;i++) {
    //   printf("i = %d %s\n", i, slovo);
        if (zebricek[i] == NULL) {
            zebricek[i] = strdup(slovo);
            break;
        }
        else if  (len > (strlen(zebricek[i]))) {  // nove slovo > stare slovo
            j = pocet-1; // nejslabsi z kola ven!
            if (zebricek[j] != NULL) {
                free(zebricek[j]);
            }
            for (; j>i; j--) {
                    zebricek[j] = zebricek[j-1];
            }
            zebricek[i] = strdup(slovo);
            break;
        }
    }
    return i;
}


int main (int argc, char* argv[])
{
    char** zebricek;
    int i;

    FILE* fin;
    int pocet = 10;  //defaultní hodnota, pokud bychom nedostali argument

    char* slovo = malloc(1024);
    if (argc<2) {
        printf("usage: %s soubor ?pocet?\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc>2) {
    pocet = atoi(argv[2]);  //strtol - umi nahlasit i chybu
    //nebo pouzit sscanf...
    }

 //   setlocale(LC_ALL, "");  - pro znaky ceske abecedy, nefunguje ale

    fin = fopen(argv[1], "rt");
    if (fin == NULL) {
    perror("openerror");
    exit(EXIT_FAILURE);


    }
    #if 0
    while (getWord(fin, &slovo)) {
       puts(slovo); //vypíše všechno
    }
    #endif


    zebricek = calloc(pocet, sizeof(char*));
    while ( getWord(fin, &slovo)) {
       // puts(slovo);
       topten(pocet, zebricek, slovo);
    }
    for (i=0; i<pocet; i++){
        printf("%s\n", zebricek[i]);
    }

    return 0;
}
