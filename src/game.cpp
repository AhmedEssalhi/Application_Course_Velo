#include "game.hpp"

Game::Game() : 
    window(VideoMode(1000, 700), "Pixel Car Game"), 
    car("../assets/cars/car3.png", 
        window.getSize().x / 2,
        window.getSize().y - 100, 
        5.f
    ) {}

void Game::run()
{
    while(window.isOpen())
    {
        handleEvent();
        update();
        render();
    }
}

void Game::handleEvent()
{
    Event event;
    while (window.pollEvent(event))
    {
        if ((event.type == Event::Closed) ||
            Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();
    }
}

void Game::update()
{

}

void Game::render()
{
    window.clear();
    car.draw(window);
    window.display();
}