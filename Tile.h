#ifndef TILE_H
#define TILE_H


class Tile
{
    public:
        Tile(bool blocked, bool sightBlocked);
        bool tileBlocked;
        bool tileSightBlocked;
};

#endif // TILE_H
