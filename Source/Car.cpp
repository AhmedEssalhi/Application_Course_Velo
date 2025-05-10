#include "Car.h"
#include <iostream>

Car::Car(float x, float y, float moveSpeed) {
    if (!texture.loadFromFile("assets/cars/car3.png")) {
        std::cerr << "Failed to load texture" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setOrigin(
        sprite.getGlobalBounds().width / 2, 
        sprite.getGlobalBounds().height / 2
    );
    speed = moveSpeed;
}

void Car::update() {
    float currentSpeed = 1.5f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sprite.getPosition().x > sprite.getGlobalBounds().width)
        sprite.move(-currentSpeed, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sprite.getPosition().x < 1000 - sprite.getGlobalBounds().width)
        sprite.move(currentSpeed, 0);
}

void Car::draw(sf::RenderWindow& window) {
    sprite.setTexture(texture);
    window.draw(sprite);
}

sf::FloatRect Car::getBounds() const {
    return sprite.getGlobalBounds();
}
