#include "Vec1D.hpp"


    Vec1D::Vec1D(double x): _x(x) {}

    double Vec1D::getX() const { return _x; }

    std::string Vec1D::to_string()  const {
      std::string str = (std::to_string(_x));
      return  str;
    }
    double Vec1D::get_norm() const { return _x; }

