CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -O2 \
	$(shell pkg-config --cflags gtk+-3.0) \
	$(shell pkg-config --cflags sdl)
LDFLAGS =
LDLIBS = -lm $(shell pkg-config --libs gtk+-3.0) \
	$(shell pkg-config --libs sdl) -lSDL_image
VALGRIND = valgrind

SRC = 	interface/buttons.c \
	interface/interface.c \
	neural_network/neural_network.c \
	neural_network/propagation.c \
	neural_network/training/gradient_descent.c \
	neural_network/training/training.c \
	ocr.c \
	preprocessing/binarization.c \
	preprocessing/grayscale.c \
	preprocessing/preprocessing.c \
	segmentation/chars.c \
	segmentation/lines.c \
	segmentation/segmentation.c \
	tests/xor_network.c \
	utils/image.c \
	utils/math.c \
	utils/matrix.c \
	utils/random.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

.PHONY: all clean check-valgrind

all: ocr
	mkdir -p output

ocr: ${OBJ}

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} ocr

check-valgrind:
	${VALGRIND} \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--suppressions=glib.suppression \
		./ocr --train

-include ${DEP}
