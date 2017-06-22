#include <vector>
#include <algorithm>
#include "QuadTreeNode.h"

QuadTreeNode::QuadTreeNode(const vec2 &pCenter, const vec2 &pRadius) :
mCenter(pCenter), mRadius(pRadius)
{
}

void QuadTreeNode::SetCenterAndRadius(const vec2 &pCenter, const vec2 &pRadius){
    mCenter = pCenter;
    mRadius = pRadius;
}

vec2 QuadTreeNode::GetCenter() const{
    return mCenter;
}

vec2 QuadTreeNode::GetRadius() const{
    return mRadius;
}

void QuadTreeNode::SetChild(int index, QuadTreeNode *pNode){
    mChildren[index] = pNode;
}

bool QuadTreeNode::AddObject(QuadTreeObject *pObject){
    mObjects.push_back(*(pObject));
    return true;
}

void QuadTreeNode::RemoveObject(QuadTreeObject *pObject){
    mObjects.erase(std::remove(mObjects.begin(), mObjects.end(), *(pObject)), mObjects.end());
}
