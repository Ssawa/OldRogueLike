#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED
#include "Game.h"
#include "Map.h"

class GameObject
{
    public:
        GameObject(int x, int y, char character, TCODColor color, std::string name, bool blocks = false);
        virtual void Draw();
        void Clear();

        int _objectX;
        int _objectY;
        char _objectChar;
        TCODColor _objectColor;
        bool _blocks;
        std::string _name;
};


#endif // GAMEOBJECT_H_INCLUDED
