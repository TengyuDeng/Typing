CXX := g++
CXX_FLAGS := -std=c++17

BIN := bin
SRC := src
INCLUDE := include

CFLAGS = -I/usr/local/include
LINKER_FLAGS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer -lSDL2_ttf

EXECUTABLE := myGame

all: macOS win32 win64

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

clean:
	rm -r $(BIN)/*

macOS: $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(CFLAGS) $(LINKER_FLAGS)

# For Windows 32 bit
PREFIX_WIN32 := i686-w64-mingw32
CXX_WIN32 := $(PREFIX_WIN32)-g++

CFLAGS_WIN32 = -I/usr/local/$(PREFIX_WIN32)/include -Dmain=SDL_main -static-libgcc -static-libstdc++
LINKER_FLAGS_WIN32 = $(shell /usr/local/$(PREFIX_WIN32)/bin/sdl2-config --static-libs) \
	/usr/local/$(PREFIX_WIN32)/lib/libSDL2_image.a \
	/usr/local/$(PREFIX_WIN32)/lib/libSDL2_ttf.a \
	/usr/local/$(PREFIX_WIN32)/lib/libSDL2_mixer.a \
	-lusp10 -lgdi32 -lrpcrt4 -lwinmm \
	-Wl,-Bstatic -lstdc++ -lpthread

# Dynamic links (failed)
# LINKER_FLAGS = $(shell /usr/local/$(PREFIX)/bin/sdl2-config --libs) \
# 	-lSDL2_image -lSDL2_ttf -lSDL2_mixer \
# 	-Wl,-Bstatic -lstdc++ -lpthread

EXECUTABLE_WIN32 := myGame-win32.exe

win32: $(BIN)/$(EXECUTABLE_WIN32)
$(BIN)/$(EXECUTABLE_WIN32): $(SRC)/*.cpp
	$(CXX_WIN32) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ -m32 $(CFLAGS_WIN32) $(LINKER_FLAGS_WIN32)

# For Windows 64 bit
PREFIX_WIN64 := x86_64-w64-mingw32
CXX_WIN64 := $(PREFIX_WIN64)-g++

CFLAGS_WIN64 = -I/usr/local/$(PREFIX_WIN64)/include -Dmain=SDL_main -static-libgcc -static-libstdc++
LINKER_FLAGS_WIN64 = $(shell /usr/local/$(PREFIX_WIN64)/bin/sdl2-config --static-libs) \
	/usr/local/$(PREFIX_WIN64)/lib/libSDL2_image.a \
	/usr/local/$(PREFIX_WIN64)/lib/libSDL2_ttf.a \
	/usr/local/$(PREFIX_WIN64)/lib/libSDL2_mixer.a \
	-lusp10 -lgdi32 -lrpcrt4 -lwinmm \
	-Wl,-Bstatic -lstdc++ -lpthread

EXECUTABLE_WIN64 := myGame-win64.exe

win64: $(BIN)/$(EXECUTABLE_WIN64)
$(BIN)/$(EXECUTABLE_WIN64): $(SRC)/*.cpp
	$(CXX_WIN64) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ -m64 $(CFLAGS_WIN64) $(LINKER_FLAGS_WIN64)
