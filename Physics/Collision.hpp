#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include <cmath>

namespace Physics{

    class Collision{
    private:
        sf::Vector2f getSupportPoint(sf::ConvexShape *poly, const sf::Vector2f &direction);

        float FindAxisLeastPenetration(int *faceIndex, sf::ConvexShape *a, sf::ConvexShape *b);

        sf::Vector2f getNormal(const sf::Vector2f &a, const sf::Vector2f &b);

        float Dot(const sf::Vector2f &a, const sf::Vector2f &b);

        float Cross(const sf::Vector2f &a, const sf::Vector2f &b);

        sf::Vector2f Cross(const sf::Vector2f &a, float s);

        sf::Vector2f Cross(float s, const sf::Vector2f &a);

    public:
        bool CheckCollision(sf::ConvexShape *a, sf::ConvexShape *b){
            int faceIndexA;
            int faceIndexB;
            float penetrationAB = FindAxisLeastPenetration(&faceIndexA, a, b);
            float penetrationBA = FindAxisLeastPenetration(&faceIndexB, b, a);
            return (penetrationAB < penetrationBA) ? (penetrationAB < 0) : (penetrationBA < 0);
        }

    };

}

#endif
