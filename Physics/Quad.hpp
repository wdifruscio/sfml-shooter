#ifndef QUAD_NODES
#define QUAD_NODES (1UL + 2UL*2UL + 4UL*4UL + 8UL*8UL + 16UL*16UL + 32UL*32UL)

#include <math.h>
#include <array>
#include <vector>
#include <algorithm>
#include "../Entities/Entity.hpp"

using Entities::Entity;

namespace Physics{

    enum types{
        PLAYER,
        BULLET,
        ENEMY,
        ASTEROID
    };

    typedef struct Rectangle{
        float right, left, top, bottom;
        constexpr Rectangle(float r, float l, float t, float b) :
        right(r), left(l), top(t), bottom(b){}
    } Rect;

    class Quad{
    private:
        int MAX_OBJECTS = 10;
        int MAX_LEVELS = 5;
        int level;
        std::vector<Entity*> objects;
        Rect bounds;
        Quad *nodes[4];
        int get_index(Entity *qo);
        void CheckQuads(Entity *qo, Quad *q);
        Quad *parent;
    public:
        Quad(int pLevel, const Rect &rect, Quad *parent);
        ~Quad();
        void clear();
        void split();
        void insert(Entity *qo);
        std::vector<Entity*> retrieve(std::vector<Entity*> retObj, Entity *qo);
    };

    class QuadNode{
    private:
    protected:
        std::vector<Entity*> objects;
        sf::Vector2f center;
        sf::Vector2f radius;
        QuadNode *children[4];
        int parentIndex;
        int level;
    public:
        void AddObject(Entity *obj){
            objects.push_back(obj);
        }

        void RemoveObject(Entity *obj){
            objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
        }

        void SetChild(int index, QuadNode *pNode){
            children[index] = pNode;
        }

        void SetCenterAndRadius(const sf::Vector2f &center, const sf::Vector2f &radius){
            this->center = center;
            this->radius = radius;
        }

        void SetParentIndex(int index){
            parentIndex = index;
        }

        void SetLevel(int level){
            this->level = level;
        }

        sf::Vector2f GetRadius() const { return radius; }
        sf::Vector2f GetCenter() const { return center; }
    };

    class QuadTree{
    private:
        const uint SIZE = 10;
        const uint LEVELS = 6;
        uint GetLevel(int num);
    protected:
        QuadNode *root;
        sf::Vector2f sizeRatio;
        sf::Vector2f screenSize;
        QuadNode *nodeLevels[6];
    public:
        ~QuadTree(){Reset();}
        QuadNode* Root() { return root; }
        bool CreateQuadTree(const sf::Vector2f &screen);
        QuadNode* InsertObject(Entity *pObject);
        void Reset();
        std::vector<Entity*> Retrieve(QuadNode * qn); 
    };

}

#endif
