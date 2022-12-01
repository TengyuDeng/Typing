CXX := g++
CXX_FLAGS := -std=c++17

BIN := bin
SRC := src
INCLUDE := include

CFLAGS = -I/usr/local/include
LINKER_FLAGS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer -lSDL2_ttf

EXECUTABLE := myGame

all: macOS

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

clean:
	rm -r $(BIN)/*

macOS: $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(CFLAGS) $(LINKER_FLAGS)