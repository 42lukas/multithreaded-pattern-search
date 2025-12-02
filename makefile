CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread
TARGET = search_prog

OBJS = main.o threads.o functions.o
DEPS = search.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)