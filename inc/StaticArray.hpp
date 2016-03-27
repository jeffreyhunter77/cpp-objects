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
      initWithData(array, size);
    }

    StaticArray(const StaticArray<T>& array) : _size(0), _data(0) {
      initWithData(array.cArray(), array.size());
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

    virtual StaticArray<T> slice(index_t start) const {
      if (start < 0)
        return slice(start, -start);
      else if (start <= size())
        return slice(start, size() - start);
      else
        return slice(start, 0);
    }

    virtual StaticArray<T> slice(index_t start, index_t length) const {
      index_t sz = size();

      if (start < 0) start = sz + start;
      if (start >= sz) return StaticArray<T>();

      if (length < 0) {
        length = sz + length;
        if (start > 0) length -= start;
      }

      if (start < 0) {
        length += start;
        start = 0;
      }

      if (length < 0) length = 0;
      if (length > start + sz) length = sz - start;

      return StaticArray<T>(&(_data[start]), length);
    }

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

    void initWithData(const T* array, index_t size) {
      initWithSize(size);
      for (index_t i = 0; i < size; ++i) _data[i] = array[i];
    }
  };

};

#endif // __included_Objects_StaticArray_hpp__
