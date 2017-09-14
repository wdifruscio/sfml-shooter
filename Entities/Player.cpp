#include "Player.hpp"
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>


namespace Entities {

    Player::Player(){
        sf::Texture t;
        t.loadFromFile("assets/ship.png");
        setTexture(t);
        bindTexture();

        sf::Vector2f vel(5.0f, 5.0f);
        setVelocity(vel);

        sf::Vector2f pos(50,440);
        setPosition(pos);
        std::cout << "START  " << position.x << "  " << position.y << std::endl;

        shape = new sf::ConvexShape(4);
        sf::Vector2f newPointPosition (position.x -15, position.y - 15);
        shape->setPoint(0, newPointPosition);

        newPointPosition.x = position.x + 15; newPointPosition.y = position.y - 15;
        shape->setPoint(1, newPointPosition);

        newPointPosition.x = position.x + 15; newPointPosition.y = position.y + 15;
        shape->setPoint(2, newPointPosition);

        newPointPosition.x = position.x - 15; newPointPosition.y = position.y + 15;
        shape->setPoint(3, newPointPosition);

        //sprite.setPosition(position);
        std::cout << "LEFT  " << sprite.getLocalBounds().left << std::endl;
        std::cout << "TOP  " << sprite.getLocalBounds().top << std::endl;
        std::cout << "HEIGHT  " << sprite.getLocalBounds().height << std::endl;
        std::cout << "WIDTH  " << sprite.getLocalBounds().width << std::endl;
    };

    Player::~Player(){};

    void Player::handleSprite(sf::Keyboard::Key key)
    {
        sf::Vector2f pos = getPosition();
        sf::Vector2f vel = getVelocity();
        sf::Vector2f newPos(pos.x, pos.y);
        if(key == sf::Keyboard::Right && position.x < 1440) newPos.x += vel.x;
        if(key == sf::Keyboard::Left && position.x > 0) newPos.x -= vel.x;
        if(key == sf::Keyboard::Up && position.y > 0) newPos.y -= vel.y;
        if(key == sf::Keyboard::Down && position.y < 900) newPos.y += vel.y;

        setPosition(newPos);
        //this->sprite.setPosition(this->position);
        std::cout << "pos.x: " << newPos.x << "  pos.y: " << newPos.y << std::endl;
        std::cout << "LEFT  " << this->sprite.getLocalBounds().left << std::endl;
        std::cout << "TOP  " << this->sprite.getLocalBounds().top << std::endl;
        std::cout << "HEIGHT  " << this->sprite.getLocalBounds().height << std::endl;
        std::cout << "WIDTH  " << this->sprite.getLocalBounds().width << std::endl;
        std::cout << "\n\n" << std::endl;
    }

    void Player::update(){
        sprite.setPosition(getPosition());
    }

    void update(){}
    void setEntityBounds(){}

}
