CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =
LDLIBS = -lm

SRCS = main.c event.c hashtable.c store.c time.c trie.c utils.c
OBJS = $(SRCS:.c=.o)
DEPS = hashtable.h event.h store.h time.h trie.h utils.h

EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJS) $(EXECUTABLE)
