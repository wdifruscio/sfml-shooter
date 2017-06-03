#ifndef BULLET 
#define BULLET

#include <SFML/Graphics.hpp>
#include <string>

class Bullet
{
    public:
    Bullet(int x, int y, sf::Texture &texture);
    ~Bullet();
    sf::Sprite sprite;
    int x;
    int y;
};

#endif