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
    void draw(RenderWindow &window);
    void move(float cordX, float cordY);
    FloatRect getBounds() const;
};