# ==============================
# MAKEFILE PARA PROJETO EM C
# ==============================

# Compilador
CC = gcc

# Flags de compilação 
CFLAGS = -g3 -Wall -Wextra -finput-charset=UTF-8 -I.

# Objetos com os caminhos corretos das subpastas
OBJ = main.o \
      fila/fila.o \
      grafo/grafo.o \
      lista/lista.o \
      pilha/pilha.o 

# Executável
TARGET = main.exe

# Declaração de alvos fictícios/virtuais
.PHONY: all clean

# Regra padrão: compilação incremental automática
all: $(TARGET)

# Linkagem dos objetos
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# --- Regras de Compilação Individual ---
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

fila/fila.o: fila/fila.c fila/fila.h
	$(CC) $(CFLAGS) -c fila/fila.c -o fila/fila.o

grafo/grafo.o: grafo/grafo.c grafo/grafo.h
	$(CC) $(CFLAGS) -c grafo/grafo.c -o grafo/grafo.o

lista/lista.o: lista/lista.c lista/lista.h
	$(CC) $(CFLAGS) -c lista/lista.c -o lista/lista.o

pilha/pilha.o: pilha/pilha.c pilha/pilha.h
	$(CC) $(CFLAGS) -c pilha/pilha.c -o pilha/pilha.o

# Limpeza dos arquivos gerados (limpa os .o dentro das subpastas automaticamente)
clean:
	rm -f $(OBJ) $(TARGET)