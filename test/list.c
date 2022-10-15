#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct nodo {
	int info;
	struct nodo* liga;
} * LISTA;

void iniLista (LISTA* cab);
int creaNodo (LISTA* nuevo, int dato);
void capturaLst (LISTA* cab);
int insIni (LISTA* cab, int dato);
int insFinalIt (LISTA* cab, int dato);
int insFinalRec (LISTA* cab, int dato);
int insIzqRefIt (LISTA* cab, int dato, int ref);
int insIzqRefRec (LISTA* cab, int dato, int ref);
void muestraLstIt (LISTA cab);
void muestraLstRec (LISTA cab);
int sumaLstIt (LISTA cab);
int sumaLstRec (LISTA cab);
void incremHIt (LISTA cab, int h);
void incremHRec (LISTA cab, int h);
void mayorLstIt (LISTA cab, int* mayor);
int mayorLstRec (LISTA cab);
int elimIni (LISTA* cab);
int elimIniRecu (LISTA* cab, int* datoRecu);
int elimFinalIt (LISTA* cab);
int elimFinalRec (LISTA* cab);
int elimRefIt (LISTA* cab, int ref);
int elimRefRec (LISTA* cab, int ref);
void muestraRes (int suma, int myrIt, int myrRec);

int main ()
{
	LISTA lista;
	int laSuma, laMayorIt, laMayorRec;
	iniLista (&lista);
	capturaLst (&lista);
	printf ("Datos originales: ");
	muestraLstIt (lista);
	printf ("\nDatos aumentados en 3 It.: ");
	incremHIt (lista, 3);
	muestraLstRec (lista);
	printf ("\nDatos aumentados en 2 Rec.: ");
	incremHRec (lista, 2);
	muestraLstRec (lista);
	printf ("\n");
	laSuma = sumaLstIt (lista);
	mayorLstIt (lista, &laMayorIt);
	laMayorRec = mayorLstRec (lista);
	muestraRes (laSuma, laMayorIt, laMayorRec);
}
void iniLista (LISTA* cab) { *cab = NULL; }
int creaNodo (LISTA* nuevo, int dato)
{
	int res = 0;
	*nuevo = (LISTA) malloc (sizeof (struct nodo));
	if (*nuevo) {
		(*nuevo)->info = dato;
		(*nuevo)->liga = NULL;
		res = 1;
	}
	return (res);
}
void capturaLst (LISTA* cab)
{
	int res, dato, refe, op;
	char resp;
	do {
		printf ("Dato: ");
		scanf ("%d", &dato);
		printf ("Opcion (1-insIni, 2-insFinIt, 3-insFinRec, 4-insRefIt, 5-insRefRec):");
		scanf ("%d", &op);
		if (op == 4 || op == 5) {
			printf ("Valor referencia: ");
			scanf ("%d", &refe);
		}
		switch (op) {
			case 1:
				res = insIni (cab, dato);
				break;
			case 2:
				res = insFinalIt (cab, dato);
				break;
			case 3:
				res = insFinalRec (cab, dato);
				break;
			case 4:
				res = insIzqRefIt (cab, dato, refe);
				break;
			case 5:
				res = insIzqRefRec (cab, dato, refe);
				break;
		}
		if (res) {
			fflush (stdin);
			printf ("Otro dato (s/n)?");
			scanf ("%c", &resp);
		} else
			printf ("Dato no ingresado\n");
	} while (res && tolower (resp) == 's');
}
int insIni (LISTA* cab, int dato)
{
	int res;
	LISTA nuevo;
	res = creaNodo (&nuevo, dato);
	if (res) {
		nuevo->liga = *cab;
		*cab = nuevo;
	}
	return (res);
}
int insFinalIt (LISTA* cab, int dato)
{
	int res;
	LISTA nuevo, aux;
	res = creaNodo (&nuevo, dato);
	if (res) {
		if (!*cab)
			*cab = nuevo;
		else {
			aux = *cab;
			for (; aux->liga; aux = aux->liga)
				;
			aux->liga = nuevo;
		}
	}
	return (res);
}
int insFinalRec (LISTA* cab, int dato)
{
	int res;
	LISTA nuevo;
	if (!*cab)
		res = creaNodo (cab, dato);
	else
		res = insFinalRec (&(*cab)->liga, dato);
	return (res);
}
int insIzqRefIt (LISTA* cab, int dato, int ref)
{
	int res = 0;
	LISTA nuevo, aux, ant;
	aux = *cab;
	while (aux && ref != aux->info) {
		ant = aux;
		aux = aux->liga;
	}
	if (aux) {
		res = creaNodo (&nuevo, dato);
		if (res) {
			nuevo->liga = aux;
			if (*cab == aux)
				*cab = nuevo;
			else
				ant->liga = nuevo;
		}
	}
	return (res);
}
int insIzqRefRec (LISTA* cab, int dato, int ref)
{
	int res;
	LISTA nuevo;
	if (!*cab)
		res = 0;
	else if (ref == (*cab)->info) {
		res = creaNodo (&nuevo, dato);
		if (res) {
			nuevo->liga = *cab;
			*cab = nuevo;
		}
	} else
		res = insIzqRefRec (&(*cab)->liga, dato, ref);
	return (res);
}
void muestraLstIt (LISTA cab)
{
	while (cab) {
		printf ("%d ", cab->info);
		cab = cab->liga;
	}
}
void muestraLstRec (LISTA cab)
{
	if (cab) {
		printf ("%d ", cab->info);
		muestraLstRec (cab->liga);
	}
}
int sumaLstIt (LISTA cab)
{
	int suma;
	for (suma = 0; cab; suma += cab->info, cab = cab->liga)
		;
	return (suma);
}
int sumaLstRec (LISTA cab)
{
	int suma;
	if (!cab)
		suma = 0;
	else
		suma = cab->info + sumaLstRec (cab->liga);
	return (suma);
}
void incremHIt (LISTA cab, int h)
{
	while (cab) {
		cab->info += h;
		cab = cab->liga;
	}
}
void incremHRec (LISTA cab, int h)
{
	if (cab) {
		incremHRec (cab->liga, h);
		cab->info += h;
	}
}
void mayorLstIt (LISTA cab, int* mayor)
{
	*mayor = 0;
	while (cab) {
		if (cab->info > *mayor)
			*mayor = cab->info;
		cab = cab->liga;
	}
}
int mayorLstRec (LISTA cab)
{
	int mayor;
	if (!cab)
		mayor = 0;
	else {
		mayor = mayorLstRec (cab->liga);
		if (cab->info > mayor)
			mayor = cab->info;
	}
	return (mayor);
}
int elimIni (LISTA* cab)
{
	int res = 0;
	LISTA aux;
	if (*cab) {
		aux = *cab;
		*cab = aux->liga;
		free (aux);
		res = 1;
	}
	return (res);
}
int elimIniRecu (LISTA* cab, int* datoRecu)
{
	int res = 0;
	LISTA aux;
	if (*cab) {
		aux = *cab;
		*cab = aux->liga;
		free (aux);
		res = 1;
	}
	return (res);
}
int elimFinalIt (LISTA* cab)
{
	int res = 0;
	LISTA aux, ant;
	if (*cab) {
		aux = *cab;
		while (aux->liga) {
			ant = aux;
			aux = aux->liga;
		}
		if (*cab == aux)
			*cab = NULL;
		else
			ant->liga = NULL;
		free (aux);
		res = 1;
	}
	return (res);
}
int elimFinalRec (LISTA* cab)
{
	int res;
	if (!*cab)
		res = 0;
	else if (!(*cab)->liga) {
		free (*cab);
		*cab = NULL;
		res = 1;
	} else
		res = elimFinalRec (&(*cab)->liga);
	return (res);
}
int elimRefIt (LISTA* cab, int ref)
{
	int res = 0;
	LISTA aux, ant;
	aux = *cab;
	while (aux && ref != aux->info) {
		ant = aux;
		aux = aux->liga;
	}
	if (aux) {
		if (*cab == aux)
			*cab = aux->liga;
		else
			ant->liga = aux->liga;
		free (aux);
		res = 1;
	}
	return (res);
}
int elimRefRec (LISTA* cab, int ref)
{
	int res;
	LISTA aux;
	if (!*cab)
		res = 0;
	else if (ref == (*cab)->info) {
		aux = *cab;
		*cab = aux->liga;
		free (aux);
		res = 1;
	} else
		res = elimRefRec (&(*cab)->liga, ref);
	return (res);
}
void muestraRes (int suma, int myrIt, int myrRec)
{
	printf ("Suma = %d\tMayorIt = %d\tMayorRec=%d\n", suma, myrIt, myrRec);
}
