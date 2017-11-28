PROJECT	= hw6

all: $(PROJECT)

$(PROJECT): main.o term.o
ifeq (${OS}, Windows_NT)
	g++ -o $(PROJECT) main.o term.o -lgtest
else
	g++ -o $(PROJECT) main.o term.o -lgtest -lpthread
endif


main.o: main.cpp utParser.h atom.h number.h variable.h struct.h list.h parser.h scanner.h node.h
	g++ -std=gnu++0x -c main.cpp

term.o: term.h term.cpp
	g++ -std=gnu++0x -c term.cpp
	

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