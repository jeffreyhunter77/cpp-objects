#ifndef __included_Objects_Array_hpp__
#define __included_Objects_Array_hpp__

#include <StaticArray.hpp>

namespace Objects {

  extern const Class ArrayClass;

  template <class T> class Array : public StaticArray<T> {
  public:
    typedef typename Sequence<T>::index_t index_t;

    Array() : StaticArray<T>() { }
    Array(index_t size) : StaticArray<T>(size) { }
    Array(const T* array, index_t size) : StaticArray<T>(array, size) { }
    Array(const StaticArray<T>& array) : StaticArray<T>(array) { }

    const Class& classInfo() const { return ArrayClass; }

    virtual void set(index_t index, const T& value) { this->_data[this->normalizeIndex(index)] = value; }

    virtual T& operator[](index_t index) { return this->_data[this->normalizeIndex(index)]; }
  };

};

#endif // __included_Objects_Array_hpp__
