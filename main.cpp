#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;
using namespace sf;

// DEFINES
#define WIDTH 800
#define HEIGHT 600
#define FPS 60.f
#define TIMESTEP 1.f / FPS
#define PRADIUS 20
#define PElas 0.25;
#define MElas 1;

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

CircleShape circ[9999];
CircleShape player;

int amt,mass[2],force[2];
float pelas = PElas;
Vector2f acc[2], vel[2], pos[2];





int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Maze");
    window.setFramerateLimit(FPS);
    window.setActive(false);
    window.setKeyRepeatEnabled(false);

    
    cout << "How many circles u want fam" << endl;
    cin >> amt;
    for(int i = 0; i < amt; i++){
        int radius;
        int xpos;
        int ypos;       
        cout << "Radius of circle number " << i+1 << endl;
        cin >> radius;
        circ[i].setRadius(radius);
        circ[i].setOrigin(radius,radius);
        cout << "Position of circle number " << i+1 << endl;
        cin >> xpos >> ypos;
        circ[i].setPosition(xpos,ypos);
        circ[i].setFillColor(Color::Magenta);
        }
    player.setRadius(PRADIUS);
    player.setOrigin(15,15);
    player.setPosition(100,500);
    player.setFillColor(Color::Blue);
    mass[0] = 1;
    force[0] = 100;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == keyUp){
                    keyUpPressed = true;
                    //vel[0].y -= 200;
                    
                }
                if (event.key.code == keyDown){
                    keyDownPressed = true;
                     //vel[0].y += 200;
                    
                }
                if (event.key.code == keyLeft){
                    keyLeftPressed = true;
                    //vel[0].x -= 200;
                    
                }
                if (event.key.code == keyRight){
                    keyRightPressed = true;
                    //vel[0].x += 200;
                    
                }
                if (event.key.code == keyMenu)
                    keyMenuPressed = true;
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == keyUp){
                    keyUpPressed = false;
                    vel[0].y = 0;
                }
                if (event.key.code == keyDown){
                    keyDownPressed = false;
                    vel[0].y = 0;
                }
                if (event.key.code == keyLeft){
                    keyLeftPressed = false;
                    vel[0].x = 0;
                }
                if (event.key.code == keyRight){
                    keyRightPressed = false;
                    vel[0].x = 0;
                }
                if (event.key.code == keyMenu)
                    keyMenuPressed = false;
            }
        }

        if (keyUpPressed)player.move(0,-200 * TIMESTEP);
        if (keyDownPressed)player.move(0,200 * TIMESTEP);
        if (keyLeftPressed)player.move(-200 * TIMESTEP,0);
        if (keyRightPressed)player.move(200 * TIMESTEP,0);
        


        
    vel[0] = vel[0] + (acc[0] * TIMESTEP);
    pos[0] = player.getPosition();
    pos[0] = pos[0] + (0.5f * acc[0] * TIMESTEP * TIMESTEP) + (vel[0] * TIMESTEP);
    player.setPosition(pos[0]);
    


    pos[0] = player.getPosition();
        //elasticity
        if ( pos[0].y  < -5.f + PRADIUS ){   
            pos[0].y = -4.f + PRADIUS;
            vel[0].y = -pelas * vel[0].y;
            player.setPosition( pos[0] );
            }
        if (pos[0].y > HEIGHT - PRADIUS - 5.f){
            pos[0].y = HEIGHT - PRADIUS - 4.f;
            vel[0].y = -pelas * vel[0].y;
            player.setPosition( pos[0] );
        }
        if ( pos[0].x < -5.f + PRADIUS ){
            pos[0].x = -4.f + PRADIUS;
            vel[0].x = -pelas * vel[0].x;
            player.setPosition( pos[0] );
        }

        if(pos[0].x  > WIDTH - PRADIUS -5.f ){
            pos[0].x = WIDTH - PRADIUS -4.f;
            vel[0].x = -pelas * vel[0].x;
            player.setPosition( pos[0] );
        }
        
        window.clear(Color::Black);
        for(int i= 0;i < amt;i++){
            window.draw(player);
        }
        window.draw(player);
        window.display();
    }
    return 0;
}