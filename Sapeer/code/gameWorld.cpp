#include "gameWorld.h"

// I assigned every texture to the variable to get easier access later in the file
GameWorld::GameWorld(int _width,int _length,ushort bombs){
    width=_width;
    length=_length;
    bombs_number=bombs;

    setUpWorld();

    texture_flag.loadFromFile("../spirtes/Flag.png");
    texture_mine.loadFromFile("../spirtes/Mine.png");
    texture_default.loadFromFile("../spirtes/Default.png");
    num0.loadFromFile("../spirtes/Num0.png");
    num1.loadFromFile("../spirtes/Num1.png");
    num2.loadFromFile("../spirtes/Num2.png");
    num3.loadFromFile("../spirtes/Num3.png");
    num4.loadFromFile("../spirtes/Num4.png");
    num5.loadFromFile("../spirtes/Num5.png");
    num6.loadFromFile("../spirtes/Num6.png");
    num7.loadFromFile("../spirtes/Num7.png");
    num8.loadFromFile("../spirtes/Num8.png");
}

// Setting up Tile map. If you want bigger tiles you have to do it here
void GameWorld::setUpWorld()
{
    float x=0,y=0;
    for(int i=0;i<=width;i++)
    {
        std::vector<GameTile>rows;
        for(int j=0;j<=length;j++)
        {
            rows.emplace_back(GameTile(x,y,sf::Vector2f(15.f,15.f),texture_default));
            x+=15.f;
        }
        tiles.emplace_back(rows);
        y+=15.f;
        x=0.f;
    }
}

void GameWorld::draw(sf::RenderWindow &window)
{
        for(int i=0;i<width;i++)
        {
            for(int j=0;j<length;j++)
            {
                window.draw(tiles[i][j].rec);
            }
        }
}

// Auxiliary function. Enable to find which tile your mouse is on
void GameWorld::findXandY(sf::Vector2i& mouse_pos)
{
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<length;j++)
        {
            if(tiles[i][j].rec.getGlobalBounds().contains(sf::Vector2f(mouse_pos.x,mouse_pos.y)))
            {
                occupied.y=i;
                occupied.x=j;

                break;
            }
        }

    }
}

void GameWorld::flaging(sf::Vector2i mouse_pos)
{
    findXandY(mouse_pos);

    tiles[occupied.y][occupied.x].changeToFlag(texture_flag,texture_default);
}

// Main function that sends you to diffrent stages depends on your game progress
void GameWorld::clicking(sf::Vector2i mouse_pos,sf::RenderWindow &window)
{
    findXandY(mouse_pos);

    if(first_click)
        startGame();
    
    play(window);
    win();
}

// This enable you not to click on mine on your very first move
void GameWorld::startGame()
{
    first_click=false;

    srand(time(NULL));

    ushort counter=0;
    ushort y,x;

    while(counter < bombs_number)
    {
        y = (std::rand()%length) + 0;
        x = (std::rand()%width) + 0;

        if(y!=occupied.y || x!=occupied.x)
        {
            ++counter;

            tiles[y][x].is_mine=true;
        }
    }

    setingUpNumber();
}

// Every tile have variable that store their number of bombs nearbay. So it's done on the very begging 
void GameWorld::setingUpNumber()
{
    for(int y=0;y<length;y++)
    {
        for(int x=0;x<width;x++)
        {
            // Top
            if(y - 1 >= 0)
            {
                if(tiles[y-1][x].is_mine)
                    ++tiles[y][x].nearbay_bombs;

            // Top RIGHT
            if(x + 1 < width)
                if(tiles[y-1][x+1].is_mine)
                    ++tiles[y][x].nearbay_bombs;

            // Top LEFT
            if(x - 1 >= 0)
                if(tiles[y-1][x-1].is_mine)
                    ++tiles[y][x].nearbay_bombs;
            }   

            // Bottom
            if(y + 1 < length) 
            {
                if(tiles[y+1][x].is_mine)
                    ++tiles[y][x].nearbay_bombs;

            // Bottom RIGHT
            if(x + 1 < width)
                if(tiles[y+1][x+1].is_mine)
                    ++tiles[y][x].nearbay_bombs;

            // Bottom LEFT
            if(x - 1 >= 0)
                if(tiles[y+1][x-1].is_mine)
                    ++tiles[y][x].nearbay_bombs;

            }

        // Right
        if(x + 1 < width)
            if(tiles[y][x+1].is_mine)
                ++tiles[y][x].nearbay_bombs;

        // Left
        if(x - 1 >= 0)
            if(tiles[y][x-1].is_mine)
                ++tiles[y][x].nearbay_bombs;

        }
    }
}

// Revealing tiles you click your left click
void GameWorld::play(sf::RenderWindow &window)
{
    if(tiles[occupied.y][occupied.x].is_reveal == false && tiles[occupied.y][occupied.x].is_flaged == false)
    {
        // Game Over
        if(tiles[occupied.y][occupied.x].is_mine)
        {
            tiles[occupied.y][occupied.x].changeToMine(texture_mine);
            std::cout<<"You lost"<<'\n';
            // Dokończyć
        }
        else if(tiles[occupied.y][occupied.x].nearbay_bombs != 0)
        {// Show the number
            chooseTheNumberOfTexture(occupied.y, occupied.x);
        }
        else
        {
            chooseTheNumberOfTexture(occupied.y, occupied.x);
            untilHitNumber();
        }
    }
}

// Function that passes the position of tile you want to reveal and depends on number of nearbay bombs pass
// The good texure
void GameWorld::chooseTheNumberOfTexture(short y,short x)
{
if(!tiles[y][x].is_mine)
{
    switch(tiles[y][x].nearbay_bombs)
    {
        case 0:
        tiles[y][x].changeToNumber(num0);
        break;

        case 1:
        tiles[y][x].changeToNumber(num1);
        break;

        case 2:
        tiles[y][x].changeToNumber(num2);
        break;

        case 3:
        tiles[y][x].changeToNumber(num3);
        break;

        case 4:
        tiles[y][x].changeToNumber(num4);
        break;

        case 5:
        tiles[y][x].changeToNumber(num5);
        break;

        case 6:
        tiles[y][x].changeToNumber(num6);
        break;
                
        case 7:
        tiles[y][x].changeToNumber(num7);
        break;

        case 8:
        tiles[y][x].changeToNumber(num8);
        break;
    }
}
}

// Check if everything is done
void GameWorld::win()
{
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<length;j++)
        {
            if(tiles[i][j].is_mine)
                if(tiles[i][j].is_flaged == false)
                    return;

            if(!tiles[i][j].is_mine)
                if(tiles[i][j].is_reveal == false)
                    return;
                
        }

    }
    std::cout<<"Win"<<'\n';
}

// If you hit 0 you reveal some part of the map that is connected to this tile
// Have some issues and didn't work perfectly
void GameWorld::untilHitNumber()
{
    std::queue<sf::Vector2<short>> queue_zeros; 
    queue_zeros.push(occupied);

    sf::Vector2<short> h;

    while(queue_zeros.size()!= 0)
    {
        h = queue_zeros.front();

        // Top
        if(h.y-1 >= 0)
        {
            chooseTheNumberOfTexture(h.y-1,h.x);
            // Top
            if(tiles[h.y-1][h.x].nearbay_bombs == 0 && tiles[h.y-1][h.x].is_reveal == false)
                queue_zeros.push(sf::Vector2<short>(h.x,h.y-1));
            
            // Top LEFT
            if(h.x-1 > 0)
            {
                if(tiles[h.y-1][h.x-1].nearbay_bombs == 0 && tiles[h.y-1][h.x-1].is_reveal == false)
                    queue_zeros.push(sf::Vector2<short>(h.x-1,h.y-1));

                chooseTheNumberOfTexture(h.y-1,h.x-1);
            }

            // Top RIGHT
            if(h.x+1 < width)
            {
                if(tiles[h.y-1][h.x+1].nearbay_bombs == 0 && tiles[h.y-1][h.x+1].is_reveal == false)
                    queue_zeros.push(sf::Vector2<short>(h.x-1,h.y+1));

                chooseTheNumberOfTexture(h.y-1,h.x+1);  
            }

        }
        
        // Bottom
        if(h.y+1 < length)
        {
            chooseTheNumberOfTexture(h.y+1,h.x);
            // Bottom
            if(tiles[h.y+1][h.x].nearbay_bombs == 0 && tiles[h.y+1][h.x].is_reveal == false)
                queue_zeros.push(sf::Vector2<short>(h.x,h.y+1));
            
            // Bottom LEFT
            if(h.x-1 > 0)
            {
                if(tiles[h.y+1][h.x-1].nearbay_bombs == 0 && tiles[h.y+1][h.x-1].is_reveal == false)
                    queue_zeros.push(sf::Vector2<short>(h.x+1,h.y-1));

                chooseTheNumberOfTexture(h.y+1,h.x-1);
            }

            // Bottom RIGHT
            if(h.x+1 < width)
            {
                if(tiles[h.y+1][h.x+1].nearbay_bombs == 0 && tiles[h.y+1][h.x+1].is_reveal == false)
                    queue_zeros.push(sf::Vector2<short>(h.x+1,h.y+1));

                chooseTheNumberOfTexture(h.y+1,h.x+1);  
            }
        }

        // Right
        if(h.x+1 < width)
        {
            chooseTheNumberOfTexture(h.y,h.x+1);

            if(tiles[h.y][h.x+1].nearbay_bombs == 0 && tiles[h.y][h.x+1].is_reveal == false)
                queue_zeros.push(sf::Vector2<short>(h.x+1,h.y));
        }

        // Left
        if(h.x-1 > 0)
        {
            chooseTheNumberOfTexture(h.y,h.x-1);

            if(tiles[h.y][h.x-1].nearbay_bombs == 0 && tiles[h.y][h.x-1].is_reveal == false)
                queue_zeros.push(sf::Vector2<short>(h.x-1,h.y));
        }
        queue_zeros.pop();
    }
}