#include "FileHandling.h"
#include "TypesOfCharacters.h"

extern Player player;
extern std::vector<Enemy> NPCs;
extern std::vector<Item> items;
extern std::vector<Message> messageLog;

FileHandling::FileHandling()
{
}

void FileHandling::SaveMap(std::vector< std::vector<Tile> > test)
{
    std::ofstream mapFile("SaveData/map.txt");

    for(int y = 0; y < Game::MAP_HEIGHT; y++)
    {
        if(y !=0)
        {
            mapFile << std::endl;
        }
        for(int x = 0; x < Game::MAP_WIDTH; x++)
        {
            if(test[x][y].tileBlocked == false)
            {
                mapFile<<"O";
            }
            else
            {
                mapFile<<"#";
            }
        }
    }
    mapFile.close();

    std::ofstream infoFile("SaveData/playerInfo.data", std::ios::binary);
    infoFile.write((char*)&player, sizeof(player));

    //Save NPCs
    infoFile.write((char*) &NPCs, sizeof(NPCs));
    for(int i = 0; i < NPCs.size(); i++)
    {
        infoFile.write((char*) &NPCs[i], sizeof(NPCs[i]));
    }

    //Save Items
    infoFile.write((char*) &items, sizeof(items));
    for(int i = 0; i < items.size(); i++)
    {
        infoFile.write((char*) &items[i], sizeof(items[i]));
    }

    infoFile.close();
}

void FileHandling::LoadMap(std::vector< std::vector<Tile> > &test)
{
    std::string str;
    std::string store;
    std::ifstream mapFile("SaveData/map.txt");
    int loadingLocation;
    for(int i = 0; i < Game::MAP_HEIGHT; i++)
    {
        mapFile>> str;
        store += str;
        for(int j = 0; j < Game::MAP_WIDTH; j++)
        {
            if(str[j] == 'O')
            {
                test[j][i].tileBlocked = false;
            }
            else
            {
                test[j][i].tileBlocked = true;
            }
        }
    }
    mapFile.close();

    std::ifstream infoFile("SaveData/playerInfo.data", std::ios::binary);
    infoFile.read((char*)&player, sizeof(player));

    //Load NPCs
    infoFile.read((char*) &NPCs, sizeof(NPCs));
    for(int i = 0; i < NPCs.size(); i++)
    {
        infoFile.read((char*) &NPCs[i], sizeof(NPCs[i]));
    }

    //Load Items
    infoFile.read((char*) &items, sizeof(items));
    for(int i = 0; i < items.size(); i++)
    {
        infoFile.read((char*) &items[i], sizeof(items[i]));
    }

    infoFile.close();
}
