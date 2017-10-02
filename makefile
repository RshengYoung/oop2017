all: hw2

hw2: mainTerm.o number.o atom.o variable.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 mainTerm.o number.o atom.o variable.o -lgtest
else
	g++ -o hw2 mainTerm.o number.o atom.o variable.o -lgtest -lpthread
endif

mainTerm.o: mainTerm.cpp utTerm.h
	g++ --std=c++11 -c mainTerm.cpp

number.o: number.cpp number.h
	g++ --std=c++11 -c number.cpp

atom.o: atom.cpp atom.h
	g++ --std=c++11 -c atom.cpp

variable.o: variable.cpp variable.h
	g++ --std=c++11 -c variable.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif