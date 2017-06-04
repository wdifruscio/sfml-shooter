#include "Player.hpp"
#include <SFML/Graphics.hpp>

Player::Player(sf::Texture &texture, int start_x, int start_y, int initSpeed)
{
    sprite.setTexture(texture);
    x = start_x; y = start_y; speed = initSpeed; // Inital starting position and speed
};

Player::~Player(){};

void Player::handleSprite()
{
    if(x > 525) x -= speed;
    if(x < -20) x += speed;
    if(y  <  0) y += speed;
    if(y > 725) y -= speed;
}
