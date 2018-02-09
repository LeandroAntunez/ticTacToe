EXE	= ticTacToe

SRCS	= draw.c logic.c main.c
OBJS	= $(SRCS:.c=.o)

CC	= gcc

CFLAGS	= -Wextra -Wall -pedantic
#CFLAGS	+= -O
CFLAGS	+= -g

.PHONY:	all clean distclean
all:	$(EXE)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXE)

$(EXE):	$(OBJS)

$(OBJS): ticTacToe.h Makefile
