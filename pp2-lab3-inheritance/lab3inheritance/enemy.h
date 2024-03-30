#ifndef ENEMY_H
#define ENEMY_H

#include "object.h"

/**
 * Proszę o utworzenie klasy `Enemy`, która będzie dziedziczyć po klasie `Object`
 * - Klasa ta powinna mieć mieć składową odpowiadającą ilości punktów życia, oraz getter: `lifePercent()`
 * - Klasa powinna mieć konstruktor przyjmujący aktualną pozycje oraz maksymalne życie z wartością domyślną.
 * - Klasa powinna mieć metodę `isAlieve()` która zwraca prawdę jeśli wróg ma życie powyżej zera
 * - Klasa powinna mieć metodę `decreaseLife()` przyjmującą jako argument liczbę obrażeń
 * - Po zaimplementowaniu powyższego proszę zakomentować makro `UNIMPLEMENTED_enemy`
 */

// #define UNIMPLEMENTED_enemy

class Enemy: public Object
{
private:
    int lifePercent_;
    int healthPoints_;
public:
    // TODO:
    Enemy(Position position, int maxlife = 100, ObjectType type = ObjectType::OBJECT_ENEMY) : Object(type, position), healthPoints_(maxlife), lifePercent_(maxlife){};



    bool isAlieve();
    int lifePercent() const;
    void decreaseLife(int damage);
};

#endif // ENEMY_H
