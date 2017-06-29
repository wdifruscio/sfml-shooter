#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <string>

namespace Entities{
    class Player : public Entity
    {
        public:
        Player(sf::Texture &texture, int start_x, int start_y, int init_speed);
        ~Player();
        void handleSprite();
        int speed;
        int x;
        int y;
        int w;
        int h;
        virtual void update();
    };
}
#endif
