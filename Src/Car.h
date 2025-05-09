#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>

class Car {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;

public:
    Car(float x, float y, float moveSpeed);
    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
};

#endif
