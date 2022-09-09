/*
Objetivo: Apuntadores & estructuras.
Autor: Azael Monreal
Fecha: 28/08/2022
Nota(s): Considerando que la estructura contiene: nombre, edad, estatura, peso e imc.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char clave[5];
	char nombre[25];
	float sueldo_base;
	int bono_productividad;
	float impuestos;
	char bono_puntualidad;
	float sueldo_neto;
} Empleado;

int asignaMem(Empleado**);
void asignaDatos(Empleado*, char[5], char[25], float, int, float, char);
void imprimeDatos(Empleado);
void capturaDatos(Empleado*);
void liberaMem(Empleado*);

void calculaSNeto(Empleado*);

int main(void)
{
	Empleado* empleado;
	if(asignaMem(&empleado))
	{
		asignaDatos(empleado, "12345", "Juan Perez", 230.35, 1, 14.5, 'S');
		imprimeDatos(*empleado);
		calculaSNeto(empleado);
		imprimeDatos(*empleado);
		capturaDatos(empleado);
		imprimeDatos(*empleado);
		liberaMem(empleado);
	}
	else
		printf("No se pudo asignar la memoria\n");

	return 0;
}

int asignaMem(Empleado** emp)
{
	*emp = (Empleado*)malloc(sizeof(Empleado));

	return *emp != NULL;
}

void asignaDatos(Empleado* emp, char clave[5], char nom[25], float sbase,
				 int bprod, float imp, char bpun)
{
	strcpy(emp->clave, clave);
	strcpy(emp->nombre, nom);
	emp->sueldo_base = sbase;
	emp->bono_productividad = bprod;
	emp->impuestos = imp;
	emp->bono_puntualidad = bpun;
	emp->sueldo_neto = 0;
}

void imprimeDatos(Empleado emp)
{
	printf("Clave: %s\n", emp.clave);
	printf("Nombre: %s\n", emp.nombre);
	printf("Sueldo Base: %f\n", emp.sueldo_base);
	printf("Bono Productividad: %i\n", emp.bono_productividad);
	printf("Impuestos(%%): %f\n", emp.impuestos);
	printf("Bono Puntualidad: %c\n", emp.bono_puntualidad);
	printf("Sueldo Neto: %f\n", emp.sueldo_neto);
}

void capturaDatos(Empleado* emp)
{
	printf("Clave: ");
	gets(emp->clave);
	printf("Nombre: ");
	gets(emp->nombre);
	printf("Sueldo Base: ");
	scanf("%f", &emp->sueldo_base);
	printf("Bono Productividad: ");
	scanf("%i", &emp->bono_productividad);
	printf("Impuestos(%%): ");
	scanf("%f", &emp->impuestos);
	printf("Bono Puntualidad: ");
	scanf("%c", &emp->bono_puntualidad);
	printf("Sueldo Neto: ");
	scanf("%f", &emp->sueldo_neto);
	emp->sueldo_neto = 0;
}
void liberaMem(Empleado* emp) { free(emp); }

void calculaSNeto(Empleado* emp)
{
	emp->sueldo_neto = (emp->sueldo_base * (1 + (emp->impuestos / 100))) +
					   (emp->bono_productividad * emp->sueldo_base * 0.12) +
					   ((emp->bono_puntualidad == 'S') * 550);
}
