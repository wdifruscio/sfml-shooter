#ifndef QUAD_H
#define QUAD_H

#include <math.h>
#include <array>
#include <vector>

class QuadObject;

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

typedef struct Position{
    int x, y, type, rad;
    Position(int x, int y, int t, int r)
    : x(x), y(y), type(t), rad(r) {}
} Position;

class Quad{
private:
    int MAX_OBJECTS = 10;
    int MAX_LEVELS = 5;
    int level;
    std::vector<QuadObject*> objects;
    Rect bounds;
    Quad *nodes[4];
    int get_index(QuadObject *qo);
    void CheckQuads(QuadObject *qo, Quad *q);
    Quad *parent;
public:
    Quad(int pLevel, const Rect &rect, Quad *parent);
    ~Quad();
    void clear();
    void split();
    void insert(QuadObject *qo);
    void Update();
    std::vector<QuadObject*> retrieve(std::vector<QuadObject*> retObj, QuadObject *qo);
};

class QuadObject{
private:
protected:
    Quad *mNode;
public:
    QuadObject();
    QuadObject(const Position &pos);
    QuadObject(const Position &pos, Quad *initNode);
    void SetQuadTreeNode(Quad *pNode);
    Quad* GetQuadTreeNode();
    Position pos;
};


#endif
