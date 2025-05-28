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
OBJECTS = $(BUILD_PATH)/CornerStitching.exe

# Compiler flags
CXXFLAG = -O3 -Wall
INCLUDE = -I$(SRC_PATH) 

# Make-command list
.PHONY: clean

# Target: Dependencies
# 	Shell-command

main.out: main.o block.o readfile.o
	$(CC) $(C17) -o $(OBJECTS) main.o block.o readfile.o

main.o: main.cpp block.h readfile.h parameter.h
	$(CC) -I$(INCLUDE) $(CXXFLAG) $(C17) -c main.cpp

block.o: block.cpp block.h parameter.h
	$(CC) -I$(INCLUDE) $(CXXFLAG) $(C17) -c block.cpp

readfile.o: readfile.cpp block.h readfile.h
	$(CC) -I$(INCLUDE) $(CXXFLAG) $(C17) -c readfile.cpp

clean:
	@echo "Removing objects"
	@echo "Removing executable file"
	del main.out main.o block.o readfile.o $(OBJECTS)