# Research Project for Abstract Algebra
## Abstract
text about
## Guide
### Run project

	pwd
output should end with /project

	cmake .
	cmake --build .
	cmake -B ./build

	g++ main.cpp -g -O2 -std=c++11 -pthread -march=native -o main -lntl -lgmp -lm && ./main

### Aggressive Optimization

	g++ main.cpp -g -Ofast -std=c++11 -pthread -march=native -o main -lntl -lgmp -lm && ./main

check levels of optimization for a detailed explanation
Optimization levels: https://linux.die.net/man/1/gcc
Optimization levels: https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

NTL Documentation original command

	g++ -g -O2 -std=c++11 -pthread -march=native foo.cpp -o foo -lntl -lgmp -lm
