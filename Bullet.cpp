#include "Bullet.hpp"
#include <SFML/Graphics.hpp>

Bullet::Bullet(int x, int y, sf::Texture &texture) {
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
};

Bullet::~Bullet() {};