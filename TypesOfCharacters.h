#ifndef TYPESOFCHARACTERS_H
#define TYPESOFCHARACTERS_H

#include "Character.h"
#include "Item.h"

class Player : public Character
{
    public:
        Player(int x, int y, char character, TCODColor color, std::string name, float hp, float pow, float def, bool blocks = true);
        bool IsBlocked(int x, int y);
        void PickUp();
        std::vector<Item> inventory;
};

class Enemy : public Character
{
    public:
        Enemy(int x, int y, char character, TCODColor color, std::string name, float hp, float pow, float def, bool blocks = true);
        void ChooseMove();
        void ChasePlayer();
        bool IsBlocked(int x, int y);
};

#endif // TYPESOFCHARACTERS_H
