#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
	int info;
	struct nodo* liga;
} * NODO_Q;

typedef struct {
	NODO_Q head;
	NODO_Q tail;
} QUEUE;

void init (QUEUE*);
int creaNodo (NODO_Q*, int);
void capturaCola (QUEUE*);
int enqueue (QUEUE*, int);
void imprimeCola (QUEUE*);
int dequeue (QUEUE*, int*);

int main ()
{
	QUEUE queue;

	init (&queue);
	capturaCola (&queue);
	printf ("Datos: ");
	imprimeCola (&queue);
	printf ("\n");
	printf ("Datos: ");
	imprimeCola (&queue);
	printf ("\n");
}

void init (QUEUE* q) { q->head = q->tail = NULL; }

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

void capturaCola (QUEUE* q)
{
	int res, dato, resp;
	do {
		printf ("Dato: ");
		scanf ("%d", &dato);
		res = enqueue (q, dato);
		if (res) {
			printf ("Otro dato (1 - si/0 - no)? ");
			scanf ("%d", &resp);
		} else
			printf ("Dato no ingresado\n");
	} while (res && resp);
}

int enqueue (QUEUE* queue, int dato)
{
	int res;
	NODO_Q nuevo;
	res = creaNodo (&nuevo, dato);
	if (res) {
		if (!queue->head)
			queue->head = nuevo;
		else
			queue->tail->liga = nuevo;

		queue->tail = nuevo;
		nuevo->liga = NULL;
	}
	return (res);
}

int dequeue (QUEUE* queue, int* r)
{
	int res = 0;
	if (queue->head) {
		*r = (queue->head)->info;
		NODO_Q temp;
		temp = queue->head;
		queue->head = temp->liga;
		free (temp);
		res = 1;
	}
	return (res);
}

void imprimeCola (QUEUE* queue)
{
	int d;
	while (dequeue (queue, &d))
		printf ("%d ", d);
}
