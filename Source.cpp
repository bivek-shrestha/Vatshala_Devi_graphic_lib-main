/*
           Project Done by:

           Bivek Shrestha    (076BCT020)
           Bigyapti Bashyal  (076BCT016)
           Ishani Malla      (076BCT028)
*/


#include <SFML/Graphics.hpp>
#include "calc.h"
#include "2D.h"
#include "sketch.h"
#include "Camera.h"
#include "essential.h"
#include "objs.h"
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Nritya Vatshala Devi");
    window.setFramerateLimit(60);

    obj nritya;
    nritya= LoadObject("nrityacolorednewest1.mtl", "nrityacolorednewest1.obj");
    //nritya = LoadObject("nrityacolored9.mtl", "nrityacolored9.obj"); // for color full temple

   

    sf::Clock clock;
    float theta = 0;

    Camera photo;
    photo.update({ 8, 9, 7, 1 }, { 0, 0, 0, 1 });

    Vec4 light = { 4.5, 0.5, 4, 1 };
    Vec4 oldposition{ -1, -1, 1, 1 };
    Vec4 centre{ 0, 0, 0 };

    sf::CircleShape circle;
    circle.setRadius(5);
    circle.setFillColor(sf::Color(255, 255, 187));
    Vec4 lightOrigin = worldtoScreen(photo, light);
    circle.setOrigin(sf::Vector2f(2.5, 2.5));
    circle.setPosition(sf::Vector2f(lightOrigin[0], lightOrigin[1]));

    
    while (window.isOpen())
    {
        sf::Event event;

        sf::Time elapsed = clock.getElapsedTime();
        float t = elapsed.asSeconds();
        clock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    photo.ZoomIn(t);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    photo.ZoomOut(t);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    photo.moveLeft(t);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    photo.moveRight(t);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    photo.rotateLeft(t);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    photo.rotateRight(t);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    photo.moveUp(t);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    photo.moveDown(t);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                    theta += 1;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                    theta -= 1;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
                    light[0] += 0.1;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
                    light[0] -= 0.1;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
                    light[1] += 0.1;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
                    light[1] -= 0.1;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
                    light[2] += 0.1;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                    light[2] -= 0.1;
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    oldposition = { -1, -1, 1, 1 };
                }
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mouseposition = sf::Mouse::getPosition(window);
                Vec4 newposition{ mouseposition.x, mouseposition.y, 1, 1};

                Mat4 T = screentoPort(photo);

                if (oldposition[0] == -1 )oldposition = newposition;
                if (oldposition == newposition)continue;

                Vec4 world_oldposition = T * oldposition;
                Vec4 world_newposition = T * newposition;

                float angle = magnitude(oldposition - newposition) * 0.2;
                Vec4 axis = (world_oldposition - centre) * (world_newposition - centre);

                Mat4 X = getRotationMatrix(centre, centre + axis, angle);
                nritya.transform(X);
                oldposition = newposition;
            }
        }
        window.clear(sf::Color(100, 150, 150));

        // draw everything here...

        Mat4 T = getRotationMatrix(centre, centre+Vec4{0, 1, 0, 0}, 5 * theta);
        nritya.transform(T);
        draw(nritya, window, photo, light);

        Vec4 lightOrigin = worldtoScreen(photo, light);
        circle.setPosition(sf::Vector2f(lightOrigin[0], lightOrigin[1]));
        window.draw(circle);
        
        window.display();
    }

    return 0;
}
