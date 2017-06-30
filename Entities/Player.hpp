#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <string>

namespace Entities{
    class Player : public Entity
    {
        public:
        Player();
        ~Player();
        void handleSprite(sf::Keyboard::Key);
        bool canMove;
        int speed;
        int w;
        int h;
        virtual void update();
    };
}
#endif
