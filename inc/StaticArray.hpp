#ifndef __included_Objects_StaticArray_hpp__
#define __included_Objects_StaticArray_hpp__

#include <Sequence.hpp>

namespace Objects {

  extern const Class StaticArrayClass;

  template <class T> class StaticArray : public Sequence<T> {
  public:
    typedef typename Sequence<T>::index_t index_t;

    StaticArray() : _size(0), _data(0) { }

    StaticArray(index_t size) : _size(0), _data(0) { initWithSize(size); }

    StaticArray(const T* array, index_t size) : _size(0), _data(0) {
      initWithSize(size);
      for (index_t i = 0; i < size; ++i) _data[i] = array[i];
    }

    ~StaticArray() {
      if (_data) {
        delete[] _data;
        _data = 0;
      }
    }

    const Class& classInfo() const { return StaticArrayClass; }

    index_t size() const { return _size; }

    T* cArray() { return _data; }
    const T* cArray() const { return _data; }

    T get(index_t index) const { return _data[normalizeIndex(index)]; }

    T operator[](index_t index) const { return _data[normalizeIndex(index)]; }

    virtual bool operator==(const Sequence<T>& seq) const {
      index_t len = size();

      if (len != seq.size()) return false;

      for (index_t i = 0; i < len; ++i)
        if ( ! (this->get(i) == seq.get(i)) )
          return false;

      return true;
    }

    virtual bool operator!=(const Sequence<T>& seq) const { return ! ( *this == seq ); }

  protected:

    index_t normalizeIndex(index_t index) const {
      index_t s = size();

      if (index < 0) index = s + index;
      if (index >= s || index < 0) throw Exception("Index out of range");

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

#endif // __included_Objects_StaticArray_hpp__
