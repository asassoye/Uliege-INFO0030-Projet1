### 
## Makefile skeleton
## INFO0030: Projet 1
## Andrew Sassoye
### 

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LD=gcc
LDFLAGS=

# Files
EXEC=pnm
MODULES=main.c pnm.c verifications.c error.c
OBJECTS=main.o pnm.o verifications.o error.o

## Rules

all: $(EXEC)

pnm: $(OBJECTS)
	$(LD) -o $(EXEC) $(OBJECTS) $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

pnm.o: pnm.c
	$(CC) -c pnm.c -o pnm.o $(CFLAGS)

clean:
	rm -f *.o $(EXEC) *~

