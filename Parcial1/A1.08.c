/*
 * Objetivo: Manejo de un arreglo bidimensional 'dinámico'.
 * Autor: Azael Monreal
 * Fecha: 06/09/22
 * Nota(s): El arreglo es de estructuras.
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

void getRC(int* nr, int* nc);
int asignMem(Person*** ptr, int nr, int nc);
void inputData(Person** ptr, int nr, int nc);
void printData(Person** ptr, int nr, int nc);
void freeMem(Person** ptr, int nr);

int main(void)
{
	Person** array;

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

int asignMem(Person*** arr, int nr, int nc)
{
	*arr = (Person**)malloc(nr * sizeof(Person*));
	if(!*arr) {
		return 0;
	}
	for(int i = 0; i < nr; i++) {
		(*arr)[i] = (Person*)malloc(nc * sizeof(Person));
		if(!(*arr)[i]) {
			while(--i >= 0)
				free((*arr)[i]);
			free(*arr);
			return 0;
		}
	}
	return 1;
}

void inputData(Person** arr, int nr, int nc)
{
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			printf("Person [%d][%d]\n", i, j);
			printf("name: ");
			scanf("%s", arr[i][j].name);
			fflush(stdout);
			printf("age: ");
			scanf("%d", &arr[i][j].age);
			printf("height: ");
			scanf("%f", &arr[i][j].height);
			printf("weight: ");
			scanf("%f", &arr[i][j].weight);
			arr[i][j].bmi = arr[i][j].height / (arr[i][j].height * arr[i][j].height);
			printf("\n");
		}
		printf("\n");
	}
}

void printData(Person** arr, int nr, int nc)
{
	printf("----- Array -----\n");
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			printf("[name:%s age:%d height:%.2f weight:%.2f bmi:%.2f]\n", arr[i][j].name,
				   arr[i][j].age, arr[i][j].height, arr[i][j].weight, arr[i][j].bmi);
		}
		printf("\n");
	}
	printf("-----------------\n");
}

void freeMem(Person** arr, int nr)
{
	for(int i = 0; i < nr; i++)
		free(arr[i]);
	free(arr);
}
