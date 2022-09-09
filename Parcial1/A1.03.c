/*
 * Objetivo: Manejo de apuntadores.
 * Autor: Azael Monreal
 * Fecha: 27/08/22
 * Nota(s): Apuntador a un apuntador de tipo char.
 */

#include <stdio.h>
#include <stdlib.h>

int asignMem(char***);
void setData(char**, char);
void printData(char**);
void inputData(char**);
void freeMem(char**);

int main(void)
{
	char** ptrptr;

	if(asignMem(&ptrptr))
	{
		setData(ptrptr, 'h');
		printData(ptrptr);
		inputData(ptrptr);
		printData(ptrptr);
		freeMem(ptrptr);
	}
	else
		printf("No se pudo asignar la memoria\n");

	return 0;
}

int asignMem(char*** ptr)
{
	*ptr = (char**)malloc(sizeof(char*));
	if(*ptr != NULL) /* Checar disponibilidad de memoria */
	{
		**ptr = (char*)malloc(sizeof(char));
		if(**ptr != NULL) /* Checar disponibilidad de memoria */
			return 1;
		else
			free(*ptr);
	}
	return 0;
}

void setData(char** ptrInt, char dato) { **ptrInt = dato; }

void printData(char** ptrInt) { printf("El dato es: %c\n", **ptrInt); }

void inputData(char** ptrInt)
{
	printf("Dame el dato: ");
	scanf("%c", *ptrInt);
}

void freeMem(char** ptrInt)
{
	free(*ptrInt);
	free(ptrInt);
}
