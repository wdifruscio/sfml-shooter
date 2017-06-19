#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "Player.hpp"
#include "ParticleSystem.cpp"

using namespace sf;

struct Bullet {
    int x, y, dx;
};

struct Asteroid {
    int x,y,dx,dy;
};

int main() {
    ParticleSystem particles(10000);
    int gWindow_w = 1440; int gWindow_h = 900;
    VideoMode vm(gWindow_w, gWindow_h);
    RenderWindow window(vm,"Space Shooter");
    window.setFramerateLimit(60);

    Texture t2, t3, t4, bg1, bg2;
    t2.loadFromFile("assets/bullet.png");
    t3.loadFromFile("assets/ship.png");
    t4.loadFromFile("assets/asteroid_1.png");
    bg1.loadFromFile("assets/background-stars.png");
    bg2.loadFromFile("assets/background-nebula.png");
    // bg3.loadFromFile("assets/starlayer3.png");
    
    Sprite sBullet(t2), sAsteroid(t4), sBg1(bg1), sBg2(bg2), sBg2_copy(bg2);
    Player player(t3, 0, gWindow_h / 2, 5);
    FloatRect sBulletBounds = sBullet.getLocalBounds();
    FloatRect sAsteroidBounds = sAsteroid.getLocalBounds();

    int player_bullet_speed = 10;
    float player_bullet_timer = 0.0f, delay = 0.2f, time = 0.0f, asteroid_timer = 0.0f, asteroid_delay = 1.0f;
    float sBg2_dx = 0.1f;
    Clock clock;
    std::srand ((unsigned)std::time(NULL));
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
            int x = player.x + player.w / 2, y = (player.y + (player.h / 2)) + sBulletBounds.height / 2.0;
            Bullet bullet;
            bullet.x = x; bullet.y = y, bullet.dx = player_bullet_speed;
            std::cout << "PLAYER Y: " << player.y << "\t" << "BULLET Y: " << bullet.y << std::endl;
            bullets.push_back(bullet);
            player_bullet_timer = 0;
            std::cout << "BULLET CREATED Y POSITION: " << bullets[bullets.size() - 1].y << "\tBULLETS SIZE: " << bullets.size() << std::endl;
        }
        if(std::rand() % 10 + 1 > 1 && asteroid_delay < asteroid_timer) {
            int x = gWindow_w, y = std::rand() % gWindow_h;
            Asteroid asteroid;
            asteroid.x = x; asteroid.y = y; asteroid.dx = rand() % 10 - 4; asteroid.dy = rand() % 8 - 4; 
            asteroids.push_back(asteroid);
            asteroid_timer = 0;
        }
        sf::Time elapsed = clock.restart();
        particles.update(elapsed);
        window.clear();

        
        if(sBg2.getPosition().x < -sBg2.getLocalBounds().width) sBg2.setPosition(0, 0);
        if(sBg2_copy.getPosition().x < 0) sBg2_copy.setPosition(sBg2.getLocalBounds().width, 0);

        sBg2.move(-sBg2_dx, 0);
        sBg2_copy.move(-sBg2_dx, 0);

        window.draw(sBg1);
        window.draw(sBg2);
        window.draw(sBg2_copy);

        player.sprite.setPosition(player.x, player.y);
        sf::Vector2f thrusterPos((float)player.x + 10, (float)player.y + ((float)player.h / 2));
        particles.setEmitter(thrusterPos);                
        window.draw(particles);        
        window.draw(player.sprite);

        // update it
        
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
            sBullet.setPosition(bullets[i].x, bullets[i].y - bullets[i].dx);
            // std::cout << "BULLET POS Y: " << bullets[i].y << std::endl;
            if(bullets[i].x > gWindow_w) {
                bullets.erase(bullets.begin()+i);
                break;
            } 
            else { 
                bullets[i].x += bullets[i].dx; 
            }
            window.draw(sBullet);
        }

        for(unsigned i = 0;  i < asteroids.size(); i++) {
            sAsteroid.setPosition(asteroids[i].x, asteroids[i].y);
            // std::cout << "BULLET POS Y: " << asteroids[i].y << std::endl;
            if(asteroids[i].y > gWindow_h || asteroids[i].y < 0 || asteroids[i].x < 0) {
                asteroids.erase(asteroids.begin()+i);
                break;
            } 
            else { 
                asteroids[i].y -= 1 * asteroids[i].dy;
                asteroids[i].x += 1 * asteroids[i].dx; 
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
