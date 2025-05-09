#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

class Obstacle
{
    private:
    Texture texture;
    Sprite sprite;
    float speed;

    public:
    Obstacle(const std::string& texturePath, float, float, float speed);
    void update();
    void draw(RenderWindow& window);
    FloatRect getBounds() const;
    bool isOffScreen() const;
    bool checkCollision(const FloatRect& playerBounds) const;
    
};

#endif