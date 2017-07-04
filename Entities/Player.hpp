#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <string>
#include "Entity.hpp"

namespace Entities{
    class Player : public Entity
    {
        public:
        Player();
        ~Player();
        void handleSprite(sf::Keyboard::Key);
        virtual void update();
    };
}
#endif
