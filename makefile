INC_DIR = include
SRC_DIR = src
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

term.o: $(INC_DIR)/term.h $(SRC_DIR)/term.cpp
	g++ -std=gnu++0x -c $(SRC_DIR)/term.cpp
atom.o: $(INC_DIR)/atom.h $(SRC_DIR)/atom.cpp
	g++ -std=gnu++0x -c $(SRC_DIR)/atom.cpp
variable.o: $(INC_DIR)/variable.h $(SRC_DIR)/variable.cpp
	g++ -std=gnu++0x -c $(SRC_DIR)/variable.cpp
number.o: $(INC_DIR)/number.h $(SRC_DIR)/number.cpp
	g++ -std=gnu++0x -c $(SRC_DIR)/number.cpp
struct.o: $(INC_DIR)/struct.h $(SRC_DIR)/struct.cpp
	g++ -std=gnu++0x -c $(SRC_DIR)/struct.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o $(PROJECT)
endif

# test:
# 	make clean
# 	make
# 	./$(PROJECT)