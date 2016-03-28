#ifndef __included_Objects_Vector_hpp__
#define __included_Objects_Vector_hpp__

#include <Array.hpp>

namespace Objects {

  extern const Class VectorClass;

  template <class T> class VectorWithErrorHandling;

  template <class T> class Vector : public Array<T> {
  private:
    typedef Array<T> super;

  public:
    typedef typename Sequence<T>::index_t index_t;

    Vector() : _entries(0), Array<T>() { }
    Vector(index_t capacity) : _entries(0), Array<T>(capacity) { }
    Vector(const T* array, index_t size) : _entries(size), Array<T>(array, size) { }
    Vector(const StaticArray<T>& array) : _entries(array.size()), Array<T>(array) { }

    const Class& classInfo() const { return VectorClass; }

    index_t size() const { return _entries; }
    virtual index_t capacity() const { return super::size(); }

    virtual Vector<T>& push(const T item) { return insert(_entries, item); }
    virtual T pop() { return remove(-1); }
    virtual T shift() { return remove(0); }
    virtual Vector<T>& unshift(const T item) { return insert(0, item); }

    virtual Vector<T>& insert(index_t atIndex, const T item) {
      ensureCapacity(_entries + 1);

      atIndex = atIndex == _entries ? atIndex : this->indexForSet(atIndex);

      shiftLeft(atIndex);

      ++_entries;

      this->set(atIndex, item);

      return *this;
    }

    virtual T remove(index_t atIndex) {
      T item = this->get(atIndex);

      atIndex = this->normalizeIndex(atIndex);
      if (!this->indexInRange(atIndex)) return this->errorValue();

      shiftRight(atIndex);

      --_entries;

      return item;
    }

    virtual Vector<T>& operator=(const StaticArray<T>& array) {
      _entries = 0;
      this->assignArray(array);
      _entries = array.size();
      return *this;
    }

    inline VectorWithErrorHandling<T> withErrorHandling();
    inline VectorWithErrorHandling<T> withErrorHandling(const T& errorValue);

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

    void shiftLeft(index_t fromIndex) {
      for (index_t i = _entries; i > fromIndex; --i)
        this->_data[i] = this->_data[i - 1];
    }

    void shiftRight(index_t fromIndex) {
      for (index_t i = fromIndex; i < _entries - 1; ++i)
        this->_data[i] = this->_data[i + 1];
    }

    index_t _entries;
  };

  template <class T> class VectorWithErrorHandling : public Vector<T>, public ArrayErrorHandling<T> {
  public:
    VectorWithErrorHandling() { }
    VectorWithErrorHandling(const Vector<T>& copy) : Vector<T>(copy) { }
    VectorWithErrorHandling(const VectorWithErrorHandling<T>& copy) : ArrayErrorHandling<T>(copy), Vector<T>(copy) { }

    virtual VectorWithErrorHandling<T>& operator=(const Vector<T>& array) {
      this->assignArray(array);
      return *this;
    }

    virtual VectorWithErrorHandling<T>& operator=(const VectorWithErrorHandling<T>& array) {
      this->assignArray(array);
      this->assignErrorHandling(array);
      return *this;
    }

    virtual T errorValue() const { return ArrayErrorHandling<T>::errorValue(); }
    virtual void errorValue(const T& value) { ArrayErrorHandling<T>::errorValue(value); }
    virtual bool hasErrorValue() const { return ArrayErrorHandling<T>::hasErrorValue(); }
  };


  template <class T> inline VectorWithErrorHandling<T> Vector<T>::withErrorHandling() {
    return VectorWithErrorHandling<T>(*this);
  }

  template <class T> inline VectorWithErrorHandling<T> Vector<T>::withErrorHandling(const T& errorValue) {
    VectorWithErrorHandling<T> copy(*this);
    copy.errorValue(errorValue);
    return copy;
  }

};

#endif // __included_Objects_Vector_hpp__
