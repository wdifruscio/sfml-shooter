#include <cstddef>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <algorithm>
#include "Quad.hpp"
#include "../Entities/Entity.hpp"

namespace Physics{

    //*==========================================================*//
    // Create Quad Tree
    // Better Description Coming Soon!
    //*==========================================================*//

    bool QuadTree::CreateQuadTree(const sf::Vector2f &screen){
        Reset();
        QuadNode *pNodes = Root();
        for(uint I = QUAD_NODES; I--;)
            new(&pNodes[I]) QuadNode();

        sizeRatio.x = (1UL << SIZE)/screen.x; sizeRatio.y = (1UL << SIZE)/screen.y;

        QuadNode *pThis = pNodes, *pLast = NULL;
        sf::Vector2f fFull = screen;
        sf::Vector2f _fSize = screen;
        _fSize *= 0.5f;
        screenSize = screen;

        sf::Vector2f vOffset(-_fSize.x, -_fSize.y);
        for(uint I = 0UL; I < LEVELS; ++I){
            nodeLevels[I] = pThis;

            for(uint Y = (1UL << I); Y--;){
                QuadNode *pRow = &pThis[Y*(1UL<<I)];
                float fYPos = (float(Y) / float(1UL << I)) * fFull.y + _fSize.y;

                for(uint X = (1UL << I); X--;){
                    float fXPos = (float(X) / float(1UL << I)) * fFull.x + _fSize.x;
                    sf::Vector2f pos(fXPos, fYPos);
                    pRow[X].SetCenterAndRadius(pos + vOffset, _fSize);

                    if(pLast){
                        uint parentX = X >> 1UL;
                        uint parentY = Y >> 1UL;
                        uint parentIndex = (parentY * (1UL << (I - 1UL))) + parentX;
                        uint x = X & 1UL;
                        uint y = Y & 1UL;
                        uint childIndex = (y << 1UL) + x;
                        pThis[childIndex].SetLevel(I);
                        pThis[childIndex].SetParentIndex(parentIndex);
                        pLast[parentIndex].SetChild((y << 1UL) + x, &pRow[X]);
                    }
                }
            }

            pLast = pThis;
            pThis += (1UL << I) * (1UL << I);
            _fSize *= 0.5f;
        }

        return true;
    }

    void QuadTree::Reset(){
        if(Root() != NULL){
            QuadNode *listNodes = Root();
            for(uint32_t I = QUAD_NODES; I--;)
                listNodes[I].~QuadNode();
            delete[] listNodes;
            root = nullptr;
        }
    }

    QuadNode* QuadTree::InsertObject(Entity *pObject){
        Entities::Bounds rangeBox = pObject->getBounds();
        if(rangeBox.minX < 0 || rangeBox.maxX > screenSize.x || rangeBox.minY < 0 || rangeBox.maxY > screenSize.y){
            if(rangeBox.maxX < -40 || (rangeBox.minX > screenSize.x + 40) || rangeBox.maxY < -40 || (rangeBox.minY > screenSize.y + 40)){
                pObject->isAlive =  false;
                return nullptr;
            }
            Root()->AddObject(pObject);
            return Root();
        }

        Entities::Bounds squashBox(rangeBox.minX*sizeRatio.x
            , rangeBox.maxX*sizeRatio.x
            , rangeBox.minY*sizeRatio.y
            , rangeBox.maxY*sizeRatio.y);

        uint minX = static_cast<uint>(floor(squashBox.minX));
        uint maxX = static_cast<uint>(ceil(squashBox.maxX));
        uint minY = static_cast<uint>(floor(squashBox.minY));
        uint maxY = static_cast<uint>(ceil(squashBox.maxY));

        uint xMinMaxXOR = ((minX ^ maxX) >> (SIZE - LEVELS));
        uint yMinMaxXOR = ((minY ^ maxY) >> (SIZE - LEVELS));

        uint xLevel = 5UL - GetLevel(xMinMaxXOR);
        uint yLevel = 5UL - GetLevel(yMinMaxXOR);
        uint level = std::min(xLevel, yLevel);

        uint x = minX >> (SIZE - level);
        uint y = minY >> (SIZE - level);

        QuadNode *pNode = &nodeLevels[level][y*(1UL << level) + x];
        pNode->AddObject(pObject);
        return pNode;
    }

    uint GetLevel(uint num){
        uint i = 0;
        while(num > 1){
            num = num >> 1;
            i++;
        }
        return i;
    }

}
