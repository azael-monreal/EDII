#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct nodoMono {
	float coef;
	int expo;
	struct nodoMono* sigMono;
} * MONO;

void initList (MONO* list) { list = NULL; }

void push (MONO* list, float c, int e)
{
	struct nodoMono* temp = (MONO) malloc (sizeof (struct nodoMono));

	temp->coef = c;
	temp->expo = e;

	temp->sigMono = *list;

	*list = temp;
}

void printList (MONO pol)
{
	for (; pol; pol = pol->sigMono) {
		printf ("%fx^%d + ", pol->coef, pol->expo);
	}
	printf ("\n");
}

float evalPol (MONO pol, float x)
{
	float eval;
	if (!pol)
		eval = 0;
	else
		eval = pol->coef * (pow (x, pol->expo)) + evalPol (pol->sigMono, x);
	return eval;
}

int main (void)
{
	MONO pol;
	initList (&pol);
	push (&pol, 2, 1);
	// push (&lista, 5, 8);
	push (&pol, 9, 2);
	push (&pol, 2, 0);

	printList (pol);

	printf ("%f\n", evalPol (pol, 0));

	return 0;
}
