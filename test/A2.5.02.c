#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
	int info;
	struct nodo* liga;
} * NODO_Q;

void init (NODO_Q*, NODO_Q*);
int creaNodo (NODO_Q*, int);
void capturaCola (NODO_Q*, NODO_Q*);
int enqueue (NODO_Q*, NODO_Q*, int);
void imprimeCola (NODO_Q*);
int dequeue (NODO_Q*, int*);

int main ()
{
	NODO_Q head;
	NODO_Q tail;

	init (&head, &tail);
	capturaCola (&head, &tail);
	printf ("Datos: ");
	imprimeCola (&head);
	printf ("\n");
	printf ("Datos: ");
	imprimeCola (&head);
	printf ("\n");
}
void init (NODO_Q* h, NODO_Q* t) { *h = *t = NULL; }
int creaNodo (NODO_Q* nuevo, int dato)
{
	int res = 0;
	*nuevo = (NODO_Q) malloc (sizeof (struct nodo));
	if (*nuevo) {
		(*nuevo)->info = dato;
		(*nuevo)->liga = NULL;
		res = 1;
	}
	return (res);
}
void capturaCola (NODO_Q* head, NODO_Q* tail)
{
	int res, dato, resp;
	do {
		printf ("Dato: ");
		scanf ("%d", &dato);
		res = enqueue (head, tail, dato);
		if (res) {
			printf ("Otro dato (1 - si/0 - no)? ");
			scanf ("%d", &resp);
		} else
			printf ("Dato no ingresado\n");
	} while (res && resp);
}
int enqueue (NODO_Q* head, NODO_Q* tail, int dato)
{
	int res;
	NODO_Q nuevo;
	res = creaNodo (&nuevo, dato);
	if (res) {
		if (!*head)
			*head = nuevo;
		else
			(*tail)->liga = nuevo;

		nuevo->liga = NULL;
		*tail = nuevo;
	}
	return (res);
}
int dequeue (NODO_Q* cab, int* r)
{
	int res = 0;
	if (*cab) {
		*r = (*cab)->info;
		NODO_Q temp;
		temp = *cab;
		*cab = temp->liga;
		free (temp);
		res = 1;
	}
	return (res);
}

void imprimeCola (NODO_Q* cab)
{
	int d;
	while (dequeue (cab, &d))
		printf ("%d ", d);
}
