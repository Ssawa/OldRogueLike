#include "GameObject.h"
#include "Character.h"

extern std::vector<Character> NPCs;
extern GameObject player;

GameObject::GameObject(int x, int y, char character, TCODColor color, std::string name,bool blocks):
_objectX(x), _objectY(y), _objectChar(character), _objectColor(color), _blocks(blocks), _name(name)
{
}

void GameObject::Draw()
{
    Game::gameConsole->setForegroundColor(_objectColor);
    Game::gameConsole->putChar(_objectX, _objectY, _objectChar, TCOD_BKGND_NONE);
}

void GameObject::Clear()
{
    Game::gameConsole->putChar(_objectX, _objectY,' ', TCOD_BKGND_NONE);
}
