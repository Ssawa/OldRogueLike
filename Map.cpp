#include "Map.h"
#include "Game.h"
/*
Map::Map()
{
    CreateDungeon();
}

void Map::CreateDungeon()
{
    for(int x = 0; x < MAP_WIDTH; x++)
    {
        vector<Tile> row;
        for(int y = 0; y < MAP_HEIGHT; y++)
        {
            if(x == 0 || x == MAP_WIDTH-1 || y == 0 || y == MAP_HEIGHT-1)
            {
                row.push_back(Tile(true, true));
            }
            else
            {
                row.push_back(Tile(false, false));
            }
        }
        dungeonMap.push_back(row);
    }
}

void Map::DrawDungeon()
{
    for(int x = 0; x < MAP_WIDTH; x++)
    {
        for(int y = 0; y < MAP_HEIGHT; y++)
        {
            if(dungeonMap[x][y].tileBlocked == false)
            {
                Game::gameConsole->setBack(x, y, TCODColor::desaturatedBlue, TCOD_BKGND_SET);
            }
            else
            {
                Game::gameConsole->setBack(x, y, TCODColor::darkerBlue, TCOD_BKGND_SET);
            }
        }
    }
}
*/
