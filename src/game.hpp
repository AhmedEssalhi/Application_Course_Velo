#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "car.hpp"

using namespace sf;
using namespace std;

class Game
{
    private:
    RenderWindow window;
    Car car;

    public:
    Game();
    void run();
    private:
    void handleEvent();
    void update();
    void render();

};

#endif