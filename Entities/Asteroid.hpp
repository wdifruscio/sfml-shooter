#ifndef ASTEROID_H
#define ASTEROID_H


#include <SFML/Graphics.hpp>
#include "Entity.hpp"

#include <string>

namespace Entities{
    class Asteroid : public Entity
    {
        public:
        Asteroid();
        ~Asteroid();
        void handleSprite();
        virtual void update();
    };
}
#endif
