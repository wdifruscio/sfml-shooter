#include "Player.hpp"
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Entities
{
    Player::Player(){
        sf::Texture t;
        t.loadFromFile("assets/ship.png");
        setTexture(t);
        bindTexture();
        sf::Vector2f vel(5.0f, 5.0f);        
        setVelocity(vel);
        sf::Vector2f pos(50,440);
        setPosition(pos);
    };

    Player::~Player(){};

    void Player::handleSprite(sf::Keyboard::Key key) 
    {
        sf::Vector2f pos = getPosition();
        sf::Vector2f vel = getVelocity();
        sf::Vector2f newPos(pos.x, pos.y);
        if(key == sf::Keyboard::Right) newPos.x += vel.x; 
        if(key == sf::Keyboard::Left) newPos.x -= vel.x;
        if(key == sf::Keyboard::Up) newPos.y -= vel.y;
        if(key == sf::Keyboard::Down) newPos.y += vel.y;
        setPosition(newPos);
        std::cout << "pos.x: " << newPos.x << "pos.y " << newPos.y << std::endl;
    }

    void Player::update()
    {
        sprite.setPosition(getPosition());
    }
}
