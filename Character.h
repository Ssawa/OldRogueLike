#ifndef NPC_H
#define NPC_H

#include "GameObject.h"

class Player;
class Enemy;


class Character : public GameObject
{
    public:
        Character(int x, int y, char character, TCODColor color, std::string name,float hp, float pow, float def, bool blocks = true);
        void Draw();
        void Move(int x, int y);
        virtual bool IsBlocked(int x, int y) = 0;
        void IsAlive();
        void Attack(Enemy &defender);
        void Attack(Player &defender);

        float _hp;
        float _maxHP;
        float _power;
        float _def;
        bool _alive;
};

#endif // NPC_H
