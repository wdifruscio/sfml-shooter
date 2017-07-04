#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "../Animation.hpp"

namespace Entities{

    enum EntityType{
        Player,
        Foe,
        Projectile,
        Debris,
        Generic
    };

    typedef struct Boundaries{
        float minX, maxX, minY, maxY;
        constexpr Boundaries(float x1, float  x2, float y1, float y2)
        : minX(x1), maxX(x2), minY(y1), maxY(y2) {}
    } Bounds;

    class Entity {
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
        Animation       *animation;

        Bounds          bounds;

    public:
        bool         isAlive = true;
        //// SETTERS ////
        void         setPosition     (const sf::Vector2f &pos) { position.x = pos.x; position.y = pos.y; }
        void         setVelocity     (const sf::Vector2f &vel) { velocity.x = vel.x; velocity.y = vel.y; }
        void         setAngle        (float initAngle)         { this->angle = initAngle; }
        void         setAcceleration (float acc)               { this->acceleration = acc; }
        void         setType         (EntityType type)         { this->type = type; }
        void         setTexture      (sf::Texture &texture)    { this->texture = texture; }
        void         setShape        (sf::Shape *shape)        { this->shape = shape; }
        void         bindTexture()                             { sprite.setTexture(this->texture); }
        void         setAnimation    (Animation *animation)    { this->animation = animation; }

        void         setEntityBounds (const sf::Vector2f &min, const sf::Vector2f &max) {
            bounds.minX = min.x; bounds.minY = min.y; bounds.maxX = max.x; bounds.maxY = max.y;
        }

        //// GETTERS ////
        sf::Vector2f getPosition()     { return position; }
        sf::Vector2f getVelocity()     { return velocity; }
        float        getAngle()        { return angle; }
        float        getAcceleration() { return acceleration; }
        EntityType   getType()         { return type; }
        sf::Texture  getTexture()      { return texture; }
        sf::Shape*   getShape()        { return shape; }
        sf::Sprite   getSprite()        { return sprite; }
        Animation*   getAnimation()    { return animation; }
        Bounds       getBounds()       { return bounds; }

        // //// PURE VIRTUAL ////
        virtual void update(void) = 0;
        void draw(sf::RenderWindow &window) { window.draw(sprite); }
    };
}


#endif
