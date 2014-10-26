#ifndef AIS_H
#define AIS_H

#include "Game.h"
#include "Character.h"

class Character;

class MonsterAI
{
    public:
        MonsterAI(Character owner);
        void Move(int x, int y);
        bool IsBlocked(int x, int y);
        void ChooseMove();
        void ChasePlayer();

        Character* _owner;
};

class PlayerAI
{
    public:
        PlayerAI(Character owner);
        void Move(int x, int y);
        bool IsBlocked(int x, int y);

        Character* _owner;
};

#endif // AIS_H
