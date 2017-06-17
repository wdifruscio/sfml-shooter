#ifndef QUAD_H
#define QUAD_H

#include <math.h>
#include <array>
#include <vector>

enum types{
    PLAYER,
    BULLET,
    ENEMY,
    ASTEROID
};

typedef struct Rectangle{
    int right, left, top, bottom;
    constexpr Rectangle(int r, int l, int t, int b) :
    right(r), left(l), top(t), bottom(b){}
} Rect;

typedef struct obect{
    int x, y, type, rad;
} object;

class Quad{
private:
    int MAX_OBJECTS = 10;
    int MAX_LEVELS = 5;
    int level;
    std::vector<object> objects;
    Rect bounds;
    Quad *nodes[4];
    void SetTreeNode(Quad *_pqtnNode);
    int get_index(const object &obj);
public:
    Quad(int pLevel, const Rect &rect);
    ~Quad();
    void clear();
    void split();
    void insert(const object &obj);
    void update();
    std::vector<object> retrieve(std::vector<object> retObj, const object &obj);
};


#endif
