#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

// DEFINES
#define WIDTH 800
#define HEIGHT 600
#define FPS 60.f
#define TIMESTEP 1.f / FPS

// keybindings
#define keyUp sf::Keyboard::W
#define keyDown sf::Keyboard::S
#define keyLeft sf::Keyboard::A
#define keyRight sf::Keyboard::D
#define keyMenu sf::Keyboard::Escape

// input booleans
bool keyUpPressed = false;
bool keyDownPressed = false;
bool keyLeftPressed = false;
bool keyRightPressed = false;
bool keyMenuPressed = false;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Maze");
    window.setFramerateLimit(FPS);
    window.setActive(false);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == keyUp)
                    keyUpPressed = true;
                if (event.key.code == keyDown)
                    keyDownPressed = true;
                if (event.key.code == keyLeft)
                    keyLeftPressed = true;
                if (event.key.code == keyRight)
                    keyRightPressed = true;
                if (event.key.code == keyMenu)
                    keyMenuPressed = true;
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == keyUp)
                    keyUpPressed = false;
                if (event.key.code == keyDown)
                    keyDownPressed = false;
                if (event.key.code == keyLeft)
                    keyLeftPressed = false;
                if (event.key.code == keyRight)
                    keyRightPressed = false;
                if (event.key.code == keyMenu)
                    keyMenuPressed = false;
            }
        }
        window.clear(sf::Color::Black);
        window.display();
    }
    return 0;
}