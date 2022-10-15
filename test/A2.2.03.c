#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodoGen {
	char nomTipo[10];
	int tipo;
	void* info;
	struct nodoGen* sigGen;
} * GEN;

void initList (GEN* list) { list = NULL; }

void pushI (GEN* list, int d)
{
	struct nodoGen* temp = (GEN) malloc (sizeof (struct nodoGen));

	strcpy (temp->nomTipo, "entero");
	temp->tipo = 2;
	temp->info = malloc (sizeof (int));
	*(int*) temp->info = d;

	temp->sigGen = *list;

	*list = temp;
}

void pushF (GEN* list, float d)
{
	struct nodoGen* temp = (GEN) malloc (sizeof (struct nodoGen));

	strcpy (temp->nomTipo, "flotante");
	temp->tipo = 3;
	temp->info = malloc (sizeof (float));
	*(float*) temp->info = d;

	temp->sigGen = *list;

	*list = temp;
}

void printList (GEN list)
{
	for (; list; list = list->sigGen) {
		switch (list->tipo) {
			case 1:
				printf ("%c\n", *(char*) list->info);
				break;
			case 2:
				printf ("%d\n", *(int*) list->info);
				break;
			case 3:
				printf ("%f\n", *(float*) list->info);
				break;
		}
	}
	printf ("\n");
}

float sumList (GEN list)
{
	float sum;
	if (!list)
		sum = 0;
	else
		switch (list->tipo) {
			case 2:
				sum = *(int*) list->info + sumList(list->sigGen);
				break;
			case 3:
				sum = *(float*) list->info + sumList(list->sigGen);
				break;
		}

	return sum;
}

int main (void)
{
	GEN lista;
	initList (&lista);

	pushI (&lista, 2);
	pushI (&lista, 9);
	pushF (&lista, 0.3);
	pushF (&lista, 10.4);

	printList (lista);

	printf ("%.2f\n", sumList (lista));

	return 0;
}
