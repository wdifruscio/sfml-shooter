#include "QuadTreeObject.h"
#include "QuadTreeNode.h"

QuadTreeObject::QuadTreeObject(){}

void QuadTreeObject::SetQuadTreeNode(QuadTreeNode *pNode){
    mNode = pNode;
}

QuadTreeNode* QuadTreeObject::GetQuadTreeNode() const{
    return mNode;
}

bool QuadTreeObject::operator==(const QuadTreeObject &node){
    return mNode == node.mNode;
}
