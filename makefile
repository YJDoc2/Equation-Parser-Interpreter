eqparse : main.o cparser.o
	g++ -o eqparse cparser.o main.o
	rm ./*.o

main.o : main.cpp c_bindings.cpp
	g++ -c main.cpp

cparser.o : cparser.c
	gcc -c cparser.c -lm
