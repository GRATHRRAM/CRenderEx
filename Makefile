CC=gcc
FLAGS=-O3 -Wall -Wextra -g -c -lm
BUILD_DIR=./Build
SRC_DIR=./src

all: CRenderEx.o CRInput.o libCRInput.a libCRenderEx.a

CRenderEx.o: $(SRC_DIR)/CRenderEx.c
	$(CC) $(FLAGS) $(SRC_DIR)/CRenderEx.c -o $(BUILD_DIR)/CRenderEx.o

CRInput.o: $(SRC_DIR)/CRInput.c
	$(CC) $(FLAGS) $(SRC_DIR)/CRInput.c -o $(BUILD_DIR)/CRInput.o

libCRenderEx.a: $(BUILD_DIR)/CRenderEx.o 
	ar ruv $(BUILD_DIR)/libCRenderEx.a $(BUILD_DIR)/CRenderEx.o

libCRInput.a: $(BUILD_DIR)/CRInput.o
	ar ruv $(BUILD_DIR)/libCRInput.a $(BUILD_DIR)/CRInput.o

clean: 
	rm $(BUILD_DIR)/*.a $(BUILD_DIR)/*.o
