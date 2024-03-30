#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#include <memory>
#ifndef TESTS_SHAPECOMPOSITE_H
#define TESTS_SHAPECOMPOSITE_H

using namespace std;
namespace Shapes {
    enum class ShapeOperation{
        INTERSECTION,
        SUM,
        DIFFERENCE
    };

class ShapeComposite : public Shapes::Shape {
    private:
        shared_ptr<Shape> shape1_;
        shared_ptr<Shape> shape2_;
        ShapeOperation operation_;
    public:
        ShapeComposite(shared_ptr<Shape> shape1, shared_ptr<Shape> shape2, ShapeOperation operation);
        bool isIn(int x, int y) const override;

    };

}

#endif //TESTS_SHAPECOMPOSITE_H
