#include "Animation.hpp"

Animation::Animation(sf::Texture &t, int x, int y, int w, int h, int count, float Speed, float duration) 
{
    Frame = 0;
    speed = Speed;
    duration = duration;

    for(int i = 0; i < count; i++) {
        frames.push_back( sf::IntRect(x + i*w, y, w, h) );
        sprite.setTexture(t);
        sprite.setOrigin(w/2, h/2);
        sprite.setTextureRect(frames[0]);
    }
};


void Animation::update()
{
    int n = frames.size();    
    for(float i = 0; i < duration; i+= speed / n) {
        Frame += speed;
        if (n>0) sprite.setTextureRect (frames[int(Frame)]);                    
    }
};

void Animation::draw(sf::RenderWindow &app)
{
    app.draw(sprite);
}

bool Animation::isEnd() {
    return Frame > frames.size();
}