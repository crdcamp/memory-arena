CFLAGS =  -Wpadded -Wall -Wextra -Wunused-parameter

all: arena

run: main
	./arena

main: arena.c

watch:
	ls *c | entr -c make run

clean:
	$(RM) arena

.PHONY: all run clean
