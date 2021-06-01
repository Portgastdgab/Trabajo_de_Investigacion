/**
 * Optimization levels: https://linux.die.net/man/1/gcc
 * add -<optimization_level>
 * gcc -Ofast
 * Optimization levels: https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
 **/

#include <iostream>

int myModule(int dividend, int divisor)
{
	const int quotient = dividend / divisor;
	const int remainder = dividend - (quotient * divisor);
	return (remainder < 0) ? remainder + divisor : remainder;
}
int classic_euclidean(int a, int b)
{
	int c;
	while (b != 0)
	{
		c = a;
		a = b;
		b = myModule(c, b);
	}
	return a;
}

int Euclides_con_menor_resto()
{
}

int binary_mcd()
{
}

int lehmer_mcd(int a, int b)
{
	// a >= b
}

int other()
{
}

int main()
{
}
