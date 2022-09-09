/*
 * Objetivo: Funcionas basicas para manejar apuntadores
 * Autor: Azael Monreal
 * Fecha: 25/08/22
 * Nota(s): El apuntador es de tipo long.
 */

#include <stdio.h>
#include <stdlib.h>

int asignMem(long**);
void setData(long*, long);
void printData(long*);
void inputData(long*);
void add1(long*);
void subs1(long*);
void freeMem(long*);

int main(int argc, char* argv[])
{
	long* ptrLong;

	if(asignMem(&ptrLong))
	{
		setData(ptrLong, 100);
		printData(ptrLong);
		inputData(ptrLong);
		printData(ptrLong);
		add1(ptrLong);
		printData(ptrLong);
		subs1(ptrLong);
		printData(ptrLong);
		freeMem(ptrLong);
	}
	else
		printf("No se pudo asignar la memoria\n");

	return 0;
}

int asignMem(long** ptr)
{
	*ptr = (long*)malloc(sizeof(long));

	return *ptr!=NULL;
}

void setData(long* ptr, long data) { *ptr = data; }

void printData(long* ptr) { printf("El dato es: %ld\n", *ptr); }

void inputData(long* ptr)
{
	printf("Dame el dato: ");
	scanf("%ld", ptr);
}
void add1(long* ptr) { (*ptr)++; }

void subs1(long* ptr) { (*ptr)--; }

void freeMem(long* ptr) { free(ptr); }
