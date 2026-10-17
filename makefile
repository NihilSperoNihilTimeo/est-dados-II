# ==============================
# MAKEFILE PARA PROJETO EM C
# ==============================

# Compilador
CC = gcc

# Flags de compilação 
CFLAGS = -g3 -Wall -Wextra -finput-charset=UTF-8 -I.

# Objetos comuns a ambos os programas
OBJ_COMUM = fila/fila.o \
            grafo/grafo.o \
            lista/lista.o \
            pilha/pilha.o \
			algoritmos/AGM.o \
            algoritmos/BEL.o \
			algoritmos/BEP.o \
			algoritmos/CC.o \
			algoritmos/CMC.o

# Objetos específicos de cada executável
OBJ_MAIN = main.o $(OBJ_COMUM)
OBJ_CRIACAO = criacaoGrafos.o $(OBJ_COMUM)

# Executáveis gerados
TARGET_MAIN = main
TARGET_CRIACAO = criacaoGrafos

# Declaração de alvos fictícios/virtuais
.PHONY: all clean

# Regra padrão: compila ambos os executáveis
all: $(TARGET_MAIN) $(TARGET_CRIACAO)

# Linkagem do programa principal
$(TARGET_MAIN): $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ_MAIN) -o $(TARGET_MAIN)

# Linkagem do programa de criação de grafos
$(TARGET_CRIACAO): $(OBJ_CRIACAO)
	$(CC) $(CFLAGS) $(OBJ_CRIACAO) -o $(TARGET_CRIACAO)

# --- Regras de Compilação Individual ---
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

criacaoGrafos.o: criacaoGrafos.c
	$(CC) $(CFLAGS) -c criacaoGrafos.c -o criacaoGrafos.o

fila/fila.o: fila/fila.c fila/fila.h
	$(CC) $(CFLAGS) -c fila/fila.c -o fila/fila.o

grafo/grafo.o: grafo/grafo.c grafo/grafo.h
	$(CC) $(CFLAGS) -c grafo/grafo.c -o grafo/grafo.o

lista/lista.o: lista/lista.c lista/lista.h
	$(CC) $(CFLAGS) -c lista/lista.c -o lista/lista.o

pilha/pilha.o: pilha/pilha.c pilha/pilha.h
	$(CC) $(CFLAGS) -c pilha/pilha.c -o pilha/pilha.o

algoritmos/AGM.o: algoritmos/AGM.c algoritmos/algoritmos.h
	$(CC) $(CFLAGS) -c algoritmos/AGM.c -o algoritmos/AGM.o

algoritmos/BEL.o: algoritmos/BEL.c algoritmos/algoritmos.h
	$(CC) $(CFLAGS) -c algoritmos/BEL.c -o algoritmos/BEL.o

algoritmos/BEP.o: algoritmos/BEP.c algoritmos/algoritmos.h
	$(CC) $(CFLAGS) -c algoritmos/BEP.c -o algoritmos/BEP.o

algoritmos/CC.o: algoritmos/CC.c algoritmos/algoritmos.h
	$(CC) $(CFLAGS) -c algoritmos/CC.c -o algoritmos/CC.o

algoritmos/CMC.o: algoritmos/CMC.c algoritmos/algoritmos.h
	$(CC) $(CFLAGS) -c algoritmos/CMC.c -o algoritmos/CMC.o
# Limpeza dos ficheiros gerados
clean:
	rm -f main.o criacaoGrafos.o $(OBJ_COMUM) $(TARGET_MAIN) $(TARGET_CRIACAO)