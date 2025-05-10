#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;
    static std::vector<std::string> carModels;

public:
    Obstacle(float moveSpeed);
    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isOffScreen() const;
    bool checkCollision(const sf::FloatRect& playerBounds) const;
};

#endif