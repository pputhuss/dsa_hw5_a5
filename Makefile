WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

SRCS = a5.c
OBJS = $(SRCS:%.c=%.o)

a5: $(OBJS)
	$(GCC) $(OBJS) -o a5

run: a5
	./a5 input.txt

clean:
	rm -f *.o a5 output