This is an experiment in different types of object modeling and APIs in C++. It is currently a work in progress.

The current set of objects are in a namespace `Objects`. The following classes are defined:

 * **Object** - A base object type
 * **Class** - A simple object for class-level information about objects
 * **Exception** - A base class for exceptions
 * **Sequence** - An abstract interface for list-like structures
 * **StaticArray** - An immutable array
 * **Array** - A modifiable array with a fixed length
 * **Vector** - A modifiable array which can grow and shrink

The `StaticArray`, `Array`, and `Vector` classes also offer variants that allow an error value to be specified in place of exception throwing behavior when bounds are exceeded. This allows you do to things like:

```cpp
void printContents(const Vector<int> list&) {
  VectorWithErrorHandling<int> items = list.withErrorHandling(-1);
  int item;

  while ((item = items.pop()) != -1)
    printf("got = %d\n", item);
}
```

The example is a contrived, but for some types which have an unambiguous difference between an empty and a non-empty value, that behavior can make for easier programming than dealing with exceptions.
