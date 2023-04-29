# Install
BIN = demo

# Flags
CFLAGS += -std=c99 -pedantic -O0
CFLAGS += $(shell pkg-config --cflags sdl2)
LIBS += -lm -ldl $(shell pkg-config --libs sdl2)

SRC = main.c
OBJ = $(SRC:.c=.o)

ifeq ($(OS),Windows_NT)
BIN := $(BIN).exe
LIBS += -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lm -lGLU32
endif

$(BIN):
	@mkdir -p bin
	rm -f bin/$(BIN) $(OBJS)
	$(CC) $(SRC) $(CFLAGS) -o bin/$(BIN) $(LIBS)
