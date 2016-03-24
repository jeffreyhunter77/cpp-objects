#ifndef __included_Objects_Array_hpp__
#define __included_Objects_Array_hpp__

#include <StaticArray.hpp>

namespace Objects {

  extern const Class ArrayClass;

  template <class T> class Array : public StaticArray<T> {
  private:
    typedef StaticArray<T> super;

  public:
    typedef typename Sequence<T>::index_t index_t;

    Array() : StaticArray<T>() { }
    Array(index_t size) : StaticArray<T>(size) { }
    Array(T* array, index_t size) : StaticArray<T>(array, size) { }

    const Class& classInfo() const { return ArrayClass; }

    void set(index_t index, const T& value) { super::_data[super::normalizeIndex(index)] = value; }
  };

};

#endif // __included_Objects_Array_hpp__
