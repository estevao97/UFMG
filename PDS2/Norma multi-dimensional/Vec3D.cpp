#include "Vec3D.hpp"


Vec3D::Vec3D(double x, double y, double z): Vec2D(x, y), _z(z) {}

double Vec3D::getZ() const { return _z; }

std::string Vec3D::to_string() const {
 std::string str = (Vec2D::to_string()+","+std::to_string(_z));
 return  str;
}

double Vec3D::get_norm() const {return sqrt(_x*_x + _y*_y + _z*_z);}
  