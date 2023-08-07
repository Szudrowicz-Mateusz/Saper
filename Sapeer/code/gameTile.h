#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>


class GameTile{
public:

    // Shape off tile
    sf::RectangleShape rec;

    // Varriables
    bool is_flaged;
    bool is_mine;
    bool is_reveal;
    ushort nearbay_bombs;
    sf::Vector2f pos;

    // Construtors & Destructors
    GameTile(float x, float y, sf::Vector2f recSize, sf::Texture &texture_default);
    GameTile()=delete;
    ~GameTile()=default;

    // Functions
    void changeToFlag(sf::Texture &texture_flag, sf::Texture &texture_default);
    void changeToMine(sf::Texture &texture_mine);
    void changeToNumber(sf::Texture &number);
};