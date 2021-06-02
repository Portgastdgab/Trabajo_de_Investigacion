/**
 * Optimization levels: https://linux.die.net/man/1/gcc
 * add -<optimization_level>
 * gcc -Ofast
 * Optimization levels: https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
 **/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <NTL/ZZ.h>
#include <vector>
#include <map>

using namespace std;
using namespace NTL;
// a single addition chain
typedef std::vector<unsigned int> Chain;

// iterative depth-first search of Brauer sequence
bool search(Chain &chain, unsigned int exponent, unsigned int maxDepth)
{
	// too deep ?
	if (chain.size() > maxDepth)
		return false;

	auto last = chain.back();
	for (size_t i = 0; i < chain.size(); i++)
	{
		//auto sum = chain[i] + last;
		auto sum = chain[chain.size() - 1 - i] + last; // try high exponents first => about twice as fast
		if (sum == exponent)
			return true;

		chain.push_back(sum);
		if (search(chain, exponent, maxDepth))
			return true;

		chain.pop_back();
	}

	return false;
}

// increase depth until a solution is found
Chain findChain(unsigned int exponent)
{
	// cached ? (needed for Hackerrank only)
	static std::map<unsigned int, Chain> cache;
	auto lookup = cache.find(exponent);
	if (lookup != cache.end())
		return lookup->second;

	// start iterative search
	Chain chain;
	unsigned int depth = 1;
	while (true)
	{
		// reset chain
		chain = {1};
		// a start search
		if (search(chain, exponent, depth))
			break;

		// failed, allow to go one step deeper
		depth++;
	}

	cache[exponent] = chain;
	return chain;
}

long mySmallModule(long dividend, long divisor)
{
	const long quotient = dividend / divisor;
	const long remainder = dividend - (quotient * divisor);
	return (remainder < 0) ? remainder + divisor : remainder;
}

ZZ myHugeModule(ZZ dividend, ZZ divisor)
{
	const ZZ quotient = dividend / divisor;
	const ZZ remainder = dividend - (quotient * divisor);
	return (remainder < 0) ? remainder + divisor : remainder;
}

// unsigned binarySearch()
// {
// }
// unsigned smallSearch(unsigned chain[], unsigned size)
// {
// }

ZZ empower(ZZ base, unsigned exponent)
{
	auto chain = findChain(exponent);
	ZZ resultChain[chain.size()] = {base, base * base};
	// unsigned (*search[2])(unsigned *) = {
	// 	binarySearch,
	// 	smallSearch,
	// };
	for (unsigned i = 2; i < chain.size(); i++)
	{
		auto sum = chain[i];
		const unsigned exp1_index = i - 1;
		const unsigned exp2 = sum - chain[exp1_index];
		unsigned exp2_index;
		for (unsigned j = 0; j < chain.size(); j++)
			if (exp2 == chain[j])
			{
				exp2_index = j;
				break;
			}

		ZZ mult1 = resultChain[exp1_index];
		ZZ mult2 = resultChain[exp2_index];
		resultChain[i] = mult1 * mult2;
		// resultChain[i] = resultChain[i-1] * resultChain[resultChain[i-1]]
	}
	return resultChain[chain.size() - 1];
}

void classic_euclidean(ZZ a, ZZ b)
{
	ZZ c;
	while (b != 0)
	{
		c = a;
		a = b;
		b = myHugeModule(c, b);
	}
	cout << "classic euclidean\t: " << a << endl;
}

ZZ bits(int bits)
{
	ZZ begin = empower(ZZ(2), bits) / ZZ(2), end = empower(ZZ(2), bits);
	srand(time(NULL));
	return begin + myHugeModule(ZZ(rand()), (end - begin));
}

void Euclides_con_menor_resto(ZZ a, ZZ b)
{
	cout << "mcd(" << a << ", " << b << ") = ";
}
void binario_del_mcd(ZZ a, ZZ b)
{
	cout << "mcd(" << a << ", " << b << ") = ";
}
ZZ Lehmer_del_mcd(ZZ a, ZZ b)
{
	if (a == 0)
		return b;
	if (b == 0)
		return a;
	if (a == b)
		return a;

	const ZZ difference = a - b;
	if (a > b)
		return Lehmer_del_mcd(difference, b);
	else
		return Lehmer_del_mcd(a, difference);
}

void Otro_algoritmo_que_sugiera(ZZ a, ZZ b)
{
	cout << "mcd(" << a << ", " << b << ") = ";
}
int main()
{
	int n_bits = 1024;
	ZZ a = bits(n_bits);
	ZZ b = bits(n_bits);
	while (b == a)
		b = bits(n_bits);

	classic_euclidean(a, b);
}
