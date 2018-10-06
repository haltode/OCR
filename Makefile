CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -O2 \
	$(shell pkg-config --cflags gtk+-3.0)
LDFLAGS =
LDLIBS = -lm $(shell pkg-config --libs gtk+-3.0)

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
