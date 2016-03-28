#ifndef __included_Objects_StaticArray_hpp__
#define __included_Objects_StaticArray_hpp__

#include <Sequence.hpp>

namespace Objects {

  extern const Class StaticArrayClass;

  template <class T> class StaticArrayWithErrorHandling;

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

    T get(index_t index) const {
      index = normalizeIndex(index);
      if ( ! indexInRange(index) ) return errorValue();
      return _data[index];
    }

    T operator[](index_t index) const { return get(index); }

    virtual StaticArray<T>& operator=(const StaticArray<T>& array) {
      assignArray(array);
      return *this;
    }

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

    virtual T errorValue() const { throw Exception("Index out of range"); }
    virtual bool hasErrorValue() const { return false; }

    inline StaticArrayWithErrorHandling<T> withErrorHandling();
    inline StaticArrayWithErrorHandling<T> withErrorHandling(const T& errorValue);

  protected:

    index_t normalizeIndex(index_t index) const {
      return (index < 0 ? size() + index : index);
    }

    bool indexInRange(index_t index) const {
      return (index < size() && index >= 0);
    }

    void assignArray(const StaticArray<T>& array) {
      _size = 0;

      if (_data) {
        delete[] _data;
        _data = 0;
      }

      initWithData(array.cArray(), array.size());
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


  template <class T> class ArrayErrorHandling {
  public:
    virtual T errorValue() const {
      if (_throwExceptions) throw Exception("Index out of range");
      return _errorValue;
    }
    virtual void errorValue(const T& value) {
      _throwExceptions = false;
      _errorValue = value;
    }
    virtual void resetErrorValue() {
      _throwExceptions = true;
    }
    virtual bool hasErrorValue() const {
      return !_throwExceptions;
    }

  protected:
    ArrayErrorHandling() : _throwExceptions(true) { }
    ArrayErrorHandling(const ArrayErrorHandling& copy) : _throwExceptions(!copy.hasErrorValue()) {
      if (!_throwExceptions) _errorValue = copy.errorValue();
    }
    ArrayErrorHandling(bool useExceptions, const T& errorValue) : _throwExceptions(useExceptions), _errorValue(errorValue) { }

    void assignErrorHandling(const ArrayErrorHandling& copy) {
      _throwExceptions = ! copy.hasErrorValue();
      if (!_throwExceptions) _errorValue = copy.errorValue();
    }

    bool _throwExceptions;
    T _errorValue;
  };


  template <class T> class StaticArrayWithErrorHandling : public StaticArray<T>, public ArrayErrorHandling<T> {
  public:
    StaticArrayWithErrorHandling() { }
    StaticArrayWithErrorHandling(const StaticArray<T>& copy) : StaticArray<T>(copy) { }
    StaticArrayWithErrorHandling(const StaticArrayWithErrorHandling<T>& copy) : ArrayErrorHandling<T>(copy), StaticArray<T>(copy) { }

    virtual StaticArrayWithErrorHandling<T>& operator=(const StaticArray<T>& array) {
      this->assignArray(array);
      return *this;
    }

    virtual StaticArrayWithErrorHandling<T>& operator=(const StaticArrayWithErrorHandling<T>& array) {
      this->assignArray(array);
      this->assignErrorHandling(array);
      return *this;
    }

    virtual T errorValue() const { return ArrayErrorHandling<T>::errorValue(); }
    virtual void errorValue(const T& value) { ArrayErrorHandling<T>::errorValue(value); }
    virtual bool hasErrorValue() const { return ArrayErrorHandling<T>::hasErrorValue(); }
  };


  template <class T> inline StaticArrayWithErrorHandling<T> StaticArray<T>::withErrorHandling() {
    return StaticArrayWithErrorHandling<T>(*this);
  }

  template <class T> inline StaticArrayWithErrorHandling<T> StaticArray<T>::withErrorHandling(const T& errorValue) {
    StaticArrayWithErrorHandling<T> copy(*this);
    copy.errorValue(errorValue);
    return copy;
  }

};

#endif // __included_Objects_StaticArray_hpp__
