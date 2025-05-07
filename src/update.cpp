#include "game.hpp"

void update(RectangleShape &rect)
{
    if (Keyboard::isKeyPressed(Keyboard::Left) && rect.getPosition().x > 0)
        rect.move(-4.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::Right) && rect.getPosition().x < 600 - rect.getSize().x * 2)
        rect.move(5.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::Up) && rect.getPosition().y > 0)
        rect.move(0.f, -5.f);
    if (Keyboard::isKeyPressed(Keyboard::Down) && rect.getPosition().y < 400 - rect.getSize().y * 2)
        rect.move(0.f, 5.f);
}