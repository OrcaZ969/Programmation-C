CC=gcc
LD=gcc

CFLAGS=-g -O0
LDFLAGS=-lm


EXEC=Part4_2_2
SRC=$(wildcard *.c)
OBJECTS=$(SRC:.c=.o)

.PHONY: target clean realclean

target:$(EXEC)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC): $(OBJECTS)
	$(LD) -o $(EXEC) $(OBJECTS) $(LDFLAGS)
	
clean:
	rm -f *.o core
realclean: clean
	rm -f *~
