#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Masina {
    int id;
    char* producator;
    int nrUsi;
    float pret;
};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini) {
    struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
    for (int i = 0; i < *nrMasini; i++) {
        aux[i] = masini[i];
    }
    aux[*nrMasini] = m;
    (*nrMasini)++;
    if (masini != NULL)
        free(masini);

    return aux;
}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini) {
    FILE* file = fopen(numeFisier, "r");
    if (file == NULL) {
        printf("Eroare deschidere fisier!\n");
        return NULL;
    }

    char buffer[100];
    char delimitare[] = ",\n";
    struct Masina* masini = NULL;
    (*nrMasini) = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char* element = strtok(buffer, delimitare);

        struct Masina m;
        m.id = atoi(element);

        element = strtok(NULL, delimitare);
        m.producator = malloc(strlen(element) + 1);
        strcpy(m.producator, element);

        element = strtok(NULL, delimitare);
        m.nrUsi = atoi(element);

        element = strtok(NULL, delimitare);
        m.pret = atof(element);

        masini = adaugareInVector(masini, m, nrMasini);
    }

    fclose(file);
    return masini;
}

struct Masina* masiniMulteUsi(struct Masina* masini, int* nrMasini) {
    int nrMasiniNoi = 0;
    for (int i = 0; i < *nrMasini; i++) {
        if (masini[i].nrUsi > 2) {
            nrMasiniNoi++;
        }
    }

    struct Masina* masiniUsi = malloc(sizeof(struct Masina) * nrMasiniNoi);
    int j = 0;

    for (int i = 0; i < *nrMasini; i++) {
        if (masini[i].nrUsi > 2) {
            masiniUsi[j] = masini[i];
            j++;
        }
    }

    return masiniUsi;
}

void afisareMatrice(struct Masina** matrice, int nrLinii, int* nrColoane) {
    for (int i = 0; i < nrLinii; i++) {
        for (int j = 0; j < nrColoane[i]; j++) {
            printf("id: %d, producator: %s, nrUsi: %d, pret: %.2f\n", matrice[i][j].id, matrice[i][j].producator, matrice[i][j].nrUsi, matrice[i][j].pret);
        }
        printf("\n");
    }
}

void citireMatrice(const char* numeFisier, struct Masina*** matrice, int nrLinii, int** nrColoane) {
    FILE* file = fopen(numeFisier, "r");

    if (file == NULL) {
        printf("Eroare deschidere fisier!\n");
        return;
    }

    char buffer[100];
    char delimitare[] = ",\n";

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char* element = strtok(buffer, delimitare);

        struct Masina m;
        m.id = atoi(element);

        element = strtok(NULL, delimitare);
        m.producator = malloc(sizeof(char) * (strlen(element) + 1));
        strcpy(m.producator, element);

        element = strtok(NULL, delimitare);
        m.nrUsi = atoi(element);

        element = strtok(NULL, delimitare);
        m.pret = atof(element);

        (*matrice)[m.nrUsi - 2] = adaugareInVector((*matrice)[m.nrUsi - 2], m, &((*nrColoane)[m.nrUsi - 2]));
    }

    fclose(file);
}

float pretMediu(struct Masina** matrice, int nrLinii, int* nrColoane, int nrUsi) {
    if (nrUsi < 2 || nrUsi > 4)
        return 0;

    float pretTotal = 0;
    int index = nrUsi - 2;

    if (nrColoane[index] == 0)
        return 0;

    for (int i = 0; i < nrColoane[index]; i++) {
        pretTotal += matrice[index][i].pret;
    }

    return pretTotal / nrColoane[index];
}

struct Masina cautaMasinaDupaId(struct Masina** matrice, int nrLinii, int* nrColoane, int id) {
    for (int i = 0; i < nrLinii; i++) {
        for (int j = 0; j < nrColoane[i]; j++) {
            if (matrice[i][j].id == id) {
                return matrice[i][j];
            }
        }
    }

    struct Masina m = { -1, NULL, -1, -1 };
    return m;
}

void dezalocareMatrice(struct Masina*** matrice, int nrLinii, int** nrColoane) {
    for (int i = 0; i < nrLinii; i++) {
        for (int j = 0; j < (*nrColoane)[i]; j++) {
            free((*matrice)[i][j].producator);
            (*matrice)[i][j].producator = NULL;
        }
        free((*matrice)[i]);
    }

    free((*nrColoane));
    *nrColoane = NULL;
    free((*matrice));
    *matrice = NULL;
}

int main() {
    struct Masina** matrice;
    int nrLinii = 3;
    int* nrColoane;

    nrColoane = (int*)malloc(sizeof(int) * nrLinii);
    matrice = (struct Masina*)malloc(sizeof(struct Masina) * nrLinii);

    for (int i = 0; i < nrLinii; i++) {
        nrColoane[i] = 0;
        matrice[i] = NULL;
    }

    citireMatrice("Masini.txt", &matrice, nrLinii, &nrColoane);

    afisareMatrice(matrice, nrLinii, nrColoane);

    // exemplu de apel al functiilor
    float pretMediuMasini2Usi = pretMediu(matrice, nrLinii, nrColoane, 2);
    printf("Pretul mediu pentru masinile cu 2 usi: %.2f\n", pretMediuMasini2Usi);

    // exemplu de cautare masina dupa id
    int idCautat = 2;
    struct Masina masinaCautata = cautaMasinaDupaId(matrice, nrLinii, nrColoane, idCautat);

    if (masinaCautata.id != -1) {
        printf("Masina cu id %d gasita:\n", idCautat);
        printf("id: %d, producator: %s, nrUsi: %d, pret: %.2f\n", masinaCautata.id, masinaCautata.producator, masinaCautata.nrUsi, masinaCautata.pret);
    }
    else {
        printf("Masina cu id %d nu a fost gasita\n", idCautat);
    }

    // eliberare de memorie
    dezalocareMatrice(&matrice, nrLinii, &nrColoane);

    return 0;
}