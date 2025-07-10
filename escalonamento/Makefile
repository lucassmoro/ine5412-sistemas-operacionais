executor: main.o processo.o escalonador.o
	g++ -Wall -g main.o processo.o escalonador.o -o executor

main.o: src/main.cpp
	g++ -Wall -g -c src/main.cpp -o main.o

processo.o: src/processo.cpp
	g++ -Wall -g -c src/processo.cpp -o processo.o

escalonador.o: src/escalonador.cpp
	g++ -Wall -g -c src/escalonador.cpp -o escalonador.o

clean:
	rm -f *.o executor
