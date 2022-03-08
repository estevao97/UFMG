#include "Vec2D.hpp"


Vec2D::Vec2D(double x,double y):  Vec1D(x), _y(y) {}

    double Vec2D::getY() const { return _y; }

    std::string Vec2D::to_string()  const {
      std::string str = (Vec1D::to_string()+","+std::to_string(_y));
      return  str;
    }
    double Vec2D::get_norm() const { return sqrt(_x*_x + _y*_y);}