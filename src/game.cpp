#include "game.hpp"

int main(void)
{
    RenderWindow window(VideoMode(600, 400), "Ball's Up!", Style::Default);
    window.setFramerateLimit(60);

    RectangleShape rect(Vector2f(25.f, 50.f));
    rect.setFillColor(Color::Red);
    rect.setPosition(Vector2f(275.f, 175.f));

    RectangleShape rect2(Vector2f(25.f, 50.f));
    rect2.setFillColor(Color::Black);
    rect2.setPosition(Vector2f(500.f, 150.f));

    int collisionCounter = 0;
    
    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || (
                event.type == event.KeyPressed && event.key.code == Keyboard::Escape
            ))
            window.close();
        }
        
        detectCollision(rect, rect2, collisionCounter);
        window.clear();
        window.clear(Color::White);
        update(rect);
        window.draw(rect);
        window.draw(rect2);
        window.display();
    }

    return 0;
}