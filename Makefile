CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -O2 \
	$(shell pkg-config --cflags gtk+-3.0) \
	$(shell pkg-config --cflags sdl)
LDFLAGS =
LDLIBS = -lm $(shell pkg-config --libs gtk+-3.0) \
	$(shell pkg-config --libs sdl) -lSDL_image

SRC = 	main.c \
	char_detection/char_detection.c \
	char_detection/line_detection.c \
	interface/buttons.c \
	interface/interface.c \
	neural_network/neural_network.c \
	neural_network/propagation.c \
	neural_network/training/training.c \
	neural_network/training/gradient_descent.c \
	preprocessing/binarization.c \
	preprocessing/grayscale.c \
	preprocessing/preprocessing.c \
	tests/xor_network.c \
	utils/image.c \
	utils/math.c \
	utils/matrix.c \
	utils/random.c
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
