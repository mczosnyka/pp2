#include "shape.h"
#ifndef ZAD4SHAPEDRAWING_DLASTUDENTOW_CIRCLE_H
#define ZAD4SHAPEDRAWING_DLASTUDENTOW_CIRCLE_H
using namespace std;
namespace Shapes {

    class Circle : public Shapes::Shape {
    private:
        Shapes::Point center_;
        int radius_;
    public:
        Circle(int xCenter, int yCenter, int radius);
        bool isIn(int x, int y) const override;
        int x() const;
        int y() const;
        int getRadius() const;
    };

} // Shapes

#endif //ZAD4SHAPEDRAWING_DLASTUDENTOW_CIRCLE_H
