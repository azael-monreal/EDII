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

int removeR (LIST* list, int d)
{
	int res = 0;
	if (*list) {
		res = removeR (&(*list)->sig, d);
		if ((*list)->data == d) {
			res = 1;
			LIST temp = *list;
			*list = (*list)->sig;
			free (temp);
		}
	}

	return res;
}

int main (void)
{
	LIST a, b;

	initList (&a);
	push (&a, 20);
	push (&a, 90);
	push (&a, 38);
	push (&a, 20);
	push (&a, 20);
	push (&a, 9);
	push (&a, 20);
	push (&a, 3);
	push (&a, 20);
	push (&a, 20);
	push (&a, 90);
	push (&a, 20);
	printList (a);

	printf ("\n");
	printf ("found: %d\n", removeR (&a, 20));
	printList (a);

	printf ("\n");
	printf ("found: %d\n", removeR (&a, 90));
	printList (a);

	printf ("\n");
	printf ("found: %d\n", removeR (&a, 90));
	printList (a);
	return 0;
}
