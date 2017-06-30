#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

namespace Entities {

    class EntityFactory {
        private:
        protected:
        public:
        class Player::Player* GeneratePlayer() { return new class Player::Player(); };
    };

}

#endif