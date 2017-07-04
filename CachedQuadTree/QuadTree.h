#ifndef QTREE_NODES
#define QTREE_NODES (1UL + 2UL*2UL + 4UL*4UL + 8UL*8UL + 16UL*16UL + 32UL*32UL + 64UL*64UL + 128UL*128UL)

#include <cstddef>
#include <stdint.h>
#include "QuadTreeNode.h"

class QuadTreeNode;

typedef struct Screen{
    int x, y, width, height;
    Screen(int x, int y, int w, int h) :
    x(x), y(y), width(w), height(h) {}
} Screen;

class QuadTree{
protected:
    uint8_t *ui8Nodes;
    QuadTreeNode *ptnLevels[6];
    float inverseSizeX;
    float inverseSizeY;
    Screen screen;
    QuadTreeNode *root;
public:
    QuadTree();
    ~QuadTree();
    bool CreateQuadTree(std::size_t initSize);
    void Reset();
    QuadTreeNode* Root() const{ return root; };
};

#endif
