CC = gcc
BUILD = build
BIN   = bin
FILES = src/main.c src/Mace/cell_stack.c
INC = -Isrc -Iinclude
EXE   = a.out
CFLAGS = -g

.PHONY: all clean

all : $(BUILD)/$(EXE)

$(BUILD)/$(EXE): $(FILES)
	$(CC) -o $@ $+ $(CFLAGS) $(INC)
	mv $(BUILD)/$(EXE) $(BIN) 
clean:
	rm $(BIN)/$(EXE)

run: 
	@$(BIN)/$(EXE)