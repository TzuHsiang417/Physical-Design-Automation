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
OBJECTS = $(BUILD_PATH)/Routing.exe

# Compiler flags
CXXFLAG = -O3 -Wall
INCLUDE = -I$(SRC_PATH) 

# Make-command list
.PHONY: clean

# Target: Dependencies
# 	Shell-command

main.out: main.o router.o
	$(CC) $(C17) -o $(OBJECTS) main.o router.o

main.o: main.cpp router.o
	$(CC) $(C17) -c main.cpp

placement.o: router.cpp router.h
	$(CC) $(C17) -c router.cpp

clean:
	@echo "Removing objects"
	@echo "Removing executable file"
	del main.out *.o *.exe