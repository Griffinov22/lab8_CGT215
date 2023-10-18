// lab8_CGT215.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include <vector>

using namespace std;
using namespace sf;
using namespace sfp;

void LoadTex(Texture& tex, string filename) {
    if (!tex.loadFromFile(filename)) {
        cout << "Could not load " << filename << endl;
    }
}

int main()
{
    RenderWindow window(VideoMode(800, 600), "Duck Hunter");
    World world(Vector2f(0, 0));
    int score(0);
    int arrows(5);
    int fontSz(48);
    Font font;
    if (!font.loadFromFile("Montserrat.ttf")) {
        cout << "could not load Montserrat.ttf" << endl;
        exit(0);
    }

    PhysicsSprite crossBow;
    Texture cbowTex;
    LoadTex(cbowTex, "images/crossbow.png");
    crossBow.setTexture(cbowTex);
    Vector2f sz = crossBow.getSize();
    crossBow.setCenter(Vector2f(400,
        600 - (sz.y / 2)));

    PhysicsSprite arrow;
    Texture arrowTex;
    LoadTex(arrowTex, "images/arrow.png");
    arrow.setTexture(arrowTex);
    bool drawingArrow(false);

    PhysicsRectangle top;
    top.setSize(Vector2f(800, 10));
    top.setCenter(Vector2f(400, -5));
    top.setStatic(true);
    top.onCollision = [&arrow, &arrows, &world, &drawingArrow](PhysicsBodyCollisionResult res) {
        arrows--;
        drawingArrow = false;
        world.RemovePhysicsBody(arrow);
    };
    world.AddPhysicsBody(top);

    Text arrowText;
    arrowText.setFont(font);
    arrowText.setCharacterSize(fontSz);

    Clock clock;
    Time lastTime(clock.getElapsedTime());
    while (arrows > 0) {
        Time currentTime(clock.getElapsedTime());
        int deltaTime((currentTime - lastTime).asMilliseconds());

        if (deltaTime > 2) {
            lastTime = currentTime;
            world.UpdatePhysics(deltaTime);

            if (Keyboard::isKeyPressed(Keyboard::Space) && !drawingArrow) {
                drawingArrow = true;
                arrow.setCenter(crossBow.getCenter());
                arrow.setVelocity(Vector2f(0, -1.2));
                world.AddPhysicsBody(arrow);
            }

            window.clear();
            window.draw(crossBow);
            if (drawingArrow) {
                window.draw(arrow);
            }
            //arrows text
            arrowText.setString(to_string(arrows));
            FloatRect arrowSz(arrowText.getGlobalBounds());
            arrowText.setPosition(Vector2f(20 - (arrowSz.width / 2), 560 - (arrowSz.height / 2)));
            window.draw(arrowText);

            window.display();
            
        }


    }


}
