#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace sf;
using namespace std;

void update(RectangleShape &);
void detectCollision(RectangleShape &, RectangleShape &, int &);

#endif