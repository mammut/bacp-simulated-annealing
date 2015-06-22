CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
# LDFLAGS = -Wall -lm -largp $(DEBUG) # OSX
LDFLAGS = -Wall -lm $(DEBUG) # Linux
EXEC = bacp

all: $(EXEC)

$(EXEC): main.o simulated-annealing.o bacp.o
	$(CC) $(LDFLAGS) $^ -o $@

main.o: main.c includes/main.h includes/simulated-annealing.h includes/bacp.h
	$(CC) $(CFLAGS) $<

simulated-annealing.o: simulated-annealing.c includes/simulated-annealing.h includes/bacp.h
	$(CC) $(CFLAGS) $<

bacp.o: bacp.c includes/bacp.h
	$(CC) $(CFLAGS) $<

run: $(EXEC)
	./$(EXEC)

clean:
	find . -name '*.o' -type f -delete
	rm -f $(EXEC)

