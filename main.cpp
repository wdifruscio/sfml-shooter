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
    FloatRect sAsteroidBounds = sAsteroid.getLocalBounds();

    int player_bullet_speed = 10;
    float player_bullet_timer = 0.0f, delay = 0.2f, time = 0.0f, asteroid_timer = 0.0f, asteroid_delay = 1.0f;
    Clock clock;
    std::vector<Bullet> bullets;
    std::vector<Asteroid> asteroids;

    while (window.isOpen()) {
        time = clock.getElapsedTime().asSeconds();
        clock.restart();
        player_bullet_timer += time;
        asteroid_timer += time;

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

        std::srand((int)std::time(0) * 10);
        if(std::rand() % 10 + 1 > 3 && asteroid_delay < asteroid_timer) {
            std::srand((int)std::time(0) * 600);
            int x = std::rand() % 600, y = 0;
            Asteroid asteroid;
            asteroid.x = x; asteroid.y = y; asteroid.dy = 1;
            asteroids.push_back(asteroid);
            asteroid_timer = 0;
        }
        
        window.clear();
        player.sprite.setPosition(player.x, player.y);
        window.draw(sBackground);
        window.draw(player.sprite);

        for(unsigned i = 0;  i < bullets.size(); i++) {
            for(unsigned j = 0; j < asteroids.size(); j++ ) {
                if(bullets[i].x > asteroids[j].x && bullets[i].x < asteroids[j].x + sAsteroidBounds.width 
                    && bullets[i].y > asteroids[j].y && bullets[i].y < asteroids[j].y + sAsteroidBounds.height) {
                    std::cout << "HIT!" << " ASTEROIDS: "<< asteroids.size() << std::endl;
                    asteroids.erase(asteroids.begin() + j);
                    bullets.erase(bullets.begin() + i);
                }
            }
        }
            
        for(unsigned i = 0;  i < bullets.size(); i++) {
            sBullet.setPosition(bullets[i].x, bullets[i].y - bullets[i].dy);
            // std::cout << "BULLET POS Y: " << bullets[i].y << std::endl;
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
            // std::cout << "BULLET POS Y: " << asteroids[i].y << std::endl;
            if(asteroids[i].y > 800) {
                asteroids.erase(asteroids.begin()+i);
                break;
            } 
            else { 
                asteroids[i].y += asteroids[i].dy; 
            }
                if(asteroids[i].x > player.x && asteroids[i].x < player.x + player.w
                    && asteroids[i].y > player.y && asteroids[i].y < player.y + player.h) {
                    std::cout << "PLAYER HIT!" << std::endl;
                }
            window.draw(sAsteroid);
        }

        window.display();
    }
    return 0;
}
