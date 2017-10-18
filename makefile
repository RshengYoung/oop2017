PROJECT = hw3

all: $(PROJECT)

$(PROJECT): main.o term.o atom.o variable.o number.o struct.o
ifeq (${OS}, Windows_NT)
	g++ -o $(PROJECT) main.o term.o atom.o variable.o number.o struct.o -lgtest
else
	g++ -o $(PROJECT) main.o term.o atom.o variable.o number.o struct.o -lgtest -lpthread
endif

main.o: main.cpp utVariable.h
	g++ -std=gnu++0x -c main.cpp
term.o: term.h term.cpp
	g++ -std=gnu++0x -c term.cpp
atom.o: atom.h atom.cpp
	g++ -std=gnu++0x -c atom.cpp
variable.o: variable.h variable.cpp
	g++ -std=gnu++0x -c variable.cpp
number.o: number.h number.cpp
	g++ -std=gnu++0x -c number.cpp
struct.o: struct.h struct.cpp
	g++ -std=gnu++0x -c struct.cpp

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