#ifndef __included_Objects_Vector_hpp__
#define __included_Objects_Vector_hpp__

#include <Object.hpp>
#include <Class.hpp>
#include <Exception.hpp>

#include <stdlib.h>

namespace Objects {

  extern const Class VectorClass;

  template <class T> class Vector : public Object {
  public:
    Vector() : _size(0), _capacity(0), _data(0) { }

    Vector(size_t capacity) : _size(0), _capacity(0), _data(0) {
      _data = new T[capacity];

      if (!_data) throw Exception("Out of memory");

      _capacity = capacity;
    }

    ~Vector() {
      if (_data) {
        delete[] _data;
        _data = 0;
      }
    }

    const Class& classInfo() const { return VectorClass; }

    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }

  private:
    size_t _size;
    size_t _capacity;
    T* _data;
  };

};

#endif // __included_Objects_Vector_hpp__
