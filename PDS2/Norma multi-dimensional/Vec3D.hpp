#ifndef VEC_3D
#define VEC_3D

#include "Vec2D.hpp"

/**
 * \brief A three-dimensional vector.
 */
class Vec3D: public Vec2D {
  protected:
    double _z; ///< The third coordinate of the vector.
  public:
    Vec3D(double x, double y, double z);
    double getZ() const;
    std::string to_string() const override;

    /**
     * \brief Provides the norm of the vector, that is, the distance from this
     * vector to the origin.
     * \return a double that represents the vector norm. In the case of a
     * 3D vector, that's the square root of the square of the coordinates,
     * that is: sqrt(x*x + y*y + z*z).
     */
    virtual double get_norm() const override;
  
};

#endif
