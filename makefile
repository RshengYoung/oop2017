PROJECT	= hw4

all: $(PROJECT)

$(PROJECT): main.o atom.o
ifeq (${OS}, Windows_NT)
	g++ -o $(PROJECT) main.o atom.o -lgtest
else
	g++ -o $(PROJECT) main.o atom.o -lgtest -lpthread
endif


main.o: main.cpp utList.h variable.h struct.h list.h
	g++ -std=gnu++0x -c main.cpp

atom.o: atom.h atom.cpp
	g++ -std=gnu++0x -c atom.cpp
	

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