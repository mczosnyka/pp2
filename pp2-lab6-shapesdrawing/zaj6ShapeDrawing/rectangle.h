#include "shape.h"
#ifndef ZAD4SHAPEDRAWING_DLASTUDENTOW_RECTANGLE_H
#define ZAD4SHAPEDRAWING_DLASTUDENTOW_RECTANGLE_H
using namespace std;
namespace Shapes {

    class Rectangle : public Shapes::Shape {
    private:
        Shapes::Point pointfrom;
        Shapes::Point pointto;
    public:
        Rectangle(int xFrom, int yFrom, int xTo, int yTo);
        bool isIn(int x, int y) const override;
        int x() const;
        int y() const;
        int xTo() const;
        int yTo() const;
    };

}
#endif //ZAD4SHAPEDRAWING_DLASTUDENTOW_RECTANGLE_H