#include "Player.hpp"
#include <SFML/Graphics.hpp>

Player::Player(sf::Texture &texture)
{
    sprite.setTexture(texture);
};

Player::~Player(){};