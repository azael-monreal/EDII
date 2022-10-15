#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* sig;
} * LIST;

void initList (LIST* list) { *list = NULL; }

void push (LIST* list, int n)
{
	struct node* temp = (LIST) malloc (sizeof (struct node));

	temp->data = n;

	temp->sig = *list;

	*list = temp;
}

void printList (LIST list)
{
	for (; list; list = list->sig) {
		printf ("%d\n", list->data);
	}
}

int compareLists (LIST listA, LIST listB)
{
	int eq = 1;
	for (; listA && listB && eq; listA = listA->sig, listB = listB->sig)
		if (listA->data != listB->data)
			eq = 0;

	if (listA || listB)
		eq = 0;

	return eq;
}

int compareListsR (LIST listA, LIST listB)
{
	int eq;

	if (!listA && !listB)
		eq = 1;
	else if (!listA || !listB || listA->data != listB->data)
		eq = 0;
	else
		eq = compareListsR (listA->sig, listB->sig);

	return eq;
}

int isOrdered (LIST list)
{
	int eq = 1;

	for (; list->sig && eq; list = list->sig)
		if (list->data > list->sig->data)
			eq = 0;

	return eq;
}

int isOrderedR (LIST list)
{
	int eq;

	if (!list->sig)
		eq = 1;
	else if (list->data > list->sig->data)
		eq = 0;
	else
		eq = isOrderedR (list->sig);

	return eq;
}

int main (void)
{
	LIST a, b;

	initList (&a);
	push (&a, 90);
	push (&a, 38);
	push (&a, 20);
	push (&a, 9);
	push (&a, 3);
	printList (a);

	initList (&b);
	push (&b, 90);
	push (&b, 38);
	push (&b, 20);
	push (&b, 9);
	printList (b);

	printf ("equals = %d\n", compareLists (a, b));
	printf ("equalsr = %d\n", compareListsR (a, b));
	push (&b, 3);
	printf ("equals = %d\n", compareLists (a, b));
	printf ("equalsr = %d\n", compareListsR (a, b));

	printf ("ordered = %d\n", isOrdered (a));
	printf ("orderedr = %d\n", isOrderedR (a));
	push (&a, 8);
	printf ("ordered = %d\n", isOrdered (a));
	printf ("orderedr = %d\n", isOrderedR (a));

	return 0;
}
