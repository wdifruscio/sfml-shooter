#include <vector>
#include <array>

#include "Quad.h"

Quad::Quad(int pLevel, const Rect &rect, Quad *parent = nullptr) :
level(pLevel), bounds(rect), parent(parent)
{
}

Quad::~Quad(){
    this->clear();
}

void Quad::clear(){
    objects.clear();
    for(unsigned int i = 0; i < sizeof(nodes)/sizeof(Quad); i++){
        if(nodes[i] != NULL){
            nodes[i]->clear();
            nodes[i] = NULL;
        }
    }
}

void Quad::split(){
    int center_x = (bounds.right - bounds.left) / 2;
    int center_y = (bounds.top - bounds.bottom) / 2;
                                                                                                                            //               ___________
    nodes[0] = new Quad(level + 1, Rect(bounds.right, bounds.left + center_x, bounds.top, bounds.bottom - center_y), this); // top-right    |  Q1 |  Q0 |
    nodes[1] = new Quad(level + 1, Rect(bounds.right - center_x, bounds.left, bounds.top, bounds.bottom - center_y), this); // top-left     |_____|_____|
    nodes[2] = new Quad(level + 1, Rect(bounds.right - center_x, bounds.left, bounds.top + center_y, bounds.bottom), this); // bottom-left  |  Q2 |  Q3 |
    nodes[3] = new Quad(level + 1, Rect(bounds.right, bounds.left + center_x, bounds.top + center_y, bounds.bottom), this); // bottom-right |_____|_____|
}

void Quad::insert(QuadObject *qo){
    if(nodes[0] != NULL){
        int index = get_index(qo);
        if(index > 0){
            nodes[index]->insert(qo);
            return;
        }
    }
    objects.push_back(qo);
    if((int)objects.size() > MAX_OBJECTS && level < MAX_LEVELS){
        if(nodes[0] == NULL)
            split();
        size_t i = 0;
        while(i < objects.size()){
            QuadObject o = objects.at(i);
            int index = get_index(o);
            if(index > 0){
                nodes[index]->insert(o);
                objects.erase(objects.begin() + i);
            }
            else
                i++;
        }
    }
}

std::vector<QuadObject*> Quad::retrieve(std::vector<QuadObject*> return_objects, QuadObject *qo){
    int index = get_index(qo);
    // Checks to see if the object can fit in a smaller scope and if the current node is a leaf node
    if(index > 0 && nodes[0] != NULL)
        nodes[index]->retrieve(return_objects, qo);

    return_objects.reserve(return_objects.size() + objects.size()); //preallocate memory for concat
    return_objects.insert(return_objects.end(), objects.begin(), objects.end()); // add all elements on objects to return_objects

    return return_objects;
}

void Quad::Update(){

}

// PRIVATE
int Quad::get_index(QuadObject *qo){
    int index = -1;
    int center_x = (bounds.right - bounds.left) / 2;
    int center_y = (bounds.top - bounds.bottom) / 2;

    // Can fit in top Quadrants
    bool top_quad = (((qo->pos.y + qo->pos.rad) < center_y) && (qo->pos.y - qo->pos.rad) > bounds.top);
    // Can fit in bottom Quadrants
    bool bottom_quad = ((qo->pos.y - qo->pos.rad) > center_y) && ((qo->pos.y + qo->pos.rad) < bounds.bottom);
    // Can fit in left Quadrants
    if(((qo->pos.x + qo->pos.rad) < center_x) && ((qo->pos.x - qo->pos.rad) > bounds.left)){
        if(top_quad)
            index = 1;
        else if(bottom_quad)
            index = 2;
    }
    // Can fit in right Quadrants
    if(((qo->pos.x - qo->pos.rad) > center_x) && ((qo->pos.x + qo->pos.rad) > bounds.right)){
        if(top_quad)
            index = 0;
        else if(bottom_quad)
            index = 3;
    }
    return index;
}
