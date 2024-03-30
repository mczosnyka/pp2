#include "enemy.h"

int Enemy::lifePercent() const{
    return (healthPoints_ / lifePercent_ * 100);
}

bool Enemy::isAlieve(){
    if(healthPoints_ > 0){
        return true;
    }
    else{
        return false;
    }
}

void Enemy::decreaseLife(int damage){
    healthPoints_ -= damage;
};
