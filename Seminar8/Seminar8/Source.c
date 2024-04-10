#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Mesaj Mesaj;
typedef struct Heap Heap;

struct Mesaj {
	char* text;
	int prioritate;
};

struct Heap {
	Mesaj* vector;
	int dimensiune;
	int dimensiuneTotala;
};

Mesaj initializareMesaj(const char* text, int prioritate) {
	Mesaj m;
	m.text = (char*)malloc(sizeof(char) * (strlen(text) + 1));
	strcpy(m.text, text);
	m.prioritate = prioritate;
	return m;
}

Heap initializareHeap(int dimensiune) {
	Heap h;
	h.vector = (Mesaj*)malloc(sizeof(Mesaj) * dimensiune);
	h.dimensiune = 0;
	h.dimensiuneTotala = dimensiune;
	return h;
}

void afisareMesaj(Mesaj mesaj) {
	printf("Mesajul cu textul %s si prioritatea %d\n", mesaj.text, mesaj.prioritate);
}

void afisareHeap(Heap h) {
	for (int i = 0; i < h.dimensiune; i++) {
		afisareMesaj(h.vector[i]);
	}
}

void filtrareHeap(Heap h, int poz) {
	int pozS = poz * 2 + 1;
	int pozD = poz * 2 + 2;
	//care e pozitia maximului?
	int pozMax = poz; //presupunem ca max este radacina

	if (pozS < h.dimensiune && h.vector[pozS].prioritate > h.vector[pozMax].prioritate) {
		pozMax = pozS;
	}

	if (pozD < h.dimensiune && h.vector[pozD].prioritate > h.vector[pozMax].prioritate) {
		pozMax = pozD;
	}

	if (pozMax != poz) {
		Mesaj aux = h.vector[poz];
		h.vector[poz] = h.vector[pozMax];
		h.vector[pozMax] = aux;
		if (pozMax * 2 + 1 < h.dimensiune) {
			filtrareHeap(h, pozMax);
		}
	}
}

Mesaj ExtragereMesaj(Heap* h) {
	if (h->dimensiune > 0) {
		Mesaj aux = h->vector[0];
		h->vector[0] = h->vector[h->dimensiune - 1];
		h->vector[h->dimensiune - 1] = aux;
		h->dimensiune--;
		for (int i = h->dimensiune / 2; i >= 0; i--) {
			filtrareHeap(*h, i);
		}
		return aux;
	}

}

void afisareHeapTotala(Heap h) {
	for (int i = 0; i < h.dimensiuneTotala; i++) {
		afisareMesaj(h.vector[i]);
	}
}

void dezalocareHeap(Heap* h) {
	if (h->vector != NULL) {
		while (h->dimensiuneTotala > 0) {
			free(h->vector[h->dimensiuneTotala - 1].text);
			h->dimensiuneTotala--;
		}
		free(h->vector);
		h->vector = NULL;
		h->dimensiune = 0;
	}
}

void main() {
	Heap h;
	h = initializareHeap(6);
	h.vector[0] = initializareMesaj("Salut", 3);
	h.vector[1] = initializareMesaj("Salut, ce faci?", 8);
	h.vector[2] = initializareMesaj("Buna", 6);
	h.vector[3] = initializareMesaj("Salut!", 2);
	h.vector[4] = initializareMesaj("Ce mai faci?", 9);
	h.vector[5] = initializareMesaj("Pa!", 4);
	h.dimensiune = 6;

	afisareHeap(h);
	printf("Dupa filtrare: \n");
	for (int i = (h.dimensiune / 2) - 1; i >= 0; i--) {
		filtrareHeap(h, i);
	}
	afisareHeap(h);

	printf("Extragere: \n");
	afisareMesaj(ExtragereMesaj(&h));
	afisareMesaj(ExtragereMesaj(&h));
	afisareMesaj(ExtragereMesaj(&h));
	afisareMesaj(ExtragereMesaj(&h));
	afisareMesaj(ExtragereMesaj(&h));
	afisareMesaj(ExtragereMesaj(&h));

	printf("Afisare totala: \n");
	afisareHeapTotala(h);

	dezalocareHeap(&h);
}