# Name des Programms
TARGET = multithreaded-pattern-search.exe

# Quell- und Headerdateien (hardcoded)
SRC     = main.c functions.c threads.c
HEADERS = search.h

# Objektverzeichnis und -dateien
OBJ_DIR = obj
OBJ     = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

# Compiler
CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

.PHONY: all run clean

# Default target
all: $(TARGET)

# Linken
$(TARGET): $(OBJ)
	@echo "Linking $(TARGET)..."
	$(CC) $(CFLAGS) -o $@ $^

# Compile-Regel für obj/ Dateien (abhängig von search.h)
$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Erzeuge obj/ falls nicht vorhanden
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: all
	./$(TARGET)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
