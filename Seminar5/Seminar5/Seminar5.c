#include <stdio.h>
#include <malloc.h>
//lista simpla: necontigua, parcurgere secventiala
//pana la test: lista simpla, lista dubla, hashtable

typedef struct CafeneauaMea Cafenea;
typedef struct Nod Nod;

struct CafeneauaMea {
    char* nume;
    int nrLocuri;
    float suprafata;
};

struct Nod {
    Cafenea info;
    Nod* next;
};

Cafenea initializareCafenea(const char* nume, int nrLocuri, float suprafata) {
    Cafenea cafenea;
    cafenea.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(cafenea.nume, nume);
    cafenea.nrLocuri = nrLocuri;
    cafenea.suprafata = suprafata;

    return cafenea;
}

Nod* inserareInceput(Cafenea cafenea, Nod* cap) {
    Nod* nou = malloc(sizeof(Nod));
    nou->next = cap;
    nou->info = initializareCafenea(cafenea.nume, cafenea.nrLocuri, cafenea.suprafata);
    return nou;
}

void afisareCafenea(Cafenea cafenea) {
    printf("Denumire: %s, Nr scaune: %i, Suprafata: %.2f\n", cafenea.nume, cafenea.nrLocuri, cafenea.suprafata);
}

void afisareCafenele(Nod* lista) {
    while (lista != NULL) {
        afisareCafenea(lista->info);
        lista = lista->next;
    }
}

//functie care ne da numele cafenelei cu densitatea cea mai mica
char* numeCafeneaDensitateMinima(Nod* lista) {
    if (lista != NULL) {
        if (lista->info.suprafata != 0) {
            float minim = lista->info.nrLocuri / lista->info.suprafata;
            Nod* adresa = lista;
            lista = lista->next;
            while (lista != NULL) {
                if (lista->info.nrLocuri / lista->info.suprafata < minim) {
                    minim = lista->info.nrLocuri / lista->info.suprafata;
                    adresa = lista;
                }
                //deplasare
                lista = lista->next;
            }
            char* nume = malloc(sizeof(char) * (strlen(adresa->info.nume) + 1));
            strcpy(nume, adresa->info.nume);
            return nume;
        }
    }
}

void stergereLista(Nod** nod) { //** pentru ca il modificam
    while (*nod != NULL) {
        Nod* aux;
        aux = *nod;
        *nod = (*nod)->next;
        free(aux->info.nume);
        free(aux);
    }
    *nod = NULL;
}

void inserareFinal(Nod** lista, Cafenea cafenea) {
    if (*lista == NULL) {
        *lista = inserareInceput(cafenea, *lista);
    }
    else {
        Nod* curent = *lista;
        while (curent->next != NULL) {
            curent = curent->next;
        }
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->info = initializareCafenea(cafenea.nume, cafenea.nrLocuri, cafenea.suprafata);
        nou->next = NULL;
        curent->next = nou;
    }
}

void main() {
    Nod* cap = NULL;
    Cafenea cafenea1 = initializareCafenea("Tucano", 12, 20);
    Cafenea cafenea2 = initializareCafenea("Teds", 22, 40);
    Cafenea cafenea3 = initializareCafenea("Urban", 19, 35);
    Cafenea cafenea4 = initializareCafenea("Starbucks", 25, 43);

    //unde putem sa inseram elemente?
    //inceput, mijloc, final
    //mijloc: mai multe variante

    cap = inserareInceput(cafenea1, cap);
    cap = inserareInceput(cafenea2, cap);
    cap = inserareInceput(cafenea3, cap);

    afisareCafenele(cap);

    char* numeMinim = numeCafeneaDensitateMinima(cap);
    printf("Cafeneaua cu densitata minima este: %s\n", numeMinim);

    inserareFinal(&cap, cafenea4);
    afisareCafenele(cap);

    stergereLista(&cap);
    afisareCafenele(cap);

    free(cafenea1.nume);
    cafenea1.nume = NULL;

    free(cafenea2.nume);
    cafenea2.nume = NULL;

    free(cafenea3.nume);
    cafenea3.nume = NULL;

    free(numeMinim);
    numeMinim = NULL;
}