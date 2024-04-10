//liste dublu inlantuite

#include <stdio.h>
#include <malloc.h>
typedef struct Santier Santier;
typedef struct Nod Nod;

struct Santier {
    char* numeProiect;
    int nrMuncitori;
    float suprafata;
};

typedef struct NodLdi NodLdi;
struct NodLdi {
    NodLdi* prev;
    NodLdi* next;
    Santier info;
};

//structura care retine adresele celor doua capete
typedef struct ListaDubla ListaDubla;
struct ListaDubla {
    NodLdi* prim;
    NodLdi* ultim;
};

void inserareInceput(ListaDubla* lista, Santier s) {
    //nod nou
    NodLdi* aux = malloc(sizeof(NodLdi));
    aux->info = s;
    aux->next = lista->prim;
    aux->prev = NULL;

    //NU PARCURGEM LISTA!! AVANTAJ AL LISTEI DUBLE
    if (lista->prim != NULL) {
        lista->prim->prev = aux;
        //lista.prim = aux; o punem la final
    }
    else {
        //lista.prim = aux; o punem la final
        lista->ultim = aux;
        //aux e si primul si ultimul nod
    }
    lista->prim = aux;
}

void afisareSantier(Santier santier)
{
    printf("Santierul %s are %d muncitori si %.2f m^2 suprafata", santier.numeProiect, santier.nrMuncitori, santier.suprafata);
    printf("\n");
}

void afisareLdiDeLaInceput(ListaDubla lista) {
    for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next)
    {
        afisareSantier(nod->info);
    }
    printf("\n");
}

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
    Santier santier;
    santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);
    strcpy(santier.numeProiect, numeProiect);
    santier.nrMuncitori = nrMuncitori;
    santier.suprafata = suprafata;
    return santier;
}

//stergerea santierului dupa un nume dat(unic)
void stergereSantierDupaNume(ListaDubla* lista, const char* nume)
{
    NodLdi* nod = lista->prim;
    while (nod != NULL)
    {
        if (strcmp(nod->info.numeProiect, nume) == 0)
        {
            if (nod->prev == NULL) // daca e primul nod
            {
                if (nod->next == NULL)
                {
                    lista->prim = NULL;
                    lista->ultim = NULL;
                }
                else
                {
                    nod->next->prev = NULL;
                    lista->prim = nod->next;
                }
            }
            else
            {
                if (nod->next == NULL) // daca e ultimul nod
                {
                    nod->prev->next = NULL;
                    lista->ultim = nod->prev;
                }
                else // daca suntem la mijloc, facem doar legaturile
                {
                    nod->prev->next = nod->next;
                    nod->next->prev = nod->prev;
                }
            }
            free(nod->info.numeProiect);
            free(nod);
            //sau pun aici break in loc de else nod=nod->next;
            nod = NULL;
        }
        else
            nod = nod->next;
    }
}

void stergereCompleta(ListaDubla* lista) {
    if (lista != NULL) {
        NodLdi* aux = lista->prim;
        while(aux != NULL){
            
            free(aux->info.numeProiect);
            NodLdi* temp = aux->next;
            free(aux);
            aux = temp;
        }
        //am sters toata lista
        lista->prim = NULL;
        lista->ultim = NULL;
    }
}

float densitate(Santier santier)
{
    if (santier.suprafata != 0)
        return santier.nrMuncitori / santier.suprafata;
    else return 0;
}

//nr total de muncitori din lista
int nrTotalMuncitori(ListaDubla lista)
{
    int s = 0;
    for (NodLdi* i = lista.prim; i != NULL; i = i->next)
        s += i->info.nrMuncitori;
    return s;
}

//nr muncitori de pe santierele care au suprafata mai mica decat un parametru dat
int nrMuncitoriSuprafata(ListaDubla lista, float suprafata)
{
    int s = 0;
    for (NodLdi* i = lista.prim; i != NULL; i = i->next)
    {
        if (i->info.suprafata < suprafata)
            s += i->info.nrMuncitori;
    }

    return s;
}

int main() {
    Santier s1 = initializareSantier("Santier 1", 10, 300);
    Santier s2 = initializareSantier("Santier 2", 12, 400);
    Santier s3 = initializareSantier("Santier 3", 15, 200);
    
    //declarare lista dublu inlantuita
    ListaDubla lista;
    lista.prim = NULL;
    lista.ultim = NULL;

    inserareInceput(&lista, s1);
    inserareInceput(&lista, s2);
    inserareInceput(&lista, s3);
    afisareLdiDeLaInceput(lista);

    
    /*stergereSantierDupaNume(&lista, "Santier 2");
    afisareLdiDeLaInceput(lista);
    stergereSantierDupaNume(&lista, "Santier 1");
    afisareLdiDeLaInceput(lista);
    stergereSantierDupaNume(&lista, "Santier 3");
    afisareLdiDeLaInceput(lista);*/

    int nrMuncitori = nrTotalMuncitori(lista);
    printf("Nr total de muncitori: %d\n", nrMuncitori);

    int nrMuncitoriSup = nrMuncitoriSuprafata(lista, 350);
    printf("Nr de muncitori dupa suprafata: %d\n", nrMuncitoriSup);

    stergereCompleta(&lista);
    afisareLdiDeLaInceput(lista);
}