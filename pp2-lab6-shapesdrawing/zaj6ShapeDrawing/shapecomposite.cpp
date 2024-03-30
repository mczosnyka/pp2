#include "shapecomposite.h"

namespace Shapes {

    ShapeComposite::ShapeComposite(shared_ptr<Shape> shape1, shared_ptr<Shape> shape2, ShapeOperation operation): shape1_(shape1), shape2_(shape2), operation_(operation){}
    bool ShapeComposite::isIn(int x, int y) const{
        if(operation_ == ShapeOperation::INTERSECTION){
            if(shape1_->isIn(x, y) && shape2_->isIn(x, y)){
                return true;
            };
        }
        else if(operation_ == ShapeOperation::SUM){
            if(shape1_->isIn(x, y) || shape2_->isIn(x, y)){
                return true;
            };
        }
        else if(operation_ == ShapeOperation::DIFFERENCE){
            if(shape1_->isIn(x, y) && !shape2_->isIn(x, y)){
                return true;
            }
        }
        return false;
    }
} // Shapes