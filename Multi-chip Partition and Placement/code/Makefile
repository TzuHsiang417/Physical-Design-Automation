# Compiler
CC = g++
C17 = -std=c++17

# Path
SRC_PATH = .
BUILD_PATH = .

# Executable 
EXE = go

# Source 
SOURCES = $(SRC_PATH)/main.cpp  
OBJECTS = $(BUILD_PATH)/Lab3.exe

# Compiler flags
CXXFLAG = -O3 -Wall
INCLUDE = -I$(SRC_PATH) 

# Make-command list
.PHONY: clean

# Target: Dependencies
# 	Shell-command

main.out: main.o placement.o placerow.o abacus.o readfile.o partition.o
	$(CC) $(C17) -o $(OBJECTS) main.o placement.o placerow.o abacus.o readfile.o partition.o

main.o: main.cpp placement.o placerow.o abacus.o readfile.o partition.o
	$(CC) $(C17) -c main.cpp

placement.o: placement.cpp placerow.o abacus.o readfile.o
	$(CC) $(C17) -c placement.cpp

placerow.o: placerow.cpp placement.h parameter.h partition.o
	$(CC) $(C17) -c placerow.cpp

abacus.o: abacus.cpp placement.h parameter.h partition.o
	$(CC) $(C17) -c abacus.cpp

readfile.o: readfile.cpp placement.h parameter.h partition.o
	$(CC) $(C17) -c readfile.cpp

partition.o: partition.cpp parameter.h
	$(CC) $(C17) -c partition.cpp

clean:
	@echo "Removing objects"
	@echo "Removing executable file"
	del main.out *.o *.exe
