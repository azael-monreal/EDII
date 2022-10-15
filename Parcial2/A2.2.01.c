#include <stdio.h>
#include <stdlib.h>

typedef struct nodoFracc {
	int num;
	int den;
	struct nodoFracc* sigFracc;
} * FRACC;

void initList (FRACC* list) { list = NULL; }

void push (FRACC* list, int n, int d)
{
	struct nodoFracc* temp = (FRACC) malloc (sizeof (struct nodoFracc));

	temp->num = n;
	temp->den = d;

	temp->sigFracc = *list;

	*list = temp;
}

void printList (FRACC list)
{

	for (; list; list = list->sigFracc) {
		printf ("%d / %d\n", list->num, list->den);
	}
}

void sumFrac (FRACC frac, int* num, int* den)
{
    int snum = 0, sden = 1, gcd, lcm;

    for (; frac; frac = frac->sigFracc) {
        for (int i = 1; i <= sden; i++) {
            if (!(sden % i) && !(frac->den % i)) {
                gcd = i;
            }
        }

        lcm = (sden * frac->den) / gcd;
        snum = (lcm * snum / sden) + (lcm * frac->num / frac->den);
        sden = lcm;
    }
    for (int i = 1; i <= sden; i++) {
        if (!(sden % i) && !(snum % i)) {
            gcd = i;
        }
    }

    *num = snum / gcd;
    *den = sden / gcd;
}

int main (void)
{
	FRACC lista;
	initList (&lista);
	push (&lista, 2, 6);
	// push (&lista, 5, 8);
	push (&lista, 9, 3);
	push (&lista, 2, 3);

	printList (lista);

	int sumanum, sumaden;

	sumFrac (lista, &sumanum, &sumaden);

	printf ("%d / %d\n", sumanum, sumaden);

	return 0;
}
