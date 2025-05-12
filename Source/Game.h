#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Car.h"
#include "Obstacle.h"
#include "Map.h"
#include "GameState.h"

class Game {
private:
    sf::RenderWindow window;
    GameState state;    
    Car player;
    Map road;
    std::vector<Obstacle> obstacles;
    sf::Clock obstacleClock;
    float obstacleSpawnTime;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite; 
    sf::Music backgroundMusic;
    sf::Font font;
    sf::Text scoreText;
    float score;   

public:
    Game();
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void resetGame();
    void changeState(GameState newState);
};

#endif
