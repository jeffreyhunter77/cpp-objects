#ifndef __included_Objects_Sequence_hpp__
#define __included_Objects_Sequence_hpp__

#include <Object.hpp>
#include <Class.hpp>
#include <Exception.hpp>

namespace Objects {

  extern const Class SequenceClass;

  template <class T> class Sequence : public Object {
  public:
    typedef long index_t;

    const Class& classInfo() const { return SequenceClass; }

    virtual index_t size() const = 0;
    virtual T* cArray() = 0;
    virtual const T* cArray() const = 0;
    virtual T get(index_t index) const = 0;
    virtual T operator[](index_t index) const = 0;
  };

};

#endif // __included_Objects_Sequence_hpp__
