#include "car.hpp"

Car::Car(const string &textureFilePath, float cordX, float cordY, float playerSpeed)
{
    texture.loadFromFile(textureFilePath);
    sprite.setTexture(texture);
    sprite.setPosition(cordX, cordY);
    sprite.setOrigin(
        sprite.getGlobalBounds().width / 2, 
        sprite.getGlobalBounds().height / 2
    );
    speed = playerSpeed;
}

void Car::draw(RenderWindow &window)
{
    window.draw(sprite);
}

void Car::move(float cordX, float cordY)
{
    sprite.move(cordX * speed, cordY * speed);
}

FloatRect Car::getBounds() const
{
    return sprite.getGlobalBounds();
}