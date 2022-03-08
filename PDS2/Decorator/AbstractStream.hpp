#ifndef ABSTRACT_STREAM_H
#define ABSTRACT_STREAM_H

#include <string>

/**
 * \brief An abstract class that denotes a stream. In our case, a stream is
 * just a string, i.e., a sequence of characteres.
 */
class AbstractStream {
public:
  /**
   * This is the abstract method that returns the string that this class
   * encodes. Notice that this method has no body, i.e., it is assigned to zero.
   * \return the string that this object represents.
   */
  virtual std::string toString() = 0;

  /**
   * The virtual destructor. Every abstract class, e.g., a class with a virtual
   * method assigned to zero, needs a virtual destructor. Why does the abstract
   * class need a virtual destructor? Any user of your class will probably hold 
   * a pointer to the abstract class, not a pointer to the concrete
   * implementation. Thus, when they try to delete it, if the destructor is
   * non-virtual, they will call the abstract class's destructor (or the
   * compiler-provided default, if you didn't specify one), not the derived
   * class's destructor. If there are memory to be liberated in the concrete
   * class, then the destructor of the abstract class will not be able to do it.
   * That will lead to a memory leak.
   */
  virtual ~AbstractStream() {};
};

#endif