
OBJS = main.cpp Player.cpp Quad.cpp
CC = g++
COMPILER_FLAGS = -W
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -std=c++11
OBJ_NAME = sfml-game

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm -rf *.o
