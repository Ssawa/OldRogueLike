#include "AIs.h"


extern TCODRandom* randomNumGen;
extern Map testDungeon;
extern GameObject player;
extern vector<Character> NPCs;



MonsterAI::MonsterAI(Character owner)
{
    _owner = &owner;
}

void MonsterAI::Move(int x, int y)
{
    if(IsBlocked(_owner->_objectX + x, _owner->_objectY + y) == false)
    {
        _owner->_objectX += x;
        _owner->_objectY += y;
    }
}

bool MonsterAI::IsBlocked(int x, int y)
{
    if(testDungeon.dungeonMap[x][y].tileBlocked == true)
    {
        return true;
    }
    for(int i = 0; i < NPCs.size(); i++)
    {
        if(NPCs[i]._objectX == x && NPCs[i]._objectY == y && NPCs[i]._blocks == true)
        {
            return true;
        }
    }
    if(player._objectX == x && player._objectY == y && _owner->_blocks == true)
    {
        return true;
    }
    return false;
}

void MonsterAI::ChooseMove()
{
    if(abs(sqrt((pow(player._objectX-_owner->_objectX, 2)+(pow(player._objectY-_owner->_objectY,2))))) < 10)
    {
        ChasePlayer();
    }
    else
    {
        Move(randomNumGen->getInt(-1,1), randomNumGen->getInt(-1,1));
    }
}

void MonsterAI::ChasePlayer()
{
    int moveX, moveY;

    if(player._objectX - _owner->_objectX > 0)
    {
        moveX = 1;
    }
    else if(player._objectX - _owner->_objectX < 0)
    {
        moveX = -1;
    }
    else
    {
        moveX = 0;
    }

    if(player._objectY - _owner->_objectY > 0)
    {
        moveY = 1;
    }
    else if(player._objectY - _owner->_objectY < 0)
    {
        moveY = -1;
    }
    else
    {
        moveY = 0;
    }

    Move(moveX, moveY);
}

PlayerAI::PlayerAI(Character owner)
{
    _owner = &owner;
}

void PlayerAI::Move(int x, int y)
{
    if(IsBlocked(_owner->_objectX + x, _owner->_objectY + y) == false)
    {
        _owner->_objectX += x;
        _owner->_objectY += y;
    }
}

bool PlayerAI::IsBlocked(int x, int y)
{
    if(testDungeon.dungeonMap[x][y].tileBlocked == true)
    {
        return true;
    }
    for(int i = 0; i < NPCs.size(); i++)
    {
        if(NPCs[i]._objectX == x && NPCs[i]._objectY == y && NPCs[i]._blocks == true)
        {
            return true;
        }
    }
    return false;
}
