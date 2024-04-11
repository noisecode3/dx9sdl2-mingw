CC := x86_64-w64-mingw32-g++
RC := x86_64-w64-mingw32-windres

CFLAGS := -Wall -Wextra -Wno-unused-parameter -O2 -std=c++20 -g

#LDFLAGS := -static-libgcc -static-libstdc++ -lSDL2 -lopengl32 -lglu32 -mwindows
LDFLAGS := -lmingw32 -lSDL2main -lSDL2 -ld3d9 -ld3dx9

#SRC := $(wildcard *.cpp)

#SRC := SDL2.cpp
SRC := DX9SDL2.cpp

OBJ := $(SRC:.cpp=.o)
RES := main.rc.o
EXE := my_program.exe

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(RES): main.rc
	$(RC) -o $@ $<

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(RES) $(EXE)
