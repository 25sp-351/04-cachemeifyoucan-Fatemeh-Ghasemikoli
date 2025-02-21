CC = gcc
CFLAGS = -Wall -Wextra -O2
DEBUGFLAGS = -g -DDEBUG  # Debug mode flags
RM = rm -f

SRCS = main.c input.c rodcutting.c solution.c
OBJS = $(SRCS:.c=.o)

all: policyLRU policyFIFO

policyLRU: $(OBJS) cache_lru.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) cache_lru.o

policyFIFO: $(OBJS) cache_fifo.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) cache_fifo.o

# Pattern rule for compiling object files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o policyLRU policyFIFO

debug: CFLAGS = $(DEBUGFLAGS)
debug: clean all

.PHONY: all clean debug
