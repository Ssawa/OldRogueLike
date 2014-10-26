#include "TypesOfCharacters.h"

extern std::vector< std::vector<Tile> > dungeonMap;
extern std::vector<Enemy> NPCs;
extern Player player;
extern TCODRandom* randomNumGen;
extern std::vector<Item> items;
extern std::vector<Message> messageLog;

Player::Player(int x, int y, char character, TCODColor color, std::string name,float hp, float pow, float def, bool blocks):
Character(x, y, character, color, name,hp, pow, def, blocks)
{
}

bool Player::IsBlocked(int x, int y)
{
    if(dungeonMap[x][y].tileBlocked == true)
    {
        return true;
    }
    for(int i = 0; i < NPCs.size(); i++)
    {
        if(NPCs[i]._objectX == x && NPCs[i]._objectY == y && NPCs[i]._blocks == true)
        {
            Attack(NPCs[i]);
            return true;
        }
    }
    return false;
}

void Player::PickUp()
{
    for(int i = 0; i < items.size(); i++)
    {
        if(items[i]._objectX == _objectX && items[i]._objectY == _objectY)
        {
            std::stringstream text;
            text << "Do you want to pick up " << items[i]._name << " ?(y/n)\n";
            Message message(text.str(), player._objectColor);
            messageLog.push_back(message);
            Game::RenderAll();

            TCOD_key_t yesOrNo = TCODConsole::waitForKeypress(true);
            if(yesOrNo.c == 'y')
            {
                inventory.push_back(items[i]); //Add item to inventory
                items.erase(items.begin() + (i)); //Delete item from items
            }
        }
    }
}


Enemy::Enemy(int x, int y, char character, TCODColor color, std::string name, float hp, float pow, float def, bool blocks):
Character(x, y, character, color, name,hp, pow, def, blocks)
{
}

void Enemy::ChooseMove()
{
    if(_alive)
    {
        if(abs(sqrt((pow(player._objectX-_objectX, 2)+(pow(player._objectY-_objectY,2))))) < 10)
        {
            ChasePlayer();
        }
        else
        {
            Move(randomNumGen->getInt(-1,1), randomNumGen->getInt(-1,1));
        }
    }
}

void Enemy::ChasePlayer()
{
    int moveX, moveY;

    if(player._objectX - _objectX > 0)
    {
        moveX = 1;
    }
    else if(player._objectX - _objectX < 0)
    {
        moveX = -1;
    }
    else
    {
        moveX = 0;
    }

    if(player._objectY - _objectY > 0)
    {
        moveY = 1;
    }
    else if(player._objectY - _objectY < 0)
    {
        moveY = -1;
    }
    else
    {
        moveY = 0;
    }

    Move(moveX, moveY);
}

bool Enemy::IsBlocked(int x, int y)
{
    if(dungeonMap[x][y].tileBlocked == true)
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
    if(player._objectX == x && player._objectY == y && _blocks == true)
    {
        Attack(player);
        return true;
    }
    return false;
}
