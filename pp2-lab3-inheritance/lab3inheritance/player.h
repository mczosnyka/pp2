#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "direction.h"

/**
 * Proszę o utworzenie klasy `Player`, która będzie dziedziczyć po klasie `Object`, następnie proszę zakomentować `UNIMPLEMENTED_playerIsObject`
 * - Klasa ta powinna mieć mieć składową `direction_`, a także operujący na niej getter i setter. Domyślna wartość to `Direction::RIGHT`
 *    - po zdefiniowaniu proszę usunąć `UNIMPLEMENTED_playerHasDirection`
 * - Klasa powinna mieć składową oznaczającą czy gracz żyje, oraz getter i setter: `isAlieve()`, `setIsAlieve()`
 *    - po zdefiniowaniu proszę usunąć `UNIMPLEMENTED_playerCanDie`
 */

// #define UNIMPLEMENTED_playerIsObject
// #define UNIMPLEMENTED_playerHasDirection
// #define UNIMPLEMENTED_playerCanDie

class Player: public Object
{
// TODO...
private:
    Direction direction_;
    bool isAlieve_ = true;
public:

    Player(ObjectType type = ObjectType::OBJECT_PLAYER, Direction direction = Direction::RIGHT, Position position = Position()) : Object(type, position), direction_(direction){};
    void setDirection(Direction direction){
        direction_ = direction;
    }

    Direction direction() const{
        return direction_;
    }
    void setIsAlieve(bool isalieve){
        isAlieve_ = isalieve;
    }

    bool isAlieve() const{
        return isAlieve_;
    }
};

#endif // PLAYER_H
