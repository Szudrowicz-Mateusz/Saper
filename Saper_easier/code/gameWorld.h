#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <cstdlib>
#include <vector>
#include <queue>

#include "gameTile.h"


class GameWorld{
public:

    // Variable
    std::vector< std::vector<GameTile>> tiles;
    int width;
    int length;
    bool first_click=true;
    ushort bombs_number;
    sf::Vector2<short> occupied;

    // Textures
    sf::Texture texture_flag;
    sf::Texture texture_mine;
    sf::Texture texture_default;
    sf::Texture num0;
    sf::Texture num1;
    sf::Texture num2;
    sf::Texture num3;
    sf::Texture num4;
    sf::Texture num5;
    sf::Texture num6;
    sf::Texture num7;
    sf::Texture num8;

    // Constructor & Destructors
    GameWorld(int _width, int _length, ushort bombs);
    GameWorld()=delete;
    ~GameWorld()=default;

    // Functions
    void setUpWorld();
    void draw(sf::RenderWindow &window);
    void flaging(sf::Vector2i mouse_pos);

    void clicking(sf::Vector2i mouse_pos, sf::RenderWindow  &window);
    void startGame();
    void setingUpNumber();
    void findXandY(sf::Vector2i& mouse_pos);
    void play(sf::RenderWindow &window);
    void win();
    void untilHitNumber();
    void chooseTheNumberOfTexture(short y, short x);
};