#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

namespace Entities{

    enum EntityType{
        Player,
        Foe,
        Projectile,
        Debris
    };

    class Entity : sf::Drawable{
    private:
    protected:
        sf::Vector2f    position;
        sf::Vector2f    velocity;
        float           angle;
        float           acceleration;
        EntityType      type;
        std::string     texture;
        sf::Sprite      sprite;
        sf::Shape       *shape;
    public:

        //// SETTERS ////
        void         setPosition     (const sf::Vector2f &pos) { position.x = pos.x; position.x = pos.x; }
        void         setVelocity     (const sf::Vector2f &vel) { velocity.x = vel.x; velocity.y = vel.y; }
        void         setAngle        (float initAngle)         { this->angle = initAngle; }
        void         setAcceleration (float acc)               { this->acceleration = acc; }
        void         setType         (EntityType type)         { this->type = type; }
        void         setTexture      (std::string texture)     { this->texture = texture; }
        void         setShape        (sf::Shape *shape)        { this->shape = shape; }

        //// GETTERS ////
        sf::Vector2f getPosition()     { return position; }
        sf::Vector2f getVelocity()     { return velocity; }
        float        getAngle()        { return angle; }
        float        getAcceleration() { return acceleration; }
        EntityType   getType()         { return type; }
        std::string  getTexture()      { return texture; }
        sf::Shape*   getShape()        { return shape; }

        //// PURE VIRTUAL ////
        virtual void draw(void) = 0;
    };

}

#endif
