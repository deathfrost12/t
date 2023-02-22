#include <stdio.h>
#include <stdlib.h>

#define POCET 10
#define VSTUP "casy.txt"

int casNaSekundy(int h, int m, int s) {
    return h * 3600 + m * 60 + s;
}

/* Funkce precte data ze vstupniho souboru a ulozi je do pole. Vrati do volajici
 funkce pocet prectenych radku, coz je skutecny pocet prvku pole. */
int prectiSoubor(int * pole) {
    FILE * vstup;
    int i = 0;
    int h, m, s;
    if ((vstup = fopen(VSTUP, "r")) == NULL) {
        printf("Chyba otevreni souboru %s.\n", VSTUP);
        return EXIT_FAILURE;
    }
    while (i < POCET && fscanf(vstup, "%d%d%d", &h, &m, &s) != EOF) {
        pole[i] = casNaSekundy(h, m, s);
        i++;
    }
    if (fclose(vstup) == EOF) {
        printf("Chyba zavreni souboru %s.\n", VSTUP);
    }
    return i;
}

void vypisPole(int * pole, int pocet) {
    int i;
    int h, m, s;
    for (i = 0; i < pocet; i++) {
        h = pole[i] / 3600;
        m = (pole[i] - h * 3600) / 60;
        s = pole[i] % 60;
        printf("%4d. %02d:%02d:%02d      ",i+1, h, m, s);
        if (h > 12) {
            h -= 12;
            printf("%02d:%02d:%02d PM\n", h, m, s);
        } else {
            printf("%02d:%02d:%02d AM\n", h, m, s);
        }
    }
    return;
}

void vymenaHodnot(int *a, int *b) {
    /* do promenne pom ulozim hodnotu lezici na adrese ukazatele a */
    int pom = *a;
    *a = *b;
    *b = pom;
    return;
}

void bubbleSort(int * pole, int pocet) {
    int i, j;
    for (i = 0; i < pocet; i++) {
        for (j = 0; j < pocet - i - 1; j++) {
            if (pole[j] > pole[j + 1]) {
                vymenaHodnot(&pole[j], &pole[j + 1]);
            }
        }
    }
    return;
}

int main(int argc, char** argv) {
    int casy[POCET];
    printf("    EVROPSKY CAS    ANGLOSASKY CAS\n");
    printf("----------------------------------\n");
    /* do promenne pocet je vracen skutecny pocet prvku pole */
    int pocet = prectiSoubor(casy);
    if (pocet > 0) {
        bubbleSort(casy, pocet);
        vypisPole(casy, pocet);
    }
    return (EXIT_SUCCESS);
}

