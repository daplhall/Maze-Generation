CC = gcc
BUILD = build
BIN   = bin
FILES = src/main.c src/stack.c src/vstack.c src/maze_jank.c src/coords.c
INC = -Isrc -Iinclude
EXE   = a.out
CFLAGS = -g -Wunused-variable -Werror=return-type -Werror=unused-variable

.PHONY: all clean

all : $(BUILD)/$(EXE)

$(BUILD)/$(EXE): $(FILES)
	$(CC) -o $@ $+ $(CFLAGS) $(INC)
	mv $(BUILD)/$(EXE) $(BIN) 
clean:
	rm $(BIN)/$(EXE)

run:
	@$(BIN)/$(EXE)