#ifndef VEC_2D
#define VEC_2D

#include "Vec1D.hpp"
#include<cmath>

/**
 * \brief a two-dimensional vector.
 */
class Vec2D: public Vec1D {
  protected:
    double _y; ///< The second coordinate of the vector.
  public:
    Vec2D(double x, double y);
    double getY() const;
    virtual std::string to_string() const override;

    /**
     * \brief Provides the norm of the vector, that is, the distance from this
     * vector to the origin.
     * \return a double that represents the vector norm. In the case of a
     * 2D vector, that's the square root of the square of the coordinates,
     * that is: sqrt(x*x + y*y).
     */
    virtual double get_norm() const override;
  
};

#endif
