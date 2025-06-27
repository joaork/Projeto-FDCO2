# Compilador e flags
CC = gcc
CFLAGS = -Wall -std=c99 -I"C:/raylib/include"
LDFLAGS = -L"C:/raylib/lib" -lraylib -lopengl32 -lgdi32 -lwinmm

# Fontes e destino
SRC = main.c funcoes.c menu.c game.c
OBJ = $(SRC:.c=.o) raygui.o
BIN = jogo_milhao

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN).exe $(OBJ) $(LDFLAGS)

clean:
	del /Q *.o *.exe 2>nul

run: all
	./$(BIN).exe