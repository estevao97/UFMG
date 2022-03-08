#ifndef CONCRETE_STREAM_H
#define CONCRETE_STREAM_H

#include "AbstractStream.hpp"

/**
 * \brief This is the concrete component of the decorator. It provides a very
 * simple implementation for the abstract stream.
 */
class ConcreteStream: public AbstractStream {

public:
  /**
   * \brief Constructor. It receives a string, and binds it to the internal
   * string that this class encapsulates.
   * \param stream: the string that will be represented by this object.
   */
  ConcreteStream(const std::string stream): _stream(stream) {}

  /**
   * \brief simply returns the internal string. No modifications.
   * \return the unmodified string encapsulated by this object.
   */
  std::string toString() override { return this->_stream; }

  private:
    std::string _stream; ///< The string encapsulated by this object.
};

#endif