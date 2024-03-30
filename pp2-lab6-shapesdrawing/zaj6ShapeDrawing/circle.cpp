#include "circle.h"
#include <cmath>

namespace Shapes {
    Circle::Circle(int xCenter, int yCenter, int radius) : center_(xCenter, yCenter), radius_(radius){}
    bool Circle::isIn(int x, int y) const{
        float buffer = sqrt((pow((x-center_.x_), 2))+(pow((y-center_.y_),2)));
        if(buffer <= radius_){
            return true;
        }
        else{
            return false;
        }

    };

    int Circle::x() const{
        return center_.x_;
    }
    int Circle::y() const{
        return center_.y_;
    }
    int Circle::getRadius()const{
        return radius_;
    }
} // Shapess