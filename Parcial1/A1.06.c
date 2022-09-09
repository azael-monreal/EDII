/*
 * Objetivo: Manejo de un arreglo unidimensional dinámico de estructuras.
 * Autor: Azael Monreal
 * Fecha: 03/09/22
 * Nota(s): El arreglo es de estructuras.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char key[6];
	char name[26];
	float sold;
	float base_salary;
	int comision;
	float net_salary;
} Vendor;

int getSize();
int asignMem(Vendor*[], int);
void inputData(Vendor[], int);
void printArray(Vendor[], int);
void freeMem(Vendor[]);

void calcComisions(Vendor[], int);
void calcNSalaries(Vendor[], int);
float calcAvrgNSalary(Vendor[], int);

int main(void)
{
	char str[10] = "he";
	Vendor* ptrVendor;
	int size = getSize();

	if(asignMem(&ptrVendor, size))
	{
		inputData(ptrVendor, size);
		calcComisions(ptrVendor, size);
		calcNSalaries(ptrVendor, size);
		printArray(ptrVendor, size);
		printf("sueldo promedio: %f", calcAvrgNSalary(ptrVendor, size));
		freeMem(ptrVendor);
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

int asignMem(Vendor* vend[], int s)
{
	*vend = (Vendor*)malloc(s * sizeof(Vendor));

	return *vend != NULL;
}

void inputData(Vendor vend[], int s)
{
	for(int i = 0; i < s; i++)
	{
		getchar();
		printf("[Vendedor 1]\nclave: ");
		gets(vend[i].key);
		printf("nombre: ");
		gets(vend[i].name);
		printf("salario base: ");
		scanf("%f", &vend[i].sold);
		printf("total vendido: ");
		scanf("%f", &vend[i].base_salary);
		vend[i].net_salary = 0;
		vend[i].comision = 0;
	}
}

void printArray(Vendor vend[], int s)
{
	for(int i = 0; i < s; i++)
		printf("[Vendedor %d]\nclave: %s\nnombre: %s\ntotal vendido: %f\nsalario base: %f\ncomision: %d\nsalario neto: %f\n",
			   i + 1, vend[i].key, vend[i].name, vend[i].sold, vend[i].base_salary, vend[i].comision, vend[i].net_salary);
}

void freeMem(Vendor* vend) { free(vend); }

void calcComisions(Vendor vend[], int s)
{
	for(int i = 0; i < s; i++)
	{
		float sold = vend[i].sold;
		int comision;

		if(sold > 7000)
			comision = 21;
		else if(sold > 3000)
			comision = 18;
		else if(sold > 1000)
			comision = 13;
		else
			comision = 10;

		vend[i].comision = comision;
	}
}

void calcNSalaries(Vendor vend[], int s)
{
	for(int i = 0; i < s; i++)
		vend[i].net_salary = vend[i].base_salary + (vend[i].sold * vend[i].comision / 100);
}

float calcAvrgNSalary(Vendor vendors[], int s)
{
	float sum = 0;
	for(int i = 0; i < s; i++)
		sum += vendors[i].net_salary;
	return sum / s;
}
