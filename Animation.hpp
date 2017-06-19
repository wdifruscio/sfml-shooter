#ifndef ANIMATION
#define ANIMATION

#include <SFML/Graphics.hpp>
#include <string>

class Animation
{
    public:
    float Frame, speed;
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;
    Animation(sf::Texture &t, int x, int y, int w, int h, int count, float Speed);
    void update();
    int n;
};

#endif