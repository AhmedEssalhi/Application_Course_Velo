#ifndef CAR_HPP
#define CAR_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Car
{
    private:
    Texture texture;
    Sprite sprite;
    float speed;

    public:
    Car(const string &textureFilePath, float cordX, float cordY, float playerSpeed);
    void update();
    void draw(RenderWindow &window);
    FloatRect getBounds() const;
};

#endif
