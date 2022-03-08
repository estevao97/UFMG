#ifndef VEC_H
#define VEC_H

#include <string>

/**
 * \brief Interface that represents every vector, regardless of its dimension.
 */
class Vec {
  public:
    /**
     * \brief String representation of the vector.
     * \return a string that represents the vector, as a tuple of n-dimensions.
     */
    virtual std::string to_string() const = 0;

    /**
     * \brief Provides the norm of the vector, that is, the distance from this
     * vector to the origin.
     * \return a double that represents the vector norm.
     */
    virtual double get_norm() const = 0;

    /**
     * \brief the virtual destructor (or else the compiler will create one
     * for you).
     */
    virtual ~Vec() {};
};

#endif