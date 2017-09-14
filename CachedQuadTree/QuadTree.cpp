#include <cstddef>
#include "QuadTree.h"
#include "QuadTreeNode.h"

bool QuadTree::CreateQuadTree(float initSizeX, float initSizeY){
    Reset();
    ui8Nodes = new uint8_t[QTREE_NODES*sizeof(QuadTreeNode)];
    if(!ui8Nodes) return false;
    QuadTreeNode *pNodes = Root();
    for(uint32_t QTREE_NODES; I--;){
        new(&pNodes[I]) QuadTreeNode();
    }

    inverseSizeX = static_cast<float>(255.0) / initSizeX;
    inverseSizeY = static_cast<float>(255.0) / initSizeY;
    return false;
}

void QuadTree::Reset(){
    if(ui8Nodes){
        QuadTreeNode *rootNode = Root();
        for(uint32_t I = QTREE_NODES; I--;)
            rootNode[I].~QuadTreeNode();
        delete[] ui8Nodes;
        ui8Nodes = NULL;
    }
}

QuadTreeNode* QuadTree::Root() const{
    return ptnLevels[0];
}
