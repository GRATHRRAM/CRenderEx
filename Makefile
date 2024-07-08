CC=gcc
FLAGS=-shared -Wall -Wextra -lm
BUILD_DIR=./Build
SRC_DIR=./src

all: $(BUILD_DIR)/libCRenderEx.so $(BUILD_DIR)/libCRInput.so

$(BUILD_DIR)/libCRenderEx.so: $(SRC_DIR)/CRenderEx.c
	$(CC) $(FLAGS) $(SRC_DIR)/CRenderEx.c -o $(BUILD_DIR)/libCRenderEx.so

$(BUILD_DIR)/libCRInput.so: $(SRC_DIR)/CRInput.c
	$(CC) $(FLAGS) $(SRC_DIR)/CRInput.c -o $(BUILD_DIR)/libCRInput.so

clean: 
	rm $(BUILD_DIR)/*.so

install: $(BUILD_DIR)/libCRenderEx.so $(BUILD_DIR)/libCRInput.so
	sudo cp $(BUILD_DIR)/*.so /usr/lib
