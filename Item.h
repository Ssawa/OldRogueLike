#ifndef ITEM_H
#define ITEM_H

#include "GameObject.h"


class Item : public GameObject
{
    public:
        Item(int x, int y, char character, TCODColor color, std::string name, float affectHP, float affectPower, float affectDef, bool blocks = false);

        float _affectHP;
        float _affectPower;
        float _affectDef;
};

#endif // ITEM_H
