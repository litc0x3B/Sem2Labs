CC=gcc
CFLAGS=-g -Wall -c -std=c11
LDFLAGS=-g -Wall -lreadline -std=c11
SOURCES=Main.c SqrMatrix.c TypeInfo.c TypeDouble.c TypeComplex.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=lab1

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

gdb: $(EXECUTABLE)
	gdb ./$(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

valgrind: $(EXECUTABLE)
	valgrind ./$(EXECUTABLE)

clear:
	rm -v *.o

