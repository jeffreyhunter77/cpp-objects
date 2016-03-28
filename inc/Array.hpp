#ifndef __included_Objects_Array_hpp__
#define __included_Objects_Array_hpp__

#include <StaticArray.hpp>

namespace Objects {

  extern const Class ArrayClass;

  template <class T> class ArrayWithErrorHandling;

  template <class T> class Array : public StaticArray<T> {
  public:
    typedef typename Sequence<T>::index_t index_t;

    Array() : StaticArray<T>() { }
    Array(index_t size) : StaticArray<T>(size) { }
    Array(const T* array, index_t size) : StaticArray<T>(array, size) { }
    Array(const StaticArray<T>& array) : StaticArray<T>(array) { }

    const Class& classInfo() const { return ArrayClass; }

    virtual void set(index_t index, const T& value) { this->_data[indexForSet(index)] = value; }

    virtual T& operator[](index_t index) { return this->_data[indexForSet(index)]; }

    inline ArrayWithErrorHandling<T> withErrorHandling();
    inline ArrayWithErrorHandling<T> withErrorHandling(const T& errorValue);

  protected:
    index_t indexForSet(index_t index) {
      index = this->normalizeIndex(index);

      if ( ! this->indexInRange(index) ) throw Exception("Index out of range");

      return index;
    }
  };

  template <class T> class ArrayWithErrorHandling : public Array<T>, public ArrayErrorHandling<T> {
  public:
    ArrayWithErrorHandling() { }
    ArrayWithErrorHandling(const Array<T>& copy) : Array<T>(copy) { }
    ArrayWithErrorHandling(const ArrayWithErrorHandling<T>& copy) : ArrayErrorHandling<T>(copy), Array<T>(copy) { }

    virtual ArrayWithErrorHandling<T>& operator=(const Array<T>& array) {
      this->assignArray(array);
      return *this;
    }

    virtual ArrayWithErrorHandling<T>& operator=(const ArrayWithErrorHandling<T>& array) {
      this->assignArray(array);
      this->assignErrorHandling(array);
      return *this;
    }

    virtual T errorValue() const { return ArrayErrorHandling<T>::errorValue(); }
    virtual void errorValue(const T& value) { ArrayErrorHandling<T>::errorValue(value); }
    virtual bool hasErrorValue() const { return ArrayErrorHandling<T>::hasErrorValue(); }
  };


  template <class T> inline ArrayWithErrorHandling<T> Array<T>::withErrorHandling() {
    return ArrayWithErrorHandling<T>(*this);
  }

  template <class T> inline ArrayWithErrorHandling<T> Array<T>::withErrorHandling(const T& errorValue) {
    ArrayWithErrorHandling<T> copy(*this);
    copy.errorValue(errorValue);
    return copy;
  }

};

#endif // __included_Objects_Array_hpp__
