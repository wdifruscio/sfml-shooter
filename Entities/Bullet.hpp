#ifndef BULLET_H
#define BULLET_H


#include <SFML/Graphics.hpp>
#include "Entity.hpp"

#include <string>

namespace Entities{
    class Bullet : public Entity
    {
        public:
        Bullet();
        ~Bullet();
        void handleSprite();
        virtual void update();
    };
}
#endif
