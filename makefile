PROJECT	= hw7

all: $(PROJECT)

$(PROJECT): main.o term.o struct.o list.o
ifeq (${OS}, Windows_NT)
	g++ -o $(PROJECT) main.o term.o struct.o list.o -lgtest
else
	g++ -o $(PROJECT) main.o term.o struct.o list.o -lgtest -lpthread
endif


main.o: main.cpp utIterator.h atom.h number.h variable.h parser.h scanner.h iterator.h
	g++ -std=gnu++0x -c main.cpp

term.o: term.h term.cpp
	g++ -std=gnu++0x -c term.cpp
struct.o: struct.h struct.cpp
	g++ -std=gnu++0x -c struct.cpp
list.o: list.h list.cpp
	g++ -std=gnu++0x -c list.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o $(PROJECT)
endif


test:
	make clean
	make
	./$(PROJECT)