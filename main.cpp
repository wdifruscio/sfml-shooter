#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "Player.hpp"

using namespace sf;

struct Bullet {
    int x, y, dy;
};

struct Asteroid {
    int x,y,dy;
};

int main() {
    VideoMode vm(600,800);
    RenderWindow window(vm,"Game Boilerplate");
    window.setFramerateLimit(60);

    Texture t1, t2, t3, t4;
    t1.loadFromFile("assets/purple.png");
    t2.loadFromFile("assets/bullet.png");
    t3.loadFromFile("assets/player.png");
    t4.loadFromFile("assets/asteroid_1.png");
    
    t1.setRepeated(true);

    Sprite sBackground(t1), sBullet(t2), sAsteroid(t4);
    sBackground.setTextureRect(IntRect(0, 0, 600,800));
    Player player(t3, 300, 700, 5);
    FloatRect sBulletBounds = sBullet.getLocalBounds();

    int player_bullet_speed = 10;
    float player_bullet_timer = 0.0f, delay = 0.2f, time = 0.0f;
    Clock clock;
    std::vector<Bullet> bullets;
    std::vector<Asteroid> asteroids;



    while (window.isOpen()) {
        time = clock.getElapsedTime().asSeconds();
        clock.restart();
        player_bullet_timer += time;

        Event event;
        while(window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        if(Keyboard::isKeyPressed(Keyboard::Right)) player.x += player.speed;
        if(Keyboard::isKeyPressed(Keyboard::Left))  player.x -= player.speed;
        if(Keyboard::isKeyPressed(Keyboard::Up))    player.y -= player.speed;
        if(Keyboard::isKeyPressed(Keyboard::Down))  player.y += player.speed;
        if(Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
        player.handleSprite();

        if(Keyboard::isKeyPressed(Keyboard::Space) && delay < player_bullet_timer) {
            int x = player.x + player.w / 2.0f - sBulletBounds.width / 2.0f, y = player.y;
            Bullet bullet;
            bullet.x = x; bullet.y = y, bullet.dy = player_bullet_speed;
            std::cout << "PLAYER Y: " << player.y << "\t" << "BULLET Y: " << bullet.y << std::endl;
            bullets.push_back(bullet);
            player_bullet_timer = 0;
            std::cout << "BULLET CREATED Y POSITION: " << bullets[bullets.size() - 1].y << "\tBULLETS SIZE: " << bullets.size() << std::endl;
        }
        if(Keyboard::isKeyPressed(Keyboard::E)) {
            int x = 500, y = 100;
            Asteroid asteroid;
            asteroid.x = y; asteroid.y = y; asteroid.dy = 1;
            asteroids.push_back(asteroid);
        }

        player.sprite.setPosition(player.x, player.y);
        window.clear();
        window.draw(sBackground);
        window.draw(player.sprite);

        for(unsigned i = 0;  i < bullets.size(); i++) {
            for(unsigned j = 0; j < asteroids.size(); j++ ) {
                if(sBullet.getGlobalBounds().intersects(sAsteroid.getGlobalBounds())) {
                    std::cout << "collission bro" << std::endl;
                    asteroids.erase(asteroids.begin()+ j);
                    bullets.erase(bullets.begin() + i);
                    break;
                }
            }
        }
            
        for(unsigned i = 0;  i < bullets.size(); i++) {
            sBullet.setPosition(bullets[i].x, bullets[i].y - bullets[i].dy);
            std::cout << "BULLET POS Y: " << bullets[i].y << std::endl;
            if(bullets[i].y < 0) {
                bullets.erase(bullets.begin()+i);
                break;
            } 
            else { 
                bullets[i].y -= bullets[i].dy; 
            }
            window.draw(sBullet);
        }

        for(unsigned i = 0;  i < asteroids.size(); i++) {
            sAsteroid.setPosition(asteroids[i].x, asteroids[i].y);
            
            std::cout << "BULLET POS Y: " << asteroids[i].y << std::endl;
            if(asteroids[i].y > 800) {
                asteroids.erase(asteroids.begin()+i);
                break;
            } 
            else { 
                asteroids[i].y += asteroids[i].dy; 
            }
            window.draw(sAsteroid);
        }

        window.display();
    }
    return 0;
}
