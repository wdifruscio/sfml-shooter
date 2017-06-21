#ifndef QUADTREEOBJ_H
#define QUADTREEOBJ_H

#include "AABB.h"

class QuadTreeNode;

class QuadTreeObject{
private:
protected:
    QuadTreeNode *mNode;
public:
    void SetQuadTreeNode(QuadTreeNode *pNode);
    virtual const AABB& QuadTreeAabb();
    QuadTreeNode* GetQuadTreeNode() const;
    bool operator== (QuadTreeObject const &node);
    QuadTreeObject();
    ~QuadTreeObject();
};

#endif
