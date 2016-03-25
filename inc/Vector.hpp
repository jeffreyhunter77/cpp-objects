#ifndef __included_Objects_Vector_hpp__
#define __included_Objects_Vector_hpp__

#include <Array.hpp>

namespace Objects {

  extern const Class VectorClass;

  template <class T> class Vector : public Array<T> {
  private:
    typedef Array<T> super;

  public:
    typedef typename Sequence<T>::index_t index_t;

    Vector() : _entries(0), Array<T>() { }
    Vector(index_t capacity) : _entries(0), Array<T>(capacity) { }
    Vector(const T* array, index_t size) : _entries(size), Array<T>(array, size) { }

    const Class& classInfo() const { return VectorClass; }

    index_t size() const { return _entries; }
    virtual index_t capacity() const { return super::size(); }

    virtual Vector<T>& push(T item) {
      ensureCapacity(_entries + 1);
      super::set(_entries++, item);
      return *this;
    }

  protected:
    const static index_t MIN_CAPACITY = 6;

    void ensureCapacity(index_t minCapacity) {
      index_t currentCapacity = capacity();

      if (currentCapacity >= minCapacity) return;

      index_t newCapacity = currentCapacity < MIN_CAPACITY ? MIN_CAPACITY : currentCapacity * 2;
      if (newCapacity < currentCapacity)
        throw Exception("Maximum vector size exceeded");

      T* _newData = new T[newCapacity];
      if (!_newData)
        throw Exception("Out of memory");

      for (index_t i = 0; i < _entries; ++i)
        _newData[i] = this->_data[i];

      if (this->_data) delete[] this->_data;

      this->_data = _newData;
      this->_size = newCapacity;
    }

    index_t _entries;
  };

};

#endif // __included_Objects_Vector_hpp__
