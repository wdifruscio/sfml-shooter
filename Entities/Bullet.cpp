#include "Bullet.hpp"
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Entities
{
    Bullet::Bullet()
    {
        sf::Texture t;
        t.loadFromFile("assets/bullet.png");
        setTexture(t);
        bindTexture();

        sf::Vector2f vel(5.0f, 5.0f);
        setVelocity(vel);
    };

    Bullet::~Bullet(){};

    void Bullet::update()
    {
        sf::Vector2f pos = getPosition();
        pos.x += 20;
        setPosition(pos);
        sprite.setPosition(pos);

        if(pos.x > 1440 || pos.x < 0 || pos.y > 900 || pos.y < 0) {
            isAlive = false;
        }
    }
}