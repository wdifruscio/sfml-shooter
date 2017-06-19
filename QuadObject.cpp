#include "Quad.h"

QuadObject::QuadObject(const object &obj)
: obj(obj)
{
}

QuadObject::QuadObject(const object &obj, Quad *initNode)
: mNode(initNode), obj(obj)
{
}

void QuadObject::SetQuadTreeNode(Quad *pNode){
    mNode = pNode;
}

Quad* QuadObject::GetQuadTreeNode(){
    return mNode;
}
