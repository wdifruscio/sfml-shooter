#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

namespace Entities {

    class EntityFactory {
        private:
        protected:
        public:
        class Player::Player* GeneratePlayer(sf::Texture &texture, int x, int y, int s) { return new class Player::Player(texture,x,y,s); };
    };

}

#endif