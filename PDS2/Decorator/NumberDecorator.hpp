#ifndef NUMBER_DECORATOR_H
#define NUMBER_DECORATOR_H

#include "StreamDecorator.hpp"

/**
 * \brief This decorator takes a stream, and adds a '+' sign in front of every
 * integer in this stream. This decorator preserves one space between
 * consecutive tokens (no space after the last token). Notice that real
 * numbers with a dot '.' remain unaltered.
 * Example: "a 23 b 3.14" => "a +23 b 3.14"
 */
class NumberDecorator: public StreamDecorator {

public:
  /**
   * \brief The constructor, which sends the object that will be decorated,
   * i.e., the stream, to the base decorator.
   * \param the object that must be decorated.
   */
  NumberDecorator(AbstractStream* streamObj): StreamDecorator(streamObj) {}

  /**
   * \brief The destructor is the default destructor produced by the compiler.
   */
  ~NumberDecorator() {};

  /**
   * \brief This decorated method adds the '+' sign in front of the integers.
   * \return the decorated string.
   */
  std::string toString() override;
};

#endif