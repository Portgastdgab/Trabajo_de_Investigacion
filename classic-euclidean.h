#include "module.h"

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
