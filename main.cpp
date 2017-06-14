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
            asteroid.x = y; asteroid.y = y; asteroid.dy = player_bullet_speed;
            asteroids.push_back(asteroid);
            std::cout << "WAT" << std::endl;
        }

        player.sprite.setPosition(player.x, player.y);
        window.clear();
        window.draw(sBackground);
        window.draw(player.sprite);
        
            std::vector<Bullet>::iterator i = bullets.begin();
            std::vector<Asteroid>::iterator j = asteroids.begin();
            while(i != bullets.end()) {
                sBullet.setPosition(i->x, i->y - i->dy);
                i->y -= i->dy;
                std::cout << "BULLET POS Y: " << i->y << std::endl;
                if(i->y > 0 ) {
                    window.draw(sBullet);
                    i++;
                }
                else {
                    bullets.erase(i);
                }
            }
            while(j!= asteroids.end()) {
                sAsteroid.setPosition(j->x, j->y);
                j->y++;
                 std::cout << "ASTEROID POS Y: " << j->y << std::endl;
                if(j->y < 800 ) {
                    window.draw(sAsteroid);
                    j++;
                }
                else {
                    asteroids.erase(j);
                }  
            }

            // if( i->y == j->y  && i->x == j->x) {
            //     std::cout << "Collision!! " << std::endl;
            // }

        window.display();
    }
    return 0;
}
