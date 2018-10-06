CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -O2
LDFLAGS =
LDLIBS = -lm

SRC = 	main.c ocr.c \
	char_detection/char_detection.c \
	neural_network/neural_network.c \
	preprocessing/preprocessing.c
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
