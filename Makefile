
OBJS = main.cpp Player.cpp Quad.cpp QuadTreeObject.cpp QuadTreeNode.cpp QuadTree.cpp
CC = g++
COMPILER_FLAGS = -W -std=c++11
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJ_NAME = sfml-game

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm -rf *.o
