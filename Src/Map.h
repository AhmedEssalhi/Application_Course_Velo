#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

class Map {
private:
    sf::Texture roadTexture;
    sf::Sprite roadSprite1, roadSprite2;
    float speed;

public:
    Map(const std::string& texturePath, float scrollSpeed);
    void update();
    void draw(sf::RenderWindow& window);
};

#endif
