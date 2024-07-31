MNIST_ML_ROOT=..
LD_LIBRARY_PATH=..
CC=g++
SRC := ./src
CFLAGS := -std=c++11 -DEUCLID
INCLUDE_DIR := ./include/*
LIB_DIR := ../lib

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

all: main

main: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o main -L$(LIB_DIR) -I$(INCLUDE_DIR) -I$(MNIST_ML_ROOT)/include -ldata -Wl,-rpath,$(LIB_DIR)

$(SRC)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR) -I$(MNIST_ML_ROOT)/include

clean:
	rm -f main $(SRC)/*.o
