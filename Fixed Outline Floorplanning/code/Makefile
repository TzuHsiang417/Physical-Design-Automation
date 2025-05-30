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
OBJECTS = $(BUILD_PATH)/Lab2.exe

# Compiler flags
CXXFLAG = -O3 -Wall
INCLUDE = -I$(SRC_PATH) 

# Make-command list
.PHONY: clean

# Target: Dependencies
# 	Shell-command

main.out: main.o SA.o operation.o floorplan.o readfile.o
	$(CC) $(C17) -o $(OBJECTS) main.o SA.o operation.o floorplan.o readfile.o

main.o: main.cpp SA.o operation.o floorplan.o readfile.o
	$(CC) $(C17) -c main.cpp

SA.o: SA.cpp operation.o floorplan.o
	$(CC) $(C17) -c SA.cpp

operation.o: operation.cpp floorplan.o
	$(CC) $(C17) -c operation.cpp

readfile.o: readfile.cpp floorplan.o
	$(CC) $(C17) -c readfile.cpp

floorplan.o: floorplan.cpp floorplan.h parameter.h btree.h
	$(CC) $(C17) -c floorplan.cpp




clean:
	@echo "Removing objects"
	@echo "Removing executable file"
	del main.out *.o *.exe
