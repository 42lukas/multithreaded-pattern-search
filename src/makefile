# multithreaded-pattern-search.exe

.PHONY: all run clean

# Default-Target
all: multithreaded-pattern-search.exe

# Linken des Programms
multithreaded-pattern-search.exe: obj/main.o obj/functions.o obj/threads.o
	@echo "Linking multithreaded-pattern-search.exe..."
	gcc -Wall -Wextra -std=c11 -g -pthread -o multithreaded-pattern-search.exe obj/main.o obj/functions.o obj/threads.o

# Objektdatei für main.c
obj/main.o: main.c search.h | obj
	@echo "Compiling main.c..."
	gcc -Wall -Wextra -std=c11 -g -c main.c -o obj/main.o

# Objektdatei für functions.c
obj/functions.o: functions.c search.h | obj
	@echo "Compiling functions.c..."
	gcc -Wall -Wextra -std=c11 -g -c functions.c -o obj/functions.o

# Objektdatei für threads.c
obj/threads.o: threads.c search.h | obj
	@echo "Compiling threads.c..."
	gcc -Wall -Wextra -std=c11 -g -c threads.c -o obj/threads.o

# Erzeuge obj/-Verzeichnis, falls nicht vorhanden
obj:
	mkdir -p obj

run: all
	@echo "Running multithreaded-pattern-search.exe..."
	./multithreaded-pattern-search.exe

clean:
	@echo "Cleaning up..."
	rm -f obj/*.o multithreaded-pattern-search.exe