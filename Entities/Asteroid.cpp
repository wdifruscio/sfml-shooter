#include "Asteroid.hpp"
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Entities
{
    Asteroid::Asteroid(){
        sf::Texture t;
        t.loadFromFile("assets/asteroid_1.png");
        setTexture(t);
        bindTexture();

        sf::Vector2f vel(5.0f, 5.0f);
        setVelocity(vel);
    };

    Asteroid::~Asteroid(){};

    void Asteroid::update()
    {
        sf::Vector2f pos = getPosition();
        sf::Vector2f vel = getVelocity();
        sf::Vector2f newPos(pos.x += vel.x, pos.y += vel.y);
        setPosition(newPos);
        sprite.setPosition(getPosition());
        if(pos.x > 1440 || pos.x < 0 || pos.y > 900 || pos.y < 0) {
            isAlive = false;
        }
    }
}
