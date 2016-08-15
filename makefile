# change application name here (executable output name)
TARGET=gladewin
PENDING=pending_program

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS= main.o
POBJ= pending_program.o


all: $(OBJS) $(POBJ)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
	$(LD) -o $(PENDING) $(POBJ) $(LDFLAGS)



main.o: src/main.c

	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB) -o main.o

pending_program.o: src/pending_program.c

	$(CC) -c $(CCFLAGS) src/pending_program.c $(GTKLIB) -o pending_program.o


clean:
	rm -f *.o $(TARGET)
