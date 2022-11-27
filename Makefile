MKDIR     := mkdir
RMDIR     := rm -r
INCLUDE   := src
INCLUDEL  := libs
BIN       := .
OBJ       := obj
SRC       := src
CC        := g++
DBG_FLAGS :=-g -DDEBUG
OPT_FLAGS :=-o3 -DNDEBUG
CFLAGS    := -std=c++2a -I$(INCLUDE) -isystem libs -Wall
LDLIBS    := -lGL -lGLEW -lglfw -lpthread
SRCS      := $(wildcard $(SRC)/*.cc)
HHS       := $(wildcard $(SRC)/*.hh)
OBJS      := $(patsubst $(SRC)/%.cc,$(OBJ)/%.o,$(SRCS))
EXE       := $(BIN)/program


.PHONY: all run clean

all: $(EXE)

$(EXE): $(OBJS) | $(BIN)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(OBJ)/%.o: $(SRC)/%.cc | $(OBJ)
	$(CC) $(CFLAGS) $(DBG_FLAGS) -c $< -o $@

$(BIN) $(OBJ):
	$(MKDIR) $@

run: $(EXE)
	./$<

clean:
	$(RMDIR) $(OBJ) $(EXE)