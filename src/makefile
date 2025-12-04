# Name des Programms
TARGET = multithreaded-pattern-search.exe

# Quell- und Headerdateien
SRC     = main.c functions.c threads.c
HEADERS = search.h

# Objektverzeichnis und -dateien
OBJ_DIR = obj
OBJ     = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

# Compiler
CC     = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g
LDFLAGS = -pthread

.PHONY: all run clean

# Default target
all: $(TARGET)

# Linken
$(TARGET): $(OBJ)
	@echo "Linking $(TARGET)..."
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Compile-Regel für obj/ Dateien
$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Erzeuge obj/ falls nicht vorhanden
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: all
	@echo "Running $(TARGET)..."
	./$(TARGET)

clean:
	@echo "Cleaning up..."
	rm -f $(OBJ_DIR)/*.o $(TARGET)
