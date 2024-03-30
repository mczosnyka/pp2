#include "rectangle.h"

namespace Shapes {
    Rectangle::Rectangle(int xFrom, int yFrom, int xTo, int yTo) : pointfrom(xFrom, yFrom), pointto(xTo, yTo){}
    bool Rectangle::isIn(int x, int y) const{
            return x>=pointfrom.x_ && x<=pointto.x_ && y>=pointfrom.y_ && y<=pointto.y_;
    };

    int Rectangle::x() const{
        return pointfrom.x_;
    }
    int Rectangle::y() const{
        return pointfrom.y_;
    }
    int Rectangle::xTo() const{
        return pointto.x_;
    }
    int Rectangle::yTo() const{
        return pointto.y_;
    }
} // Shapes