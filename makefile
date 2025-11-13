# ============================
#  Makefile für macOS & Windows
#  (Windows über Git Bash / MSYS2 / WSL)
# ============================

# Name des Programms
TARGET  = multithreaded-pattern-search

# Verzeichnisse
SRCDIR  = src
INCDIR  = include

# Compiler
CC      ?= gcc

# Flags
CFLAGS  = -Wall -Wextra -pedantic -std=c11 -I$(INCDIR)
LDFLAGS = -pthread

# Alle .c-Dateien im src-Ordner
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)

# Standard-Target
all: $(TARGET)

# Linken
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Kompilieren jeder .c zu .o
$(SRCDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/search.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Programm ausführen
run: $(TARGET)
	./$(TARGET)

# Aufräumen
clean:
	@echo "Cleaning..."
	# Binaries (Unix + Windows)
	rm -f $(TARGET) $(TARGET).exe
	# Objektdateien
	rm -f $(OBJECTS)
	# Logs (optional, wenn du logs/ nutzt)
	rm -f logs/*.log 2>/dev/null || true

.PHONY: all run clean