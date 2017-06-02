#include "Player.hpp"
#include <SFML/Graphics.hpp>

Player::Player(sf::Texture &texture)
{
    sprite.setTexture(texture);
};

Player::~Player(){};

void Player::handleSprite()
{
    if(sprite.getPosition().x > 525)
    {
        sprite.setPosition(525, sprite.getPosition().y);
    }

    if(sprite.getPosition().x < -20)
    {
        sprite.setPosition(-20,sprite.getPosition().y);
    }

    if(sprite.getPosition().y < 0) {
        sprite.setPosition(sprite.getPosition().x, 0);
    }
    
    if(sprite.getPosition().y > 725) {
        sprite.setPosition(sprite.getPosition().x, 725);
    }
}