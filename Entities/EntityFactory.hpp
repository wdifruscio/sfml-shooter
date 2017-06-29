#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

namespace Entities {

    class EntityFactory {
        private:
        protected:
        public:
        Entity entity;
        Entity GeneratePlayer {
            return entity;
        };
    };

}

#endif