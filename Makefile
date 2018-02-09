EXE	= ticTacToe

SRCS	= src/draw.c src/logic.c src/main.c
OBJS	= $(SRCS:.c=*.o)

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

$(OBJS): src/ticTacToe.h Makefile
