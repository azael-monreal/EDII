#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodoMun {
	char nomMun[25];
	float egMun;
	float pobMun;
	float dpMun;
	struct nodoMun* sigMun;
} * MUN;
typedef struct nodoEdo {
	char nomEdo[25];
	float egEdo;
	float pobEdo;
	float dpEdo;
	float promDp;
	MUN cabMun;
	struct nodoEdo* sigEdo;
} * EDO;

void initEdo (EDO*);
int creaNodoMun (MUN* nvoMun, char* nom, float eg, float pob);
int creaNodoEdo (EDO* nvoEdo, char* nom);
int insEdoOrd (EDO* cabEdo, char* nom);
int insEdoOrdRec (EDO* cabEdo, char* nom);
void capturaEdos (EDO* cabEdo);
int insMunEdo (EDO cabEdo, char* nEdo, char* nMun, float eg, float pob);
void capturaMun (EDO cabEdo);
void muestraTodoIt (EDO cabEdo);
void elimTodosMun (MUN*);
;
void muestraMunRec (MUN cabMun);
void muestraEdoRec (EDO cabEdo);
void muestraEdoNoMun (EDO cabEdo);
void encuentraEdoMasMun (EDO cabEdo, char* edoMasMun);
int elimMunEdo (EDO cabEdo, char* nEdo, char* nMun);
int elimMunEdoRec (EDO cabEdo, char* nEdo, char* nMun);
int elimEdoIt (EDO* cabEdo, char* nEdo);
int elimEdoRec (EDO* cabEdo, char* nEdo);
void elimTodosMun (MUN* cabMun);

// * Funciones
// a) Inicialización=>EDO (Estado de vacío --> NULL)

void iniEdo (EDO* cabEdo) { *cabEdo = NULL; }

// b) Crear nodo municipio

int creaNodoMun (MUN* nvoMun, char* nom, float eg, float pob)
{
	int res = 0;
	*nvoMun = (MUN) malloc (sizeof (struct nodoMun));
	if (*nvoMun) {
		strcpy ((*nvoMun)->nomMun, nom);
		(*nvoMun)->egMun = eg;
		(*nvoMun)->pobMun = pob;
		(*nvoMun)->dpMun = pob / eg;
		(*nvoMun)->sigMun = NULL;
		res = 1;
	}
	return (res);
}

// c) Crear nodo estado

int creaNodoEdo (EDO* nvoEdo, char* nom)
{
	int res = 0;
	*nvoEdo = (EDO) malloc (sizeof (struct nodoEdo));
	if (*nvoEdo) {
		strcpy ((*nvoEdo)->nomEdo, nom);
		(*nvoEdo)->egEdo = 0;
		(*nvoEdo)->pobEdo = 0;
		(*nvoEdo)->dpEdo = 0;
		(*nvoEdo)->cabMun = NULL;
		(*nvoEdo)->sigEdo = NULL;
		res = 1;
	}
	return (res);
}

// d) Inserción de estado(s)→ Lista (¿Iterativa o recursiva?)
//  - Inicio (No recomendable -> repetidos)
//  - Referencia (No recomendable -> Conocer algún dato -> repetidos)
//  - Final (Mínimo -> evitar repetidos)
//  - Ordenada (Ideal -> evitar repetidos -> recorridos cortos)
// 23
// (vacía) -> 23
// (busca)
//  25
// 10 18 23 30 39 51 . . .

int insEdoOrd (EDO* cabEdo, char* nom)
{
	int res = 0;
	EDO nuevo, aux, ant;
	aux = *cabEdo;
	while (aux && strcmp (nom, aux->nomEdo) > 0) {
		ant = aux;
		aux = aux->sigEdo;
	}
	if (!aux || strcmp (nom, aux->nomEdo) < 0) {
		res = creaNodoEdo (&nuevo, nom);
		if (res) {
			nuevo->sigEdo = aux;
			if (aux == *cabEdo)
				*cabEdo = nuevo;
			else
				ant->sigEdo = nuevo;
		}
	}
	return (res);
}

// e) Inserción de estado (recursiva)

int insEdoOrdRec (EDO* cabEdo, char* nom)
{
	int res;
	EDO nuevo;
	if (*cabEdo && strcmp (nom, (*cabEdo)->nomEdo) == 0) // Repetido ?
		res = 0;
	else if (!*cabEdo || strcmp (nom, (*cabEdo)->nomEdo) < 0) // Puede ingresar ?
	{
		res = creaNodoEdo (&nuevo, nom);
		if (res) {
			nuevo->sigEdo = *cabEdo;
			*cabEdo = nuevo;
		}
	} else
		res = insEdoOrdRec (&(*cabEdo)->sigEdo, nom);

	return (res);
}

// f) Captura estados ➔ Llenar la lista de estados (Iterativa)→ Recursiva NO CICLOS

void capturaEdos (EDO* cabEdo)
{
	int res;
	char nom[25];
	char resp;
	do {
		fflush (stdin);
		printf ("Nombre del estado : ");
		gets (nom);
		res = insEdoOrd (cabEdo, nom);
		if (res) {
			printf ("Dato aceptado\n");
			printf ("Otro? ");
			scanf ("% c", &resp);
		} else
			printf ("Dato no aceptado\n");
	} while (res && resp == 's');
}

// g) Inserción de municipio → edo (iterativa)
//  suponer que ya tenemos ---> insMunOrd(MUN *cabMun, char *nMun, float eg, float pob);

int insMunEdo (EDO cabEdo, char* nEdo, char* nMun, float eg, float pob)
{
	int res = 0;

	while (cabEdo && strcmp (nEdo, cabEdo->nomEdo) > 0)
		cabEdo = cabEdo->sigEdo;
	if (cabEdo && strcmp (nEdo, cabEdo->nomEdo) == 0)
		res = insMunOrd (&cabEdo->cabMun, nMun, eg, pob);
	return (res);
}

// h) * Inserción de municipio independiente (iterativa)
// i) * Inserción de municipio independiente (recursiva)
// j) * Inserción de municipio → edo (recursiva)
// k) Captura municipios(➔edo)

void capturaMun (EDO cabEdo)
{
	int res;
	char resp;
	char nEdo[25], nMun[25];
	float eg, pob;
	do {
		fflush (stdin);
		printf ("Nombre estado : ");
		gets (nEdo);
		printf ("Nombre municipio : ");
		gets (nMun);
		printf ("Extensión geográfica : ");
		scanf ("%f", &eg);
		printf ("Población : ");
		scanf ("%f", &pob);
		res = insMunEdo (cabEdo, nEdo, nMun, eg, pob);
		if (res) {
			printf ("Dato aceptado\n");
			printf ("Otro? ");
			scanf ("%c", &resp);
		} else
			printf ("Dato no aceptado\n");
	} while (res && resp == 's');
}

// l) * Captura estados (recursiva)
// m) * Captura municipios→Edo (Recursiva)
// n) Recorrido: Mostrar "toda" la información (Iterativa)
// Edo1 Mun11 Mun12... Edo2 Mun21 Mun22... Edo3 Mun31...

void muestraTodoIt (EDO cabEdo)
{
	MUN auxMun;
	while (cabEdo) {
		printf ("%s\n", cabEdo->nomEdo);
		auxMun = cabEdo->cabMun;
		while (auxMun) {
			printf ("%s, %.2f, %.0f, %.0f\n", auxMun->nomMun, auxMun->egMun, auxMun->pobMun,
					auxMun->dpMun);
			auxMun = auxMun->sigMun;
		}
		cabEdo = cabEdo->sigEdo;
	}
}

// o) Recorrido: Mostrar toda la información (Recursiva)

void muestraMunRec (MUN cabMun)
{
	if (cabMun) // ¿Hay municipios?
	{
		printf ("%s, %.2f, %.0f, %.0f\n", cabMun->nomMun, cabMun->egMun, cabMun->pobMun,
				cabMun->dpMun);
		muestraMunRec (cabMun->sigMun);
	}
}
void muestraEdoRec (EDO cabEdo)
{
	if (cabEdo) // ¿Hay estados?
	{
		printf ("%s\n", cabEdo->nomEdo);
		muestraMunRec (cabEdo->cabMun);
		muestraEdoRec (cabEdo->sigEdo);
	}
}

// p) Recorrido: Mostrar los estados con su No. de municipios.

void muestraEdoNoMun (EDO cabEdo)
{
	int cont;
	MUN auxMun;
	while (cabEdo) {
		cont = 0;
		for (auxMun = cabEdo->cabMun; auxMun; auxMun = auxMun->sigMun)
			cont++;

		printf ("% s tiene % d municipios\n", cabEdo->nomEdo, cont);
		cabEdo = cabEdo->sigEdo;
	}
}

// q) Recorrido: Encontrar y "retornar" el nombre del estado con más municipios → Algoritmo del
// mayor/menor

void encuentraEdoMasMun (EDO cabEdo, char* edoMasMun)
{
	int cont, contMay = 0;
	MUN auxMun;
	strcpy (edoMasMun, "");
	while (cabEdo) {
		cont = 0;
		for (auxMun = cabEdo->cabMun; auxMun; auxMun = auxMun->sigMun)
			cont++;
		if (cont > contMay) // Algoritmo el mayor
		{
			contMay = cont;
			strcpy (edoMasMun, cabEdo->nomEdo); // asignación de cadena (igualar)
		}

		cabEdo = cabEdo->sigEdo;
	} // while
}

// r) *Recorrido: Calcular y "registrar" la extensión geográfica de los estados,
//  considerando que es la suma de las extensiones de los municipios.
// t) *Recorrido: Calcular y "registrar"" la población de los estados, considerando
//  que es la suma de las poblaciones de los municipios.
// s) *Recorrido: Calcular y "asignar" la densidad de población de cada estado.
// u) Eliminar municipio -> edo (Iterativa)

int elimMunEdo (EDO cabEdo, char* nEdo, char* nMun)
{
	int res = 0;
	while (cabEdo && strcmp (nEdo, cabEdo->nomEdo) > 0)
		cabEdo = cabEdo->sigEdo;
	if (cabEdo && strcmp (nEdo, cabEdo->nomEdo) == 0) // Encontramos el estado
		res = elimMunIt (&cabEdo->cabMun, nMun);
	return (res);
}

// v) Eliminar municipio -> edo (Recursiva)

int elimMunEdoRec (EDO cabEdo, char* nEdo, char* nMun)
{
	int res;
	if (!cabEdo || strcmp (nEdo, cabEdo->nomEdo) < 0)
		res = 0;
	else if (strcmp (nEdo, cabEdo->nomEdo) == 0) // Encontramos el estado
		res = elimMunIt (&cabEdo->cabMun, nMun);
	else
		res = elimMunEdoRec (cabEdo->sigEdo, nEdo, nMun);
	return (res);
}

// w) *Eliminar municipio independiente (It)
// x) *Eliminar municipio independiente(Rec)
// y) Eliminar estado → Eliminar lista de municipios
// a) Iterativa

int elimEdoIt (EDO* cabEdo, char* nEdo)
{
	int res = 0;
	EDO ant, aux;
	aux = *cabEdo;
	while (aux && strcmp (nEdo, aux->nomEdo) > 0) {
		ant = aux;
		aux = aux->sigEdo;
	}
	if (aux && strcmp (nEdo, aux->nomEdo) == 0) // Encontró el estado ?
	{
		elimTodosMun (&aux->cabMun);
		if (aux == *cabEdo)
			*cabEdo = aux->sigEdo;
		else
			ant->sigEdo = aux->sigEdo;
		free (aux);
		res = 1;
	}

	return (res);
}

// b) Recursiva

int elimEdoRec (EDO* cabEdo, char* nEdo)
{
	int res;
	EDO aux;
	if (!*cabEdo || strcmp (nEdo, (*cabEdo)->nomEdo) < 0)
		res = 0;
	else if (strcmp (nEdo, (*cabEdo)->nomEdo) == 0) {
		elimTodosMun (&(*cabEdo)->cabMun);
		aux = *cabEdo;
		*cabEdo = aux->sigEdo;
		free (aux);
		res = 1;
	} else
		res = elimEdoRec (&(*cabEdo)->sigEdo, nEdo);
	return (res);
}

// z) Eliminar lista de municipios.
// a) Iterativa

void elimTodosMun (MUN* cabMun)
{
	MUN aux;
	while (*cabMun) {
		aux = *cabMun;
		*cabMun = aux->sigMun;
		free (aux);
	}
}

// b) Recursiva
//

void calcPromDp (EDO estados)
{
	MUN municipio;
	int muns;
	float dens;
	for (;estados;estados = estados->sigEdo) {
		muns = 0;
		dens = 0;
		for (;municipio;municipio = municipio->sigMun) {
			muns++;
			dens += municipio->dpMun;
		}
		estados->promDp = dens/muns;
	}
}
