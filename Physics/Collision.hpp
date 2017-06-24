#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include <cmath>

namespace Physics{

    class Collision{
    private:
        sf::Vector2f getSupportPoint(sf::ConvexShape *poly, const sf::Vector2f &direction){
            float bestProjection = std::numeric_limits<float>::min();
            sf::Vector2f bestVertex;

            for(unsigned int i = 0; i < poly->getPointCount(); ++i){
                sf::Vector2f vertex(poly->getPoint(i));
                float projection = Dot(vertex, direction);

                if(projection > bestProjection){
                    bestProjection = projection;
                    bestVertex = vertex;
                }
            }
            return bestVertex;
        }

        float FindAxisLeastPenetration(int *faceIndex, sf::ConvexShape *a, sf::ConvexShape *b){
            const int NUM_VERTICES = a->getPointCount();
            float bestDistance = std::numeric_limits<float>::min();
            float dotProduct;
            int bestIndex;
            sf::Vector2f aNormal, bSupport, aFace;

            for(int i = 0; i < NUM_VERTICES; ++i){
                int j = i+1 < NUM_VERTICES ? i+1 : 0;

                aNormal  = getNormal(a->getPoint(j), a->getPoint(i));
                bSupport = getSupportPoint(b, -aNormal);
                aFace    = a->getPoint(i);
                dotProduct = Dot(aNormal, bSupport - aFace);

                if(dotProduct >bestDistance){
                    bestDistance = dotProduct;
                    bestIndex = i;
                }
            }

            *faceIndex = bestIndex;
            return bestDistance;
        }

        sf::Vector2f getNormal(const sf::Vector2f &a, const sf::Vector2f &b){
            sf::Vector2f face = b - a;
            sf::Vector2f normal(face.y, -face.x);
            float length = sqrt((normal.x*normal.x) + (normal.y*normal.y));
            return normal/length;
        }

        float Dot(const sf::Vector2f &a, const sf::Vector2f &b){
            return (a.x*b.x) + (a.y*b.y);
        }

        float Cross(const sf::Vector2f &a, const sf::Vector2f &b){
            return (a.x*b.y) - (a.y*b.x);
        }
        sf::Vector2f Cross(const sf::Vector2f &a, float s){
            return sf::Vector2f(s*a.y, -s*a.x);
        }
        sf::Vector2f Cross(float s, const sf::Vector2f &a){
            return sf::Vector2f(s*a.y, -s*a.x);
        }
    public:
        static bool CheckCollision(sf::ConvexShape *a, sf::ConvexShape *b){
            return false;
        }

    };

}

#endif
