CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -O2 \
	$(shell pkg-config --cflags gtk+-3.0) \
	$(shell pkg-config --cflags sdl2)
LDFLAGS =
LDLIBS = -lm $(shell pkg-config --libs gtk+-3.0) \
	$(shell pkg-config --libs sdl2) -lSDL2_image
VALGRIND = valgrind

SRC = $(shell find src -name '*.c')
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}


all: ocr
	mkdir -p output/chars

ocr: ${OBJ}
	@echo "Linking ocr binary..."
	@$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	@echo "Building $@..."
	@$(CC) -MMD -o $@ -c $< $(CFLAGS)

-include ${DEP}

.PHONY: clean check-valgrind

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} ocr

check-valgrind:
	${VALGRIND} \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--suppressions=.glib.suppression \
		./ocr --train
