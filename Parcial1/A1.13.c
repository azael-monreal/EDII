/*
 * Objetivo: Manejo de una estructura generica.
 * Autor: Azael Monreal
 * Fecha: 13/09/22
 * Nota(s): La estructura contiene un void*.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int type;
	void* data;
} Generic;

int asignMem (Generic*);
void getData (Generic);
void printData (Generic);
void freeMem (Generic);

int main (void)
{
	Generic* generic;
	if (asignMem (generic)) {
		getData (*generic);
		printData (*generic);
		freeMem (*generic);
	} else
		printf ("memoria insuficiente\n");

	return 0;
}

int asignMem (Generic* ptr)
{
	int t;
	printf ("tipo del dato (1 - char, 2 - int, 3 - float): ");
	scanf ("%d", &t);

	switch (t) {
		case 1:
			ptr->data = malloc (sizeof (char));
			break;
		case 2:
			ptr->data = malloc (sizeof (int));
			break;
		case 3:
			ptr->data = malloc (sizeof (float));
			break;
		default:
			printf ("tipo invalido\n");
			break;
	}

	if (!(ptr->data))
		return 0;

	ptr->type = t;
	return 1;
}

void getData (Generic gen)
{
	printf ("ingresa el dato de tipo ");
	switch (gen.type) {
		case 1:
			printf ("char: ");
			scanf ("%c", (char*) gen.data);
			break;
		case 2:
			printf ("int: ");
			scanf ("%d", (int*) gen.data);
			break;
		case 3:
			printf ("float: ");
			scanf ("%f", (float*) gen.data);
			break;
		default:
			printf ("tipo invalido\n");
			break;
	}
}

void printData (Generic gen)
{
	printf ("el dato es ");
	switch (gen.type) {
		case 1:
			printf ("%c\n", *(char*) gen.data);
			break;
		case 2:
			printf ("%d\n", *(int*) gen.data);
			break;
		case 3:
			printf ("%f\n", *(float*) gen.data);
			break;
		default:
			printf ("tipo invalido\n");
			break;
	}
}

void freeMem (Generic ptr) { free (ptr.data); }
