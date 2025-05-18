CC = gcc
BUILD = build
FILES = src/main.c src/stack.c src/valstack.c src/maze.c src/coords.c
INC = -Isrc -Iinclude
EXE   = maze.out
CFLAGS = -g -Wunused-variable -Werror=return-type -Werror=unused-variable -Werror=overflow

.PHONY: all clean

all : $(BUILD)/$(EXE)

$(BUILD)/$(EXE): $(FILES)
	$(CC) -o $@ $+ $(CFLAGS) $(INC)
	mv $(BUILD)/$(EXE) $(EXE)
clean:
	rm $(BIN)/$(EXE)

run:
	@$(BIN)/$(EXE)