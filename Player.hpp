#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>
#include <string>

class Player
{
    public:
    Player(sf::Texture &texture, int start_x, int start_y, int init_speed);
    ~Player();
    void handleSprite();
    sf::Sprite sprite;
    int speed;
    int x;
    int y;
};

#endif
