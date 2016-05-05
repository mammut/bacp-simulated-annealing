CC = clang
DEBUG = -g
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	LDFLAGS = -Wall -lm $(DEBUG) # Linux
	CFLAGS = -Wall -c $(DEBUG)
endif
ifeq ($(UNAME), Darwin)
	LDFLAGS = -Wall -lm -L/usr/local/opt/argp-standalone/lib -largp $(DEBUG) # OSX
	CFLAGS = -Wall -c -I/usr/local/include $(DEBUG)
endif
EXEC = bacp
OBJS = main.o \
			 bacp.o \
			 simulated-annealing.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $<

summary: 
	awk -f lc.awk *.c includes/*.h

clean:
	find . -name '*.o' -type f -delete
	rm -f $(EXEC)

