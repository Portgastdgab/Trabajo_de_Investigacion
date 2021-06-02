#include <iostream>
#include <vector>
#include <map>

using namespace std;

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

int main()
{
	unsigned exponent = 15;
	auto chain = findChain(exponent);
	cout << "chain\t: ";
	for (int i = 0; i < chain.size(); i++)
	{
		cout << chain[i] << ",";
	}
	cout << endl;
	return 0;
}
