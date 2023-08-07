#include "gameTile.h"

GameTile::GameTile(float x, float y,sf::Vector2f recSize,sf::Texture &texture_default)
{
    // Tunning variables
    pos = sf::Vector2f(x,y);
    is_flaged=false;
    is_mine=false;
    is_reveal=false;
    nearbay_bombs=0;

    // Setting up rectangles
    rec.setPosition(pos);
    rec.setSize(recSize);
    rec.setOutlineThickness(1.f);
    rec.setOutlineColor(sf::Color::Black);
}

void GameTile::changeToFlag(sf::Texture &texture_flag, sf::Texture &texture_default)
{
if(!is_reveal)
{


    if(!is_flaged)
        rec.setTexture(&texture_flag);
    else
        rec.setTexture(&texture_default);

    is_flaged = !is_flaged;
}
}

void GameTile::changeToMine(sf::Texture &texture_mine)
{
    rec.setTexture(&texture_mine);
    is_reveal=true;
}

void GameTile::changeToNumber(sf::Texture &number)
{
    rec.setTexture(&number);
    is_reveal=true;
}