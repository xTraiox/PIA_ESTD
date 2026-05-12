# ═══════════════════════════════════════════════════════════
#  Makefile — Dijkstra Corredor Industrial NL
#  Compatible con: MinGW (Windows) y GCC (Linux/Mac)
# ═══════════════════════════════════════════════════════════

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude
SRC     = src/main.c src/grafo.c src/heap.c src/datos_nl.c

# Windows (MinGW)
ifeq ($(OS),Windows_NT)
    OUT = dijkstra_nl.exe
    RM  = del /Q
else
    OUT = dijkstra_nl
    RM  = rm -f
endif

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	$(RM) $(OUT)

.PHONY: all clean
