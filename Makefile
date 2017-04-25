TARGET = main
CC = gcc
CCFLAGS = -ansi -Wall -Wshadow -std=gnu99 -O2
LFLAGS = -lm

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CCFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LFLAGS) -o $@

clean:
	rm -f *.o $(TARGET) 

