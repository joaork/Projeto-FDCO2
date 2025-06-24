# Compilador e flags
CC = gcc
CFLAGS = -Wall -std=c99

# Fontes e destino
SRC = main.c funcoes.c menu.c game.c
OBJ = $(SRC:.c=.o)
BIN = jogo_milhao

# Regra principal
all: $(BIN)

# Como construir o binário
$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

# Limpar objetos e binários
clean:
	del /Q *.o *.exe 2>nul

# Executar
run: all
	./$(BIN)