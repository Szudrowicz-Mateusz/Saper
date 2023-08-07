#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <chrono>
#include <thread>

#include "gameTile.h"
#include "gameWorld.h"


/*
Minesweeper Project

Most of the game is done in gameWorld.cpp
Mostly used 2D vectors that show every tiles

One tile size is 15.f
This is the reason why I divided mapsize by 15 in constructor of gameWorld
*/

int main(){

    int mapsize=225;

    sf::RenderWindow window(sf::VideoMode(mapsize,mapsize),"SFML Saper", sf::Style::Close | sf::Style::Resize);
    window.setKeyRepeatEnabled(false);


    // Variable of whole TileMap
    GameWorld gameWorld(mapsize/15 , mapsize/15 , 40);

    while(window.isOpen()){

        // Events
        sf::Event event;
        while(window.pollEvent(event)){
            switch ((event.type)){

                case sf::Event::Closed:
                window.close();
                break;
            }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
            gameWorld.flaging(sf::Mouse::getPosition(window));

        else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            gameWorld.clicking(sf::Mouse::getPosition(window),window);
            
        }

        window.clear(sf::Color::Black);
        gameWorld.draw(window);
        window.display();

    }
}