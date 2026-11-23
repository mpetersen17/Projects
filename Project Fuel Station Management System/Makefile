CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -g -o0
TARGET = fuel_station

SOURCES = fuel_station.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

rebuild: clean all
