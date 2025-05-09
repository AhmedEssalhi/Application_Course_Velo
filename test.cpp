#include <c++/13/iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

int main (void)
{
    RenderWindow window(VideoMode(1000, 800), "Test !");
    Texture buttonTexture;
    Sprite buttonSprite;
    if (!buttonTexture.loadFromFile("assets/pause&intro_pic/exit_pic.png"))
        return -1;
    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setOrigin(buttonSprite.getGlobalBounds().width / 2, buttonSprite.getGlobalBounds().height / 2);
    //buttonTexture.loadFromFile("/assets/")

    buttonSprite.setPosition(
        (window.getSize().x / 2),
        (window.getSize().y / 2)
    );

    while(window.isOpen())
    {
        Event event;
        Vector2i mousePos = Mouse::getPosition(window);
    
        while(window.pollEvent(event))
        {
            if (
                (event.type == Event::Closed) ||
                (Keyboard::isKeyPressed(Keyboard::Escape))
            )
                window.close();
        }
        if (buttonSprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
        {
            buttonSprite.setScale({1.2f, 1.2});
            if (Mouse::isButtonPressed(Mouse::Button::Left))
            {
                buttonSprite.setScale({1.1f, 1.1f});
                window.close();
            }
        }
        else
        {
            buttonSprite.setScale({1.f, 1.f});
        }
            
        window.clear();
        window.draw(buttonSprite);
        window.display();
    }

    return 0;
}