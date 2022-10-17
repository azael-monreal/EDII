#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
	int dato;
	struct nodo* sig;
	struct nodo* ant;
} * NODO;

typedef struct {
	NODO head;
	NODO tail;
} LISTAD;

void init (LISTAD*);
int creaNodo (NODO*, int);
void capturaLista (LISTAD*);
int insertaIn (LISTAD*, int);
int insertaFn (LISTAD*, int);
int eliminaIn (LISTAD*, int*);
int eliminaFn (LISTAD*, int*);
void imprimeIn (LISTAD);
void imprimeFn (LISTAD);

int main ()
{
	LISTAD listad;

	init (&listad);
	capturaLista (&listad);

	imprimeIn (listad);
	printf ("\n");
	imprimeFn (listad);
	printf ("\n");

	int temp;

	eliminaIn (&listad, &temp);
	imprimeIn (listad);
	printf ("\n");

	eliminaFn (&listad, &temp);
	imprimeIn (listad);
	printf ("\n");

	eliminaIn (&listad, &temp);
	imprimeIn (listad);
	printf ("\n");
}

void init (LISTAD* q) { q->head = q->tail = NULL; }

int creaNodo (NODO* nuevo, int dato)
{
	int res = 0;
	*nuevo = (NODO) malloc (sizeof (struct nodo));
	if (*nuevo) {
		(*nuevo)->dato = dato;
		(*nuevo)->sig = NULL;
		(*nuevo)->ant = NULL;
		res = 1;
	}
	return (res);
}

void capturaLista (LISTAD* lista)
{
	int res, dato, resp, pos;
	do {
		printf ("inicio o final (1 - si/0 - no)\n");
		scanf ("%d", &pos);
		printf ("Dato: ");
		scanf ("%d", &dato);
		res = (pos) ? insertaIn (lista, dato) : insertaFn (lista, dato);
		if (res) {
			printf ("Otro dato (1 - si/0 - no)? ");
			scanf ("%d", &resp);
		} else
			printf ("Dato no ingresado\n");
	} while (res && resp);
}

int insertaIn (LISTAD* lista, int dato)
{
	int res;
	NODO nuevo;
	res = creaNodo (&nuevo, dato);
	if (res) {
		if (!lista->head)
			lista->tail = nuevo;
		else
			lista->head->ant = nuevo;
		nuevo->sig = lista->head;
		lista->head = nuevo;
	}
	return (res);
}

int insertaFn (LISTAD* lista, int dato)
{
	int res;
	NODO nuevo;
	res = creaNodo (&nuevo, dato);
	if (res) {
		if (!lista->tail)
			lista->head = nuevo;
		else
			lista->tail->sig = nuevo;
		nuevo->ant = lista->tail;
		lista->tail = nuevo;
	}
	return (res);
}

int eliminaIn (LISTAD* lista, int* r)
{
	int res = 0;
	NODO temp;
	if (lista->head) {
		temp = lista->head;
		lista->head = temp->sig;
		lista->head->ant = NULL;
		free (temp);
		res = 1;
	}
	return (res);
}

int eliminaFn (LISTAD* lista, int* r)
{
	int res = 0;
	NODO temp;
	if (lista->tail) {
		temp = lista->tail;
		lista->tail = temp->ant;
		lista->tail->sig = NULL;
		free (temp);
		res = 1;
	}
	return (res);
}

void imprimeIn (LISTAD lista)
{
	while (lista.head) {
		printf ("%d ", lista.head->dato);
		lista.head = lista.head->sig;
	}
}

void imprimeFn (LISTAD lista)
{
	while (lista.tail) {
		printf ("%d ", lista.tail->dato);
		lista.tail = lista.tail->ant;
	}
}
