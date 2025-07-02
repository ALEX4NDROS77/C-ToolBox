CC = gcc
OS := $(shell uname 2>/dev/null || echo Windows)
CFLAGS = -Wall -Wextra -pedantic -std=c11 -m64 -I$(LIB_DIR)
BIN_DIR = ../bin
SRC_DIR = ../src
LIB_DIR = ../include
CLEAN_FILES := $(BIN_DIR)/*.exe *.o

.PHONY: clean teset linkedlist

clean:
	@echo "Cleaning up..."
ifeq ($(OS), Windows)
	@del /Q /F $(subst /,\,$(BIN_DIR)\*.exe) 2>nul || exit 0
	@del /Q /F *.o 2>nul || exit 0
else
	@rm -f $(BIN_DIR)/*.exe *.o
endif
	@echo "Clean complete."

logger_test.o: $(SRC_DIR)/logger.c
	$(CC) $(CFLAGS) -DDEBUG -DWARNING -c $^ -o $@

linkedlist_test.o: $(SRC_DIR)/linkedlist.c
	$(CC) $(CFLAGS) -DDEBUG -DWARNING -c $^ -o $@

linkedlist_test: linkedlist_test.o logger_test.o
	@echo "Running tests..."
	$(CC) $(CFLAGS) -DDEBUG -DWARNING $(SRC_DIR)/unit_test.c $^ -o $(BIN_DIR)/unit_test
	@$(BIN_DIR)/unit_test

logger.o: $(SRC_DIR)/logger.c
	$(CC) $(CFLAGS) -c $^ -o $@

linkedlist.o: $(SRC_DIR)/linkedlist.c
	$(CC) $(CFLAGS) -c $^ -o $@

linkedlist: linkedlist.o
	@echo "Compiling linkedlist..."
	$(CC) $(CFLAGS) $(SRC_DIR)/linkedlist.c $^ -o $(BIN_DIR)/$@
