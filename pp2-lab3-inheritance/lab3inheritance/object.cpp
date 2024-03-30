#include "object.h"

Object::Object(ObjectType type, Position position){
type_ = type;
position_ = position;
};

void Object::setPosition(Position position){
    position_ = position;
};


ObjectType Object::type() const{
    return type_;
}


Position Object::position() const{
    return position_;
}

void Object::moveUp(){
    position_ = position_.moveUp();
}

void Object::moveDown(){
    position_ = position_.moveDown();
}

void Object::moveLeft(){
    position_ = position_.moveLeft();
}

void Object::moveRight(){
    position_ = position_.moveRight();
}