#include <stdio.h>

int main ()
{
	int a, b, gcd;

	a = 4;
	b = 8;

	for (int i = 1; i <= a; i++) {
		if (!(a % i) && !(b % i)) {
			gcd = i;
		}
	}

	printf ("%d", gcd);
}
