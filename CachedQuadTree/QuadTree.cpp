#include <cstddef>
#include "QuadTree.h"
#include "QuadTreeNode.h"

bool QuadTree::CreateQuadTree(std::size_t initSize){
    Reset();
    ui8Nodes = new uint8_t[QTREE_NODES*sizeof(QuadTreeNode)];
    if(!ui8Nodes) return false;
    QuadTreeNode *pNodes = Root();
    for(uint32_t I = QTREE_NODES; I--;){
        new(&pNodes[I])QuadTreeNode();
    }
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
