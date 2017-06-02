#ifndef PLAYER 
#define PLAYER

#include <SFML/Graphics.hpp>
#include <string>

class Player
{
    public:
    Player(sf::Texture &texture);
    ~Player();
    sf::Sprite sprite;
    double speed;
};

#endif