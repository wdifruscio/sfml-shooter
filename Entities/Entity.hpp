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

    class Entity /*: sf::Drawable */{
    private:
    protected:
        sf::Vector2f    position;
        sf::Vector2f    velocity;
        float           angle;
        float           acceleration;
        EntityType      type;
        sf::Texture     texture;
        sf::Sprite      sprite;
        sf::Shape       *shape;
    public:

        //// SETTERS ////
        // void         setPosition     (const sf::Vector2f &pos) { position.x = pos.x; position.x = pos.x; }
        void         setVelocity     (const sf::Vector2f &vel) { velocity.x = vel.x; velocity.y = vel.y; }
        void         setAngle        (float initAngle)         { this->angle = initAngle; }
        void         setAcceleration (float acc)               { this->acceleration = acc; }
        void         setType         (EntityType type)         { this->type = type; }
        void         setTexture      (sf::Texture &texture)    { this->texture = texture; }
        void         setShape        (sf::Shape *shape)        { this->shape = shape; }
        void         bindTexture()                             { sprite.setTexture(this->texture); }

        //// GETTERS ////
        // sf::Vector2f getPosition()     { return position; }
        sf::Vector2f getVelocity()     { return velocity; }
        float        getAngle()        { return angle; }
        float        getAcceleration() { return acceleration; }
        EntityType   getType()         { return type; }
        sf::Texture  getTexture()      { return texture; }
        sf::Shape*   getShape()        { return shape; }

        // //// PURE VIRTUAL ////
        virtual void update(void) = 0;
        void draw(sf::RenderWindow &window) { window.draw(sprite); }
    };

}

#endif
