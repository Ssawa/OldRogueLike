#include "Item.h"

Item::Item(int x, int y, char character, TCODColor color, std::string name, float affectHP, float affectPower, float affectDef, bool blocks):
GameObject(x, y, character, color, name, blocks), _affectHP(affectHP), _affectPower(affectPower), _affectDef(affectDef)
{
    //ctor
}
