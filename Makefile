CC = gcc
CFLAGS = -std=c99 -O2 -Wall -Wextra

NC_SRC = src/nc_core.c
NC_HEADERS = src/nc_tables.h
BRIDGE_SRC = HERRAMIENTAS/nc_legacy_bridge.c

ifeq ($(OS),Windows_NT)
    NC_TARGET := bin/neurocobol.exe
    NC_ROOT := neurocobol.exe
    BRIDGE_TARGET := bin/nc_legacy_bridge.exe
    BRIDGE_ROOT := nc_legacy_bridge.exe
    MKDIR = if not exist bin mkdir bin
    RM = del /Q /F
else
    NC_TARGET := bin/neurocobol
    NC_ROOT := neurocobol
    BRIDGE_TARGET := bin/nc_legacy_bridge
    BRIDGE_ROOT := nc_legacy_bridge
    MKDIR = mkdir -p bin
    RM = rm -f
endif

all: $(NC_TARGET) $(NC_ROOT) $(BRIDGE_TARGET) $(BRIDGE_ROOT)

$(NC_TARGET): $(NC_SRC) $(NC_HEADERS)
	$(MKDIR)
	$(CC) $(CFLAGS) $(NC_SRC) -o $(NC_TARGET)

$(NC_ROOT): $(NC_SRC) $(NC_HEADERS)
	$(CC) $(CFLAGS) $(NC_SRC) -o $(NC_ROOT)

$(BRIDGE_TARGET): $(BRIDGE_SRC)
	$(MKDIR)
	$(CC) $(CFLAGS) $(BRIDGE_SRC) -o $(BRIDGE_TARGET)

$(BRIDGE_ROOT): $(BRIDGE_SRC)
	$(CC) $(CFLAGS) $(BRIDGE_SRC) -o $(BRIDGE_ROOT)

test: all
	./$(NC_ROOT) --test
	./$(BRIDGE_ROOT) --test

clean:
	$(RM) $(NC_TARGET) $(NC_ROOT) $(BRIDGE_TARGET) $(BRIDGE_ROOT)

.PHONY: all test clean
