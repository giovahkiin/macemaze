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
#define MRADIUS 15
#define PElas 0
#define MElas 1
#define PMASS 1.f/ 1.f
#define MMASS 1.f/10.f 
#define FRICTION 0.2f * TIMESTEP
#define MAXSPEED 500.f
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
sf::Texture gameTextures[11];
int hitcount[9999];
float amt,mass[9999],force[2],elas[2];

Vector2f acc[2], vel[9999], pos[9999];





int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Maze");
    window.setFramerateLimit(FPS);
    window.setActive(false);
    window.setKeyRepeatEnabled(false);

    // loading textures
    cout << "Loading textures..." << endl;
    if (!gameTextures[0].loadFromFile("gfx/testbgsmall.jpg"));
    // 1 -- menubg?
    // 2 -- gameover
    if (!gameTextures[3].loadFromFile("gfx/santa.png"));
    // 4 -- mace
    if (!gameTextures[5].loadFromFile("gfx/ball1.png"));
    if (!gameTextures[6].loadFromFile("gfx/ball2.png"));
    if (!gameTextures[7].loadFromFile("gfx/ball3.png"));
    if (!gameTextures[8].loadFromFile("gfx/ball4.png"));
    if (!gameTextures[9].loadFromFile("gfx/ball5.png"));
    if (!gameTextures[10].loadFromFile("gfx/ball6.png"));
    for (int i = 0; i < 10; i++) gameTextures[i].setSmooth(true);

    sf::Sprite background(gameTextures[0]);

        //input for targets
        cout << "How many targets?" << endl;
        cin >> amt;
        int tempRand = 5;
        for(int i = 2; i < amt + 2; i++){
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
            // circ[i].setFillColor(Color::Magenta);
            mass[i] = 1/1000.f;
            vel[i] = Vector2f(0.f,0.f);
            // random texture
            circ[i].setTexture(&gameTextures[tempRand]);
            if (tempRand == 10) tempRand = 5;
            else tempRand++;
        }
    //player values
    circ[0].setRadius(PRADIUS);
    circ[0].setOrigin(PRADIUS,PRADIUS);
    circ[0].setPosition(100,500);
    // circ[0].setFillColor(Color::Blue);
    circ[0].setTexture(&gameTextures[3]);
    mass[0] = PMASS;
    force[0] = 100;
    elas[0] = PElas ;

    //mace values
    circ[1].setRadius(MRADIUS);
    circ[1].setOrigin(MRADIUS,MRADIUS);
    circ[1].setPosition(80,550);
    circ[1].setFillColor(Color::Red);
    mass[1] = MMASS;
    force[1] = 800;
    elas[1] = MElas;
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
                    //vel[0].y = 0;
                }
                if (event.key.code == keyDown){
                    keyDownPressed = false;
                    //vel[0].y = 0;
                }
                if (event.key.code == keyLeft){
                    keyLeftPressed = false;
                    //vel[0].x = 0;
                }
                if (event.key.code == keyRight){
                    keyRightPressed = false;
                    //vel[0].x = 0;
                }
                if (event.key.code == keyMenu)
                    keyMenuPressed = false;
            }
        }

        if (keyMenuPressed)
        {
            keyMenuPressed = false;
            window.close();
        }

        if (keyUpPressed)vel[0].y = -350;//circ[0].move(0,-350 * TIMESTEP);
        if (keyDownPressed)vel[0].y = 350;//circ[0].move(0,350 * TIMESTEP);
        if (keyLeftPressed)vel[0].x = -350;//circ[0].move(-350 * TIMESTEP,0);
        if (keyRightPressed)vel[0].x = 350;//circ[0].move(350 * TIMESTEP,0);
        
        if(keyRightPressed == false && keyLeftPressed == false) vel[0].x = 0;
        if(keyUpPressed == false && keyDownPressed == false) vel[0].y = 0;

        circ[0].move(vel[0] * TIMESTEP);

        
    //vel[0] = vel[0] + (acc[0] * TIMESTEP);
    //pos[0] = circ[0].getPosition();
    //pos[0] = pos[0] + (0.5f * acc[0] * TIMESTEP * TIMESTEP) + (vel[0] * TIMESTEP);
    //circ[0].setPosition(pos[0]);
    
    //mace movement
    Vector2f direction = Vector2f( circ[0].getPosition() - circ[1].getPosition()  );
    float magnitude = sqrt((direction.x * direction.x) + (direction.y * direction.y));
    Vector2f unitVector(direction.x / magnitude, direction.y / magnitude);
    acc[1].x = unitVector.x * 15.f *force[1] * mass[1];
    acc[1].y = unitVector.y * 15.f * force[1] * mass[1];
    vel[1] = (vel[1] + (acc[1] * TIMESTEP)) - ( ( FRICTION * vel[1] ) / mass[1] );
    circ[1].move((0.5f * acc[1] * TIMESTEP * TIMESTEP) + (vel[1] * TIMESTEP));

    //balls collision detection
    
    for( int i = 0; i < 2; i++){
        for(int j = 0; j < amt + 2;j++){
            if(i!=j && i ==1 ){
              float dx =  circ[i].getPosition().x - circ[j].getPosition().x;
              float dy =  circ[i].getPosition().y - circ[j].getPosition().y;
              Vector2f normVec(dx,dy);
              Vector2f unitVec(normVec/sqrt((dx * dx) + ( dy *dy )));
              Vector2f unitTan(-unitVec.y,unitVec.x);
              float radii = circ[j].getRadius() + circ[i].getRadius();
              if ( (dx * dx) + (dy * dy) < radii * radii){
               pos[i] = circ[i].getPosition();
               //pos[j] = circ[j].getPosition();
               vel[i] = vel[i] - 2 * ((vel[i].x * unitVec.x) + (vel[i].y * unitVec.y)) * unitVec;
              // vel[j] = vel[j] - 2 * ((vel[j].x * unitVec.x) + (vel[j].y * unitVec.y)) * unitVec;
               hitcount[j] += 1;
               cout << "Circle " << j << " has been hit " << hitcount[j] << " times." << endl;
              circ[i].setPosition(pos[i]);
            //circ[j].setPosition(pos[j]);

              }
            }
        }    
    }
  

    //sides collision
    for( int i = 0; i < 2; i++){
    pos[i] = circ[i].getPosition();
        //elasticity
        if ( pos[i].y  <  circ[i].getRadius() ){   
            pos[i].y = circ[i].getRadius();
            vel[i].y = -elas[i] * vel[i].y;
            circ[i].setPosition( pos[i] );
            }
        if (pos[i].y > HEIGHT - circ[i].getRadius() - 1.f){
            pos[i].y = HEIGHT - circ[i].getRadius() - 1.f;
            vel[i].y = -elas[i] * vel[i].y;
            circ[i].setPosition( pos[i] );
        }
        if ( pos[i].x < circ[i].getRadius() ){
            pos[i].x = circ[i].getRadius();
            vel[i].x = -elas[i] * vel[i].x;
            circ[i].setPosition( pos[i] );
        }

        if(pos[i].x  > WIDTH - circ[i].getRadius() -1.f ){
            pos[i].x = WIDTH - circ[i].getRadius() -1.f;
            vel[i].x = -elas[i] * vel[i].x;
            circ[i].setPosition( pos[i] );
        }
    }
        window.clear(Color::Black);
        window.draw(background);
        for(int i= 0;i < amt + 2;i++){
            window.draw(circ[i]);
        }
        window.display();
    }
    return 0;
}