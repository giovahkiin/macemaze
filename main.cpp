#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <sstream>

using namespace std;
using namespace sf;

// DEFINES
#define WIDTH 1366
#define HEIGHT 768
#define FPS 60.f
#define TIMESTEP 1.f / FPS
#define PRADIUS 30
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
Texture gameTextures[11];
Font deco;
Font fu;
Music music;
int hitcount[9999],balls,amt;
float mass[2],force[2],elas[2],grav;

Vector2f acc[2], vel[9999], pos[9999];
bool inputEnabled = true;

void playMusic(RenderWindow* window) {
    if (!music.openFromFile("music/music.ogg"));
    music.play();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Maze");//, sf::Style::Fullscreen);
    window.setFramerateLimit(FPS);
    window.setActive(false);
    window.setKeyRepeatEnabled(false);

    // loading resources
    cout << "Loading textures..." << endl;
    if (!gameTextures[0].loadFromFile("gfx/bg.png"));
    // 1 -- menubg?
    if (!gameTextures[2].loadFromFile("gfx/finishbg.png"));
    if (!gameTextures[3].loadFromFile("gfx/santa.png"));
    if (!gameTextures[4].loadFromFile("gfx/sack.png"));
    if (!gameTextures[5].loadFromFile("gfx/ball1.png"));
    if (!gameTextures[6].loadFromFile("gfx/ball2.png"));
    if (!gameTextures[7].loadFromFile("gfx/ball3.png"));
    if (!gameTextures[8].loadFromFile("gfx/ball4.png"));
    if (!gameTextures[9].loadFromFile("gfx/ball5.png"));
    if (!gameTextures[10].loadFromFile("gfx/ball6.png"));
    if (!deco.loadFromFile("font/cdeco.otf"));
    if (!fu.loadFromFile("font/fu.otf"));
    // playing music
    Thread t1(&playMusic, &window);
    t1.launch();
    

    for (int i = 0; i < 10; i++) gameTextures[i].setSmooth(true);

    sf::Sprite background(gameTextures[0]);
    sf::Sprite endBackground(gameTextures[2]);
        //input for targets
        cout << "How many targets?" << endl;
        cin >> amt;
        //win condition
        balls = amt;
        int tempRand = 5;
        //inputs
        for(int i = 2; i < amt + 2; i++){
            int radius;
            int xpos;
            int ypos;       
            cout << "Radius of target number " << i-1 << endl;
            cin >> radius;
            circ[i].setRadius(radius);
            circ[i].setOrigin(radius,radius);
            cout << "Position of target number " << i-1 << endl;
            cin >> xpos >> ypos;
            circ[i].setPosition(xpos,ypos);
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
    circ[0].setTexture(&gameTextures[3]);
    mass[0] = PMASS;
    force[0] = 100;
    elas[0] = PElas ;

    //mace values
    circ[1].setRadius(MRADIUS);
    circ[1].setOrigin(MRADIUS,MRADIUS);
    circ[1].setPosition(80,550);
    circ[1].setTexture(&gameTextures[4]);
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
                }
                if (event.key.code == keyDown){
                    keyDownPressed = true;
                }
                if (event.key.code == keyLeft){
                    keyLeftPressed = true;
                    circ[0].setScale(1,1);        
                }
                if (event.key.code == keyRight){
                    keyRightPressed = true;
                    circ[0].setScale(-1,1);
                }
                if (event.key.code == keyMenu)
                    keyMenuPressed = true;
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == keyUp){
                    keyUpPressed = false;
                }
                if (event.key.code == keyDown){
                    keyDownPressed = false;
                }
                if (event.key.code == keyLeft){
                    keyLeftPressed = false;    
                }
                if (event.key.code == keyRight){
                    keyRightPressed = false;
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

        if (inputEnabled) {
            //player movement
        if (keyUpPressed)vel[0].y = -350;
        if (keyDownPressed)vel[0].y = 350;
        if (keyLeftPressed)vel[0].x = -350;
        if (keyRightPressed)vel[0].x = 350;
        
        if(keyRightPressed == false && keyLeftPressed == false) vel[0].x = 0;
        if(keyUpPressed == false && keyDownPressed == false) vel[0].y = 0;

        circ[0].move(vel[0] * TIMESTEP);

        //mace movement
    Vector2f direction = Vector2f( circ[0].getPosition() - circ[1].getPosition()  );
    float magnitude = sqrt((direction.x * direction.x) + (direction.y * direction.y));
    Vector2f unitVector(direction.x / magnitude, direction.y / magnitude);
    grav = 15.f;
    acc[1].x = unitVector.x * grav *force[1] * mass[1];
    acc[1].y = unitVector.y * grav * force[1] * mass[1];
    vel[1] = (vel[1] + (acc[1] * TIMESTEP)) - ( ( FRICTION * vel[1] ) / mass[1] );
    circ[1].move((0.5f * acc[1] * TIMESTEP * TIMESTEP) + (vel[1] * TIMESTEP));
        }

    //balls collision detection
    
    for( int i = 0; i < 2; i++){
        for(int j = 0; j < amt + 2;j++){
            if(i!=j && i ==1 && circ[j].getRadius() > 0 ){
              float dx =  circ[i].getPosition().x - circ[j].getPosition().x;
              float dy =  circ[i].getPosition().y - circ[j].getPosition().y;
              Vector2f normVec(dx,dy);
              Vector2f unitVec(normVec/sqrt((dx * dx) + ( dy *dy )));
              Vector2f unitTan(-unitVec.y,unitVec.x);
              float radii = circ[j].getRadius() + circ[i].getRadius();
              if ( (dx * dx) + (dy * dy) < radii * radii){
               pos[i] = circ[i].getPosition();
               vel[i] = vel[i] - 2 * ((vel[i].x * unitVec.x) + (vel[i].y * unitVec.y)) * unitVec;
               hitcount[j] += 1;
               cout << "Circle " << j << " has been hit " << hitcount[j] << " times." << endl;
              circ[i].setPosition(pos[i]);
			float newRadius = (circ[j].getRadius() - 10);
            float newMaceRad = (circ[i].getRadius() + 3);
			   if (hitcount[j] % 3 == 0 && j != 0){
                    if(circ[j].getRadius() == 10 || circ[j].getRadius() < 10 ){                        
                        balls -= 1;
                        circ[j].setRadius(0);
                    }
                    else{                               
				   circ[j].setRadius(newRadius);
                   }
                   if(circ[i].getRadius() < 75){
                        circ[i].setRadius(newMaceRad);
                        circ[i].setOrigin(circ[i].getRadius(),circ[i].getRadius());
                        grav += 5;
                    }                   
                   circ[j].setOrigin(circ[j].getRadius(),circ[j].getRadius());
                   cout << circ[j].getRadius() << endl;
                
			   }
              }
            }
        }    
    }

    if (balls == 0){
        music.stop();
        cout << "you win!" << endl;
        inputEnabled = false;
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

    if (inputEnabled) {
window.clear(Color::Black);
        window.draw(background);
        for(int i= 0;i < amt + 2;i++){
            window.draw(circ[i]);
        }
    }
    else {
        window.clear(Color::Black);
        window.draw(endBackground);
        Text youWin;
        youWin.setFont(deco);
        youWin.setString("You Win!");
        youWin.setCharacterSize(160);
        youWin.setFillColor(sf::Color::Red);
        youWin.setPosition(310,200);
        window.draw(youWin);
        Text hitsTaken;
        hitsTaken.setFont(fu);
        std::stringstream ss;
        ss <<  "You were hit " << hitcount[0] << " times!";
        string s = ss.str();
        hitsTaken.setString(s);
        hitsTaken.setCharacterSize(84);
        hitsTaken.setFillColor(sf::Color::White);
        hitsTaken.setPosition(420,400);
        window.draw(hitsTaken);
    }
        
        window.display();
        }
    return 0;
}