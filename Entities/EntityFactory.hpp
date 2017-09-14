#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Player.hpp"

namespace Entities {

    class EntityFactory {
        private:
        protected:
        public:
        class Player* GeneratePlayer() { return new class Player(); };
    };

}

#endif
