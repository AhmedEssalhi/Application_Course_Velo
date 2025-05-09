#include "game.hpp"

Game::Game() : 
    window(VideoMode(1000, 700), "Pixel Car Game"), 
    car("../assets/cars/car3.png", 
        window.getSize().x / 2,
        window.getSize().y - 100, 
        5.f
    ),
    road("../assets/roads/road4.png", 5.0f)
    {
        if (introTexture.loadFromFile("../assets/Backgrounds/1.png"))
            stateChanger(static_cast<GameStates>(-1));
        introSprite.setTexture(introTexture);
        introSprite.setOrigin(
            introSprite.getGlobalBounds().width / 2, 
            introSprite.getGlobalBounds().height / 2
        );
        introSprite.setPosition(window.getSize().x /2,  window.getSize().y /2 - 60);

        if (mainMenuTexture.loadFromFile("../assets/Backgrounds/2.png"))
        stateChanger(static_cast<GameStates>(-1));
        mainMenuSprite.setTexture(mainMenuTexture);
        introSprite.setOrigin(
            introSprite.getGlobalBounds().width / 2, 
            introSprite.getGlobalBounds().height / 2
        );
        introSprite.setPosition(window.getSize().x /2,  window.getSize().y /2 - 60);

        /*if (roadTexture.loadFromFile("../assets/roads/road4.png"))
            stateChanger(static_cast<GameStates>(-1));*/


        stateChanger(GameStates::Intro);
    }



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
        else if (Keyboard::isKeyPressed(Keyboard::Enter))
            stateChanger(GameStates::MainMenu);
        else if (Keyboard::isKeyPressed(Keyboard::S))
            stateChanger(GameStates::Play);
        else if (Keyboard::isKeyPressed(Keyboard::Q))
            stateChanger(GameStates::Exit);
    }
}

void Game::update()
{
    /*
    1. collision detection with obstacle
    */


    // Update obstacles
    for (auto& obstacle : obstacles) {
        obstacle.update();

        if (obstacle.checkCollision(car.getBounds())) {
            stateChanger(GameStates::Exit);
        }
    }

    // Remove obstacles that move off-screen

    /*2. car mouvment bounderies*/
    /*3. obstacle movmenet for road simulation
    ...
    */
    /*roadSprite.move(0, 1.f);
    roadSprite2.move(0, 1.f);*/

    if (state == GameStates::Play)
    {
        road.update();
        car.update(); // Handle car movement
        if (obstacleClock.getElapsedTime().asSeconds() > obstacleSpawnTime) {
            obstacles.push_back(Obstacle("../assets/obstacles/obs2.png", rand() % 700, -50, 5.0f)); // Random X, off-screen start
            obstacleClock.restart();
        }
        for (auto& obstacle : obstacles) {
            obstacle.update(); // Move obstacles with the road
            if (obstacle.checkCollision(car.getBounds())) {
                stateChanger(GameStates::Exit);
            }
        }
        obstacles.erase(remove_if(obstacles.begin(), obstacles.end(),
        [](const Obstacle& obs) { return obs.isOffScreen(); }), obstacles.end());
    }
}

void Game::render()
{
    window.clear();
    switch (state)
    {
    case GameStates::Intro:
        window.draw(introSprite);
        break;
    case GameStates::MainMenu:
        window.draw(mainMenuSprite);
        break;
    case GameStates::Play:
        car.draw(window);
        for (auto &obstacle : obstacles)
            obstacle.draw(window);
        break;
    case GameStates::Exit:
        window.close();
        break;
    default:
        break;
    }

    window.display();
}

void Game::stateChanger(GameStates newState)
{
    state = newState;
}