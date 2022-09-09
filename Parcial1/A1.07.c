/*
 * Objetivo: Manejo de un arreglo bidimensional 'dinámico'.
 * Autor: Azael Monreal
 * Fecha: 06/09/22
 * Nota(s): El arreglo es de tipo long int.
 */

#include <stdio.h>
#include <stdlib.h>

void getRC(int* nr, int* nc);
int asignMem(long*** ptr, int nr, int nc);
void inputData(long** ptr, int nr, int nc);
void printData(long** ptr, int nr, int nc);
void freeMem(long** ptr, int nr);

int main(void)
{
	long** array;

	int nRen, nCol;

	getRC(&nRen, &nCol);

	if(asignMem(&array, nRen, nCol)) {
		inputData(array, nRen, nCol);
		printData(array, nRen, nCol);
		freeMem(array, nRen);
	} else
		printf("insufficient memory\n");

	return 0;
}

void getRC(int* nr, int* nc)
{
	printf("Rows: ");
	scanf("%d", nr);
	printf("Columns: ");
	scanf("%d", nc);
}

int asignMem(long*** arr, int nr, int nc)
{
	*arr = (long**)malloc(nr * sizeof(long*));
	if(!*arr) {
		return 0;
	}
	for(int i = 0; i < nr; i++) {
		(*arr)[i] = (long*)malloc(nc * sizeof(long));
		if(!(*arr)[i]) {
			while(--i >= 0)
				free((*arr)[i]);
			free(*arr);
			return 0;
		}
	}
	return 1;
}

void inputData(long** arr, int nr, int nc)
{
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			printf("[%d, %d]: ", i, j);
			scanf("%ld", (*(arr + i) + j));
		}
		printf("\n");
	}
}

void printData(long** arr, int nr, int nc)
{
	printf("----- Array -----\n");
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++)
			printf("%ld\t", arr[i][j]);
		printf("\n");
	}
	printf("-----------------\n");
}

void freeMem(long** arr, int nr)
{
	for(int i = 0; i < nr; i++)
		free(arr[i]);

	free(arr);
}
