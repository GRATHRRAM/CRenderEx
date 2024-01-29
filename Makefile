CC=gcc
FLAGS=-O3 -Wall -Wextra -g -c -lm
BUILD_DIR=Build
SRC_DIR=src

all: CopyToBuild

CRenderEx.o: $(SRC_DIR)/CRenderEx.c
	$(CC) $(FLAGS) $(SRC_DIR)/CRenderEx.c -o CRenderEx.o

CRInput.o: $(SRC_DIR)/CRInput.c
	$(CC) $(FLAGS) $(SRC_DIR)/CRInput.c -o CRInput.o

libCRenderEx.a: CRenderEx.o 
	ar ruv libCRenderEx.a CRenderEx.o

libCRInput.a: CRInput.o
	ar ruv libCRInput.a CRInput.o

CopyToBuild: libCRInput.a libCRenderEx.a
	cp *.a $(BUILD_DIR)/
 
clean: 
	rm *.a *.o
