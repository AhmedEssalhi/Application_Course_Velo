#include "Obstacle.h"
#include <iostream>

Obstacle::Obstacle(const std::string& texturePath, float x, float y, float moveSpeed) {
    if (!texture.loadFromFile("assets/obstacle/rock.png")) {
        std::cerr << "Failed to load texture" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    speed = moveSpeed;
}

void Obstacle::update() {
    sprite.move(0, speed);
}

void Obstacle::draw(sf::RenderWindow& window) {
    sprite.setTexture(texture);
    window.draw(sprite);
}

sf::FloatRect Obstacle::getBounds() const {
    return sprite.getGlobalBounds();
}

bool Obstacle::isOffScreen() const {
    return sprite.getPosition().y > 800;
}

bool Obstacle::checkCollision(const sf::FloatRect& playerBounds) const {
    return sprite.getGlobalBounds().intersects(playerBounds);
}
