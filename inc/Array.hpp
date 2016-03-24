#ifndef __included_Objects_Array_hpp__
#define __included_Objects_Array_hpp__

#include <Object.hpp>
#include <Class.hpp>
#include <Exception.hpp>

namespace Objects {

  extern const Class ArrayClass;

  template <class T> class Array : public Object {
  public:
    typedef long index_t;

    Array() : _size(0), _data(0) { }

    Array(index_t size) : _size(0), _data(0) { initWithSize(size); }

    Array(T* array, index_t size) : _size(0), _data(0) {
      initWithSize(size);
      for (index_t i = 0; i < size; ++i) _data[i] = array[i];
    }

    ~Array() {
      if (_data) {
        delete[] _data;
        _data = 0;
      }
    }

    const Class& classInfo() const { return ArrayClass; }

    index_t size() const { return _size; }
    
    T* cArray() { return _data; }
    const T* cArray() const { return _data; }

    T get(index_t index) const { return _data[normalizeIndex(index)]; }
    
    T operator[](index_t index) const { return _data[normalizeIndex(index)]; }

  protected:

    index_t normalizeIndex(index_t index) const {
      if (index < 0) index = _size + index;
      if (index >= _size || index < 0) throw Exception("Index out of range");
      return index;
    }

    index_t _size;
    T* _data;

  private:
    void initWithSize(index_t size) {
      if(size < 0) throw Exception("Invalid size value");

      _data = new T[size];

      if (!_data) throw Exception("Out of memory");

      _size = size;
    }
  };

};

#endif // __included_Objects_Array_hpp__
