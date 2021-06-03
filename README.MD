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

### cmake && make

Usual workflow executing a c++ project
1.	take build
2.	cmake ..
3.	make

cmake purpose: generate make file.

makeFile purpose: execute g++ commands

	cmake <cmakeLists.txt directory>
eg. You are in build/ and cmakeLists.txt is in root, the parent directory
	cmake ..

Now, we have a makeFile generated :D

execute it with make tool

	make

By default: cmake & make look for their respective config file in the current working directory if no arguments are passed with them, hence, make will look for the Make file in the build directory.

> “when you don’t create things, you become defined by your tastes rather than ability. your tastes only narrow & exclude people. so create.” ― Why The Lucky Stiff

a wonderful project is able to
*	Compile what you made.
*	Expose a header file to let people use your code as a third party library.
*	Use third party libraries.


As far as I have read, CMakeLists.txt file can be subdivided into 5 major sections.

1. Flags
2. Files
3. Include
4. Targets
5. External libraries
6. Unit Testing

There are 2 types of c++ libraries:

1. static (.a)
	2 types
	1. CMakeLists.txt + include + src

			add_subdirectory( ./libs/Project_name)
			target_link_libraries(binary project_name)

		CMake will automatically look for a CMakeLists.txt file inside the sub directory and run it. It will the use the .a file to link with your output as mentioned in the second line.

	2. .a file + include

		In this case, the library file has already been compiled for you and you don’t need CMake to do it for you. But adding this directory as a sub directory won’t work as CMake will start looking for a CMakeLists.txt inside the library’s directory and as it doesn’t have one, it will throw an error and won’t compile. So these three line do the trick.

			add_library(lib_project_bin STATIC IMPORTED)
			set_property(
				TARGET project_bin PROPERTY IMPORTED_LOCATION
				${CMAKE_SOURCE_DIR}/libs/Project_name/project_lib.a
				)
			target_link_libraries( binary lib_project_bin )

		The first one basically tells CMake that we are using a static library name libname.a or namelib.a. The second line specifies the path from where it resides. I have used the ${CMAKE_SOURCE_DIR} to demonstrate the use of internal CMake variable. That variable is the path to the CMakeLists.txt in your root directory; the one we run to build our binary. The last command as you might have guessed, links the library to our output.

		this is the old way of using cmake. No modular design or good software practices.
		Since Cmake 3.0.0 modular approach has been taken up.

2. dynamic (.so)

https://medium.com/heuristics/c-application-development-part-1-project-structure-454b00f9eddc
https://medium.com/heuristics/c-application-development-part-2-cmakelists-txt-e415b5b387dc
https://medium.com/heuristics/c-application-development-part-3-cmakelists-txt-from-scratch-7678253e5e24

https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/
https://medium.com/@onur.dundar1/cmake-tutorial-585dd180109b
