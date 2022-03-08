#ifndef COMMA_DECORATOR_H
#define COMMA_DECORATOR_H

#include "StreamDecorator.hpp"

/**
 * \brief This decorator takes a stream, and adds a comma after every token
 * that constitutes it, with a trailing empty space after and before the comma.
 * No comma is added after the last token.
 * Example: "a 23 b   3.14" =>  "a , 23 , b , 3.14"
 * Notice that multiple empty spaces are collapsed into one single space.
 */
class CommaDecorator: public StreamDecorator {

public:
  /**
   * \brief The constructor, which sends the object that will be decorated,
   * i.e., the stream, to the base decorator.
   * \param the object that must be decorated.
   */
  CommaDecorator(AbstractStream* streamObj): StreamDecorator(streamObj) {}

  /**
   * \brief The destructor is the default destructor produced by the compiler.
   */
  ~CommaDecorator() {};

  /**
   * \brief This decorated method adds the comma between the tokens of the
   * stream.
   * \return the decorated string with commas in between the tokens.
   */
  std::string toString() override;
};

#endif