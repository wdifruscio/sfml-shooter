#ifndef QTREENODE_H
#define QTREENODE_H

#include <vector>
#include "QuadTree.h"
#include "QuadTreeObject.h"

typedef struct CVector2{
    int x, y;
    constexpr CVector2(int x, int y) : x(x), y(y){}
} vec2;

class QuadTreeNode{
    friend class QuadTree;
protected:
    std::vector<QuadTreeObject> mObjects;
    QuadTreeNode *mChildren[4];
    vec2 mCenter;
    vec2 mRadius;
public:
    QuadTreeNode();
    QuadTreeNode(const vec2 &pCenter, const vec2 &pRadius);
    ~QuadTreeNode();
    void SetCenterAndRadius(const vec2 &pCenter, const vec2 &pRadius);
    vec2 GetCenter() const;
    vec2 GetRadius() const;
    void SetChild(int index, QuadTreeNode *pNode);
    bool AddObject(QuadTreeObject *pObject);
    void RemoveObject(QuadTreeObject *pObject);
};

#endif
