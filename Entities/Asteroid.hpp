#ifndef ASTEROID_H
#define ASTEROID_H

<<<<<<< 93c652d20e91a584c3a5f0fe017cb128360d40a4

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
=======
#include "Entity.hpp"
#include "../Animation.hpp"

namespace Entities{

    class Asteroid : public Entity{

    };

}

>>>>>>> Added collisions and new Quad Tree
#endif
