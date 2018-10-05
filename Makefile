CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -O2
LDFLAGS =
LDLIBS = -lm

SRC = main.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

.PHONY: all clean

all: main
	mv main ocr

main: ${OBJ}

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} ocr

-include ${DEP}
