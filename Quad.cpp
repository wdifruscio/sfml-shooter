#include <vector>
#include <array>

#include "Quad.h"

Quad::Quad(int pLevel, const Rect &rect) :
level(pLevel), bounds(rect)
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
    nodes[0] = new Quad(level + 1, Rect(bounds.right, bounds.left + center_x, bounds.top, bounds.bottom - center_y)); // top-right    |  Q1 |  Q0 |
    nodes[1] = new Quad(level + 1, Rect(bounds.right - center_x, bounds.left, bounds.top, bounds.bottom - center_y)); // top-left     |_____|_____|
    nodes[2] = new Quad(level + 1, Rect(bounds.right - center_x, bounds.left, bounds.top + center_y, bounds.bottom)); // bottom-left  |  Q2 |  Q3 |
    nodes[3] = new Quad(level + 1, Rect(bounds.right, bounds.left + center_x, bounds.top + center_y, bounds.bottom)); // bottom-right |_____|_____|
}

void Quad::insert(const object &obj){
    if(nodes[0] != NULL){
        int index = get_index(obj);
        if(index > 0){
            nodes[index]->insert(obj);
            return;
        }
    }
    objects.push_back(obj);
    if((int)objects.size() > MAX_OBJECTS && level < MAX_LEVELS){
        if(nodes[0] == NULL)
            split();
        size_t i = 0;
        while(i < objects.size()){
            object o = objects.at(i);
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

std::vector<object> Quad::retrieve(std::vector<object> return_objects, const object &obj){
    int index = get_index(obj);
    // Checks to see if the object can fit in a smaller scope and if the current node is a leaf node
    if(index > 0 && nodes[0] != NULL)
        nodes[index]->retrieve(return_objects, obj);

    return_objects.reserve(return_objects.size() + objects.size()); //preallocate memory for concat
    return_objects.insert(return_objects.end(), objects.begin(), objects.end()); // add all elements on objects to return_objects

    return return_objects;
}

void SetTreeNode(Quad *_pqtnNode){
    //_pqtnNode->objects
}

// PRIVATE
int Quad::get_index(const object &obj){
    int index = -1;
    int center_x = (bounds.right - bounds.left) / 2;
    int center_y = (bounds.top - bounds.bottom) / 2;

    // Can fit in top Quadrants
    bool top_quad = ((obj.y + obj.rad) < center_y) && ((obj.y - obj.rad) > bounds.top);
    // Can fit in bottom Quadrants
    bool bottom_quad = ((obj.y - obj.rad) > center_y) && ((obj.y + obj.rad) < bounds.bottom);
    // Can fit in left Quadrants
    if(((obj.x + obj.rad) < center_x) && ((obj.x - obj.rad) > bounds.left)){
        if(top_quad)
            index = 1;
        else if(bottom_quad)
            index = 2;
    }
    // Can fit in right Quadrants
    if(((obj.x - obj.rad) > center_x) && ((obj.x + obj.rad) > bounds.right)){
        if(top_quad)
            index = 0;
        else if(bottom_quad)
            index = 3;
    }
    return index;
}
