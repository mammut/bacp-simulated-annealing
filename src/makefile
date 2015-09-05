CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
#LDFLAGS = -Wall -lm -largp $(DEBUG) # OSX
LDFLAGS = -Wall -lm $(DEBUG) # Linux
EXEC = bacp

OBJS = main.o \
	   bacp.o \
	   simulated-annealing.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	find . -name '*.o' -type f -delete
	rm -f $(EXEC)

