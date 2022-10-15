#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
	int info;
	struct nodo* liga;
} * STACK;

void init (STACK*);
int creaNodo (STACK*, int);
void capturaStack (STACK*);
int push (STACK*, int);
void imprimePila (STACK*);
int pop (STACK*, int*);

int main ()
{
	STACK stack;
	init (&stack);
	capturaStack (&stack);
	printf ("Datos: ");
	imprimePila (&stack);
	printf ("\n");
	printf ("Datos: ");
	imprimePila (&stack);
	printf ("\n");
}

void init (STACK* cab) { *cab = NULL; }

int creaNodo (STACK* nuevo, int dato)
{
	int res = 0;
	*nuevo = (STACK) malloc (sizeof (struct nodo));
	if (*nuevo) {
		(*nuevo)->info = dato;
		(*nuevo)->liga = NULL;
		res = 1;
	}
	return (res);
}

void capturaStack (STACK* cab)
{
	int res, dato, resp;
	do {
		printf ("Dato: ");
		scanf ("%d", &dato);
		res = push (cab, dato);
		if (res) {
			printf ("Otro dato (1-si/0-no)? ");
			scanf ("%d", &resp);
		} else
			printf ("Dato no ingresado\n");
	} while (res && resp);
}

int push (STACK* cab, int dato)
{
	int res;
	STACK nuevo;
	res = creaNodo (&nuevo, dato);
	if (res) {
		nuevo->liga = *cab;
		*cab = nuevo;
	}
	return (res);
}

int pop (STACK* cab, int* r)
{
	int res = 0;
	if (*cab) {
		*r = (*cab)->info;

		STACK temp;
		temp = *cab;
		*cab = temp->liga;
		free (temp);
		res = 1;
	}
	return (res);
}

void imprimePila (STACK* cab)
{
	int d;
	while (pop (cab, &d))
		printf ("%d ", d);
}
