#include "Player.hpp"
#include <SFML/Graphics.hpp>

namespace Entities
{
    Player::Player(sf::Texture &texture, int start_x, int start_y, int initSpeed){
        setTexture(texture);
        bindTexture();
        x = start_x; y = start_y; speed = initSpeed; // Inital starting position and speed
        sf::FloatRect localBounds = sprite.getLocalBounds();
        w = localBounds.width;
        h = localBounds.height;
        sprite.setPosition(x,y);
    };

    Player::~Player(){};

    void Player::handleSprite() 
    {
        if(x > 1440) x -= speed;
        if(x < -20) x += speed;
        if(y  <  0) y += speed;
        if(y > 900) y -= speed;
    }

    void Player::update()
    {
        handleSprite();
        sprite.setPosition(x,y);
    }
}
