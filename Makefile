CC=gcc
CFLAGS=-std=c99 -O0 -g -ggdb

EXECUTABLE=temp
BINARY=a.out

OBJDIR=objs
SRCDIR=src
MAIN=$(SRCDIR)/main.c

MAYBE=maybe

OBJS=$(OBJDIR)/$(MAYBE).o

all: clean dirs $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) -fpic -o $(EXECUTABLE) $(OBJS) $(MAIN)

dirs:
	mkdir -p objs

$(OBJDIR)/$(MAYBE).o: $(SRCDIR)/$(MAYBE).c
	$(CC) -c $(CFLAGS) -o $@ $< 

clean:
	rm -rf $(OBJDIR) $(EXECUTABLE) $(BINARY)
