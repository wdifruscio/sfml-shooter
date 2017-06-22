#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>

namespace Physics{

    class Collision{
    private:
        float Cross(const sf::Vector2f &a, const sf::Vector2f &b){
            return (a.x*b.y) - (a.y*b.x);
        }
        sf::Vector2f Cross(const sf::Vector2f &a, float s){
            return sf::Vector2f(s*a.y, -s*a.x);
        }
        sf::Vector2f Cross(float s, const sf::Vector2f &a){
            return sf::Vector2f(s*a.y, -s*a.x);
        }
    };

}    

#endif
