#include "Obstacle.h"

Obstacle::Obstacle(const std::string& texturePath, float x, float y, float moveSpeed) {
    if (!texture.loadFromFile("assets/obstacle/rock.png")) {
        throw std::runtime_error("Failed to load texture");
    }
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    speed = moveSpeed;
}

void Obstacle::update() {
    sprite.move(0, speed);
}

void Obstacle::draw(sf::RenderWindow& window) {
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
