/*
 * Objetivo: Manejo de un arreglo unidimensional dinámico.
 * Autor: Azael Monreal
 * Fecha: 01/09/22
 * Nota(s): El arreglo es de tipo double.
 */

#include <stdio.h>
#include <stdlib.h>

int getSize();
int asignMem(double**, int);
void inputData(double*, int);
void printArray(double*, int);
void freeMem(double*);

int main(void)
{
	double* ptrDouble;
	int size = getSize();

	if(asignMem(&ptrDouble, size))
	{
		inputData(ptrDouble, size);
		printArray(ptrDouble, size);
		freeMem(ptrDouble);
	}
	else
		printf("no memory\n");

	return 0;
}

int getSize()
{
	int s;
	printf("Array size: ");
	scanf("%d", &s);
	return (s);
}

int asignMem(double** ptr, int s)
{
	*ptr = (double*)malloc(s * sizeof(double));

	return *ptr != NULL;
}

void inputData(double* ptr, int s)
{
	for(int i = 0; i < s; i++)
	{
		printf("[%d]: ", i);
		scanf("%lf", &ptr[i]);
	}
}

void printArray(double* ptr, int s)
{
	printf("----- Array -----\n");
	for(int i = 0; i < s; i++)
		printf("[%d] => %lf\n", i, ptr[i]);
	printf("-----------------\n");
}

void freeMem(double* ptr) { free(ptr); }
