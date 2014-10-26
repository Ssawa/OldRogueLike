#ifndef FILEHANDLING_H
#define FILEHANDLING_H
#include "precompiledheaders.h"
#include "Map.h"
#include "Game.h"

class FileHandling
{
    public:
        FileHandling();
        static void SaveMap(std::vector< std::vector<Tile> > test);
        static void LoadMap(std::vector< std::vector<Tile> > &test);
};

#endif // FILEHANDLING_H
