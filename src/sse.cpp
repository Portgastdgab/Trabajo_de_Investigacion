/**
 * Microsoft SSE Documentation:
 * https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2010/kcwz153a(v=vs.100)?redirectedfrom=MSDN
 **/

#include <iostream>
#include <immintrin.h>
#include <vector>

using namespace std;

void sse(char *a, const char *b, int N)
{
	int nb_iters = N / 16;

	__m128i *l = (__m128i *)a;
	__m128i *r = (__m128i *)b;

	for (int i = 0; i < nb_iters; ++i, ++l, ++r)
		_mm_store_si128(l, _mm_add_epi8(*l, *r));
}

int main()
{
	// float a[] __attribute__((aligned(16))) = {41982., 81.5091, 3.14, 42.666};
	// __m128 *ptr = (__m128 *)a;
	// __m128 t = _mm_sqrt_ps(*ptr);
	std::vector<uint32_t> v;

	// Unoptimized loop with index:
	uint64_t sum = 0;
	for (unsigned int i = 0; i < v.size(); i++)
		sum += v[i];

	// Unoptimized loop with iterator:
	uint64_t sum = 0;
	std::vector<uint32_t>::const_iterator it;
	for (it = v.begin(); it != v.end(); it++)
		sum += *it;

	// Unoptimized loop with iterator:
	uint64_t sum = 0;
	std::vector<uint32_t>::const_iterator it, end(v.end());
	for (it = v.begin(); it != end; it++)
		sum += *it;

	// Pre-increment iterators:
	uint64_t sum = 0;
	std::vector<uint32_t>::const_iterator it, end(v.end());
	for (it = v.begin(); it != end; ++it)
		sum += *it;

	// Range-based loop:
	uint64_t sum = 0;
	for (auto const &x : v)
		sum += x;

	//To tell the truth, when I did the measurements, I was surprised that caching the end iterator made a difference, even for vector, where as there was no difference between pre- and post-incrementation, even for a reverse iterator into a map. After all, end() was inlined as well; in fact, every single function used in my tests was inlined.
	// 	As to unrolling the loops: I'd probably do something like this:

	// std::vector<uint32_t>::const_iterator current = v.begin();
	// std::vector<uint32_t>::const_iterator end = v.end();
	// switch ( (end - current) % 4 ) {
	// case 3:
	//     sum += *current ++;
	// case 2:
	//     sum += *current ++;
	// case 1:
	//     sum += *current ++;
	// case 0:
	// }
	// while ( current != end ) {
	//     sum += current[0] + current[1] + current[2] + current[3];
	//     current += 4;
	// }

	return 0;
}
