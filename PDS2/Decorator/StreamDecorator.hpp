#ifndef STREAM_DECORATOR_H
#define STREAM_DECORATOR_H

#include "AbstractStream.hpp"

/**
 * \brief This is the basic decorator. Every other decorator will have to
 * implement it.
 */
class StreamDecorator: public AbstractStream {

public:
  /**
   * \brief The constructor, which simply binds the abstract stream to the
   * internal state of this object.
   * \param the object that must be decorated.
   */
  StreamDecorator(AbstractStream* streamObj): _streamObj(streamObj) {}

  /**
   * \brief The destructor is the default destructor produced by the compiler.
   */
  ~StreamDecorator() {};

  /**
   * \brief This is the method that will have to be overriden by whatever
   * decorator surrounds this class.
   * \return the unmodified decorated string.
   */
  std::string toString() override {
    return _streamObj->toString();
  }

  private:
  AbstractStream *_streamObj; ///< A pointer to the decorated object.
};

#endif