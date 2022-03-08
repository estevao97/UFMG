#ifndef PARENTHESES_DECORATOR_H
#define PARENTHESES_DECORATOR_H

#include "StreamDecorator.hpp"

/**
 * \brief This decorator takes a stream, and adds parentheses before and after
 * it. There will be a space between each parenthesis and the closest token.
 * For instance, if the stream is "a 23 b 3.14", then it produces
 * "( a, 23, b, 3.14 )".
 */
class ParenthesesDecorator: public StreamDecorator {

public:
  /**
   * \brief The constructor, which sends the object that will be decorated,
   * i.e., the stream, to the base decorator.
   * \param the object that must be decorated.
   */
  ParenthesesDecorator(AbstractStream* streamObj): StreamDecorator(streamObj) {}

  /**
   * \brief The destructor is the default destructor produced by the compiler.
   */
  ~ParenthesesDecorator() {};

  /**
   * \brief This decorated method surrounds the stream with parentheses.
   * \return the string with the parentheses.
   */
  std::string toString() override;
};

#endif