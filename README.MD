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

NTL Documentation original command

	g++ -g -O2 -std=c++11 -pthread -march=native foo.cpp -o foo -lntl -lgmp -lm
