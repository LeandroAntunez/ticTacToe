EXE	= ticTacToe

SRCS	= src/draw.c src/logic.c src/main.c
OBJS	= $(SRCS:.c=.o)

# Enable Debian/Ubuntu build hardening unless already
# enabled/disabled  — see hardened-cc(1) —  and ensure
# the setting, whatever it is, is seen by the compiler
# (and linker, hardened-ld(1)).
DEB_BUILD_HARDENING ?= 1
export DEB_BUILD_HARDENING

CC	= gcc

CFLAGS	= -Wextra -Wall -pedantic
CFLAGS	+= -Wstrict-prototypes
#CFLAGS	+= -O
CFLAGS	+= -g

.PHONY:	all clean distclean
all:	$(EXE)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXE)

#$(EXE): $(OBJS)

$(EXE) : $(OBJS)
	$(CC) -o $(EXE) $(OBJS)

$(OBJS): src/ticTacToe.h Makefile
