#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
#include <random>

#include "car.hpp"
#include "obstacle.hpp"
#include "road.hpp"

using namespace sf;
using namespace std;
// Function to generate random obstacles

enum GameStates
{
    Error = -1,
    Intro,
    MainMenu,
    Play,
    Pause,
    Exit,
};

class Game
{
    private:
    RenderWindow window;
    Texture introTexture;
    Sprite introSprite;
    Texture mainMenuTexture;
    Sprite mainMenuSprite; 
    Texture roadTexture;
    Texture roadTexture2;
    Sprite roadSprite;   
    Sprite roadSprite2;
    Car car;
    Road road;
    GameStates state;
    vector<Obstacle> obstacles;
    Clock obstacleClock;
    float obstacleSpawnTime = 2.0f; 

    public:
    Game();
    void run();

    private:
    void handleEvent();
    void update();
    void render();
    void stateChanger(GameStates);
};

#endif