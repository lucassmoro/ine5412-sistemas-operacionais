virtmem: main.o page_table.o disk.o program.o page_replacement.o
	g++ main.o page_table.o disk.o program.o page_replacement.o -o virtmem -g

main.o: src/main.cc
	g++ -Wall -g -c src/main.cc -o main.o

page_table.o: src/page_table.cc
	g++ -Wall -g -c src/page_table.cc -o page_table.o

page_replacement.o: src/page_replacement.cc
	g++ -Wall -g -c src/page_replacement.cc -o page_replacement.o

disk.o: src/disk.cc
	g++ -Wall -g -c src/disk.cc -o disk.o

program.o: src/program.cc
	g++ -Wall -g -c src/program.cc -o program.o

clean:
	rm -f *.o src/virtmem
