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

FloatRect Car::getBounds() const
{
    return sprite.getGlobalBounds();
}


void Car::update() {
    float currentSpeed = 1.f;

    if (
        Keyboard::isKeyPressed(Keyboard::Right) &&
        (sprite.getPosition().x < 1000 - sprite.getGlobalBounds().width)

    )
    sprite.move(-currentSpeed, 0);
    if (
        Keyboard::isKeyPressed(Keyboard::Left) &&
        (sprite.getPosition().x - sprite.getGlobalBounds().width > 0)
    )
        sprite.move(currentSpeed, 0);
}