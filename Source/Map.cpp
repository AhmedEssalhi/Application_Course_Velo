#include "Map.h"
#include <iostream>

Map::Map(const std::string& texturePath, float scrollSpeed) {
    if (!roadTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture" << std::endl;
    }

    roadSprite1.setTexture(roadTexture);
    roadSprite2.setTexture(roadTexture);

    roadSprite1.setPosition(0, 0);
    roadSprite2.setPosition(0, -roadSprite1.getGlobalBounds().height);
    
    roadSprite1.setScale(
        1000 / roadSprite1.getGlobalBounds().width,
        700 / roadSprite1.getGlobalBounds().height
    );
    roadSprite2.setTexture(roadTexture);
    roadSprite2.setScale(
        1000 / roadSprite2.getGlobalBounds().width,
        700 / roadSprite2.getGlobalBounds().height
    );
    speed = scrollSpeed;
}

void Map::update() {
    roadSprite1.move(0, speed);
    roadSprite2.move(0, speed);

    if (roadSprite1.getPosition().y >= roadSprite1.getGlobalBounds().height)
        roadSprite1.setPosition(0, roadSprite2.getPosition().y - roadSprite1.getGlobalBounds().height);

    if (roadSprite2.getPosition().y >= roadSprite2.getGlobalBounds().height)
        roadSprite2.setPosition(0, roadSprite1.getPosition().y - roadSprite2.getGlobalBounds().height);
}

void Map::draw(sf::RenderWindow& window) {
    window.draw(roadSprite1);
    window.draw(roadSprite2);
}
