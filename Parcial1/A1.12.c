/*
 * Objetivo: Manejo de un arreglo genérico.
 * Autor: Azael Monreal
 * Fecha: 10/09/22
 * Nota(s): El apuntador es a una estructura.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char name[25];
	int age;
	float height;
	float weight;
	float bmi;
} Person;

int getSize ();
int asignMem (void**, int);
void inputData (void*, int);
void printData (void*, int);
void freeMem (void*);

int main ()
{
	void* ptr;

	int size = getSize ();

	if (asignMem (&ptr, size)) {
		inputData (ptr, size);
		printData (ptr, size);
		freeMem (ptr);
	} else
		printf ("Memoria insuficiente\n");
}

int getSize ()
{
	int n;
	printf ("Tamaño del arreglo: ");
	scanf ("%d", &n);
	return n;
}

int asignMem (void** ptr, int s)
{
	*ptr = malloc (s * sizeof (Person));

	return *ptr != NULL;
}

void inputData (void* arr, int s)
{
	for (int i = 0; i < s; i++) {
		printf ("*** Persona %d ***\n", i);
		printf ("Nombre: ");
		scanf ("%s", ((Person*) arr)[i].name);
		printf ("Edad: ");
		scanf ("%d", &((Person*) arr)[i].age);
		printf ("Altura: ");
		scanf ("%f", &((Person*) arr)[i].height);
		printf ("Peso: ");
		scanf ("%f", &((Person*) arr)[i].weight);
		printf ("IMC: ");
		scanf ("%f", &((Person*) arr)[i].bmi);
		printf ("\n");
	}
}

void printData (void* arr, int s)
{
	for (int i = 0; i < s; i++) {
		printf ("*** Persona %d ***\n", i);
		printf ("Nombre: %s\n", ((Person*) arr)[i].name);
		printf ("Edad: %d\n", ((Person*) arr)[i].age);
		printf ("Altura: %f\n", ((Person*) arr)[i].height);
		printf ("Peso: %f\n", ((Person*) arr)[i].weight);
		printf ("IMC: %f\n", ((Person*) arr)[i].bmi);
		printf ("\n");
	}
}

void freeMem (void* ptr) { free (ptr); }
