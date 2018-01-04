PROJECT = hw8
# SHELL = main

HEADERS = atom.h variable.h struct.h list.h scanner.h parser.h global.h iterator.h
OBJECTS = atom.o struct.o list.o
UNITTEST = expression.h exception.h
MAINTEST = mainTest

all: $(PROJECT) #shell

$(PROJECT): $(MAINTEST).o $(OBJECTS)
ifeq (${OS}, Windows_NT)
	g++ -o $(PROJECT) $(MAINTEST).o $(OBJECTS) -lgtest
else
	g++ -o $(PROJECT) $(MAINTEST).o $(OBJECTS) -lgtest -lpthread
endif

# shell: $(SHELL).o
# ifeq (${OS}, Windows_NT)
# 	g++ -o shell $(SHELL).o $(OBJECTS) -lgtest
# else
# 	g++ -o shell $(SHELL).o $(OBJECTS) -lgtest -lpthread
# endif

# $(SHELL).o: $(SHELL).cpp $(HEADERS) $(OBJECTS)
# 	g++ -std=gnu++0x -c $(SHELL).cpp

$(MAINTEST).o: $(MAINTEST).cpp $(UNITTEST) $(HEADERS)
	g++ -std=gnu++0x -c $(MAINTEST).cpp

atom.o: atom.h atom.cpp variable.h
	g++ -std=gnu++0x -c atom.cpp
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