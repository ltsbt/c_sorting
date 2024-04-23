CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lSDL2
SOURCES = main.c
EXECUTABLE = c_sorting

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean run
