lab3: main.o
	g++ -std=c++11 -g -Wall main.o -o lab4
main.o: main.cpp BinarySearchTree.h BinarySearchTree.hpp BinaryNode.h BinaryNode.hpp
	g++ -std=c++11 -g -Wall -c main.cpp
clean:
	rm *.o lab4
