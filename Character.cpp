#include "Character.h"
#include "TypesOfCharacters.h"

extern std::vector< std::vector<Tile> > dungeonMap;
extern TCODRandom* randomNumGen;
extern GameObject player;
extern std::vector<Character> NPCs;
extern std::vector<Message> messageLog;

Character::Character(int x, int y, char character, TCODColor color, std::string name,float hp, float pow, float def, bool blocks):
GameObject(x, y, character, color, name,blocks),_hp(hp), _maxHP(hp), _power(pow), _def(def), _alive(true)
{
}

void Character::Draw()
{
    IsAlive();
    if(_alive)
    {
        Game::gameConsole->setForegroundColor(_objectColor);
        Game::gameConsole->putChar(_objectX, _objectY, _objectChar, TCOD_BKGND_NONE);
    }
    else
    {
        Game::gameConsole->setForegroundColor(_objectColor);
        Game::gameConsole->putChar(_objectX, _objectY, 'X', TCOD_BKGND_NONE);
    }
}


void Character::Move(int x, int y)
{
    if(_alive)
    {
        if(IsBlocked(_objectX + x, _objectY + y) == false)
        {
            _objectX += x;
            _objectY += y;
        }
    }
}

bool Character::IsBlocked(int x, int y)
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
        return true;
    }
    return false;
}

void Character::IsAlive()
{
    if(_hp <= 0)
    {
        _alive = false;
    }
}

void Character::Attack(Enemy &defender)
{
    if(_alive&& defender._alive)
    {
        if(defender._def == 0)
        {
            defender._def += .8;
        }
        defender._hp -= (_power/defender._def);
        std::stringstream text;
        text << "You Attack the " << defender._name << " for " << (_power/defender._def) << " damage.\n";
        Message message(text.str(), player._objectColor);
        messageLog.push_back(message);

        defender.IsAlive();
        if(!defender._alive)
        {
            std::stringstream text;
            text << "You kill the " << defender._name << std::endl;
            Message message(text.str(), player._objectColor);
            messageLog.push_back(message);
        }
    }
}

void Character::Attack(Player &defender)
{
    if(_alive&& defender._alive)
    {
        if(defender._def == 0)
        {
            defender._def += .8;
        }
        defender._hp -= (_power/defender._def);
        std::stringstream text;
        text << _name << " attacks you for " << (_power/defender._def) << " damage.\n";
        Message message(text.str(), player._objectColor);
        messageLog.push_back(message);

        defender.IsAlive();
        if(!defender._alive)
        {
            std::stringstream text;
            text << "You are killed by the " << _name << std::endl;
            Message message(text.str(), player._objectColor);
            messageLog.push_back(message);
        }
    }
}
