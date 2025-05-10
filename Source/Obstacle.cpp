#include "Obstacle.h"
#include <iostream>

std::vector<std::string> Obstacle::carModels = {
    "assets/cars/blueObstacleCar.png",
    "assets/cars/yelloObstacleCar.png",
    "assets/cars/greenObstacleCar.png",
    "assets/cars/orangeObstacleCar.png",
    "assets/cars/blackObstacleCar.png",
    "assets/cars/purpleObstacleCar.png",
    "assets/cars/whiteObstacleCar.png"
};

Obstacle::Obstacle(float moveSpeed) {
    std::string selectedCar = carModels[rand() % carModels.size()];

    if (!texture.loadFromFile(selectedCar)) {
        std::cerr << "Failed to load texture" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(rand() % 500 + 100, -50);
    sprite.setScale({.35f, .35f});
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
