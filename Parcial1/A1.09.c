/*
 * Objetivo: Manejo de un apuntador genérico.
 * Autor: Azael Monreal
 * Fecha: 09/09/22
 * Nota(s): El apuntador es a tipo unsigned int.
 */

#include <stdio.h>
#include <stdlib.h>

int asignMem (void**);
void asignData (void*, unsigned int);
void inputData (void*);
void printData (void*);
void freeMem (void*);

int main ()
{
	void* ptr;

	if (asignMem (&ptr)) {
		asignData (ptr, 100);
		printData (ptr);
		inputData (ptr);
		printData (ptr);
		freeMem (ptr);
	} else
		printf ("Memoria insuficiente\n");
}

int asignMem (void** ptr)
{
	*ptr = malloc (sizeof (int));

	return *ptr != NULL;
}

void asignData (void* ptr, unsigned int data) { *(unsigned int*) ptr = data; }

void inputData (void* ptr)
{
	printf ("Escribe el dato: ");
	scanf ("%u", (unsigned int*) ptr);
}

void printData (void* ptr) { printf ("El dato es: %u\n", *(unsigned int*) ptr); }

void freeMem (void* ptr) { free (ptr); }
