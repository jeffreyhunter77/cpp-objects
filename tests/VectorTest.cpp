#include <Vector.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string.h>

using namespace Objects;

typedef Vector<int> IntVector;

TEST_CASE("Vector constructor", "[Vector]") {

  SECTION("without arguments creates an empty vector") {
    IntVector v;

    REQUIRE( v.size() == 0 );
    REQUIRE( v.capacity() == 0 );
  }

  SECTION("allocates a vector with the specified capacity when given a capacity") {
    IntVector v(10);

    REQUIRE( v.size() == 0 );
    REQUIRE( v.capacity() == 10 );
  }

  SECTION("performs a copy when initialized with an array and size") {
    int evens[] = {2, 4, 6, 8, 10, 12, 14};
    IntVector v(evens, 7);

    REQUIRE( v.size() == 7 );

    for (int i = 0; i < 7; ++i) {
      REQUIRE( v.get(i) == evens[i] );
    }

    REQUIRE( v.cArray() != evens );
  }

}

TEST_CASE("Vector.classInfo", "[Vector]") {
  IntVector v;

  SECTION("returns the Vector class info object") {
    REQUIRE( strcmp(v.classInfo().name(), "Vector") == 0 );
  }

}

TEST_CASE("Vector.push", "[Vector]") {
  IntVector v(3);

  SECTION("adds an item to the end of the list") {
    v.push(1);

    REQUIRE( v.size() == 1 );
    REQUIRE( v[0] == 1 );
  }

  SECTION("permits chaining") {
    v.push(1).push(3);

    REQUIRE( v.size() == 2 );
    REQUIRE( v[0] == 1 );
    REQUIRE( v[1] == 3 );
  }

  SECTION("grows the list when capacity is exceeded") {
    int* oldData = v.cArray();
    v.push(1).push(3).push(5).push(7).push(9);

    REQUIRE( v.size() == 5 );
    REQUIRE( v.capacity() > 3 );
    REQUIRE( v[0] == 1 );
    REQUIRE( v[1] == 3 );
    REQUIRE( v[2] == 5 );
    REQUIRE( v[3] == 7 );
    REQUIRE( v[4] == 9 );
    REQUIRE( v.cArray() != oldData );
  }

  SECTION("grows a list from an initial capacity of 0") {
    IntVector emptyV(0);
    emptyV.push(3).push(2).push(1);

    REQUIRE( emptyV.size() == 3 );
    REQUIRE( emptyV.capacity() >= 3 );
    REQUIRE( emptyV[0] == 3 );
    REQUIRE( emptyV[1] == 2 );
    REQUIRE( emptyV[2] == 1 );
  }
}

TEST_CASE("Vector.get", "[Vector]") {
  IntVector v(20);
  v.push(1).push(3).push(5);

  SECTION("throws an exception when given an index past the end of the list") {
    REQUIRE_THROWS_AS( v.get(7), Exception );
    REQUIRE_THROWS_AS( v.get(-12), Exception );
  }
}

TEST_CASE("Vector.pop", "[Vector]") {
  int odds[] = {1, 3, 5, 7, 9, 11, 13};
  IntVector v(odds, 7);

  SECTION("removes the last item from the list and returns it") {
    REQUIRE( v.pop() == 13 );
    REQUIRE( v.size() == 6 );
    REQUIRE( v[5] == 11 );
  }

  SECTION("throws an exception when called on an empty vector") {
    IntVector empty;
    REQUIRE_THROWS_AS( empty.pop(), Exception );
    REQUIRE( empty.size() == 0 );
  }
}

TEST_CASE("Vector.insert", "[Vector]") {
  int odds[] = {1, 3, 5};
  IntVector v(odds, 3);

  SECTION("supports addition of an item at the start of the list") {
    v.insert(0, -1);

    REQUIRE( v.size() == 4 );
    REQUIRE( v.capacity() >= 4 );
    REQUIRE( v[0] == -1 );
    REQUIRE( v[1] == 1 );
    REQUIRE( v[2] == 3 );
    REQUIRE( v[3] == 5 );
  }

  SECTION("supports addition of an item at the end of the list") {
    v.insert(3, 7);

    REQUIRE( v.size() == 4 );
    REQUIRE( v.capacity() >= 4 );
    REQUIRE( v[0] == 1 );
    REQUIRE( v[1] == 3 );
    REQUIRE( v[2] == 5 );
    REQUIRE( v[3] == 7 );
  }

  SECTION("supports insertion of an item in the middle of the list") {
    v.insert(1, 2);

    REQUIRE( v.size() == 4 );
    REQUIRE( v.capacity() >= 4 );
    REQUIRE( v[0] == 1 );
    REQUIRE( v[1] == 2 );
    REQUIRE( v[2] == 3 );
    REQUIRE( v[3] == 5 );
  }

  SECTION("treats negative indexes as offsets from the end") {
    v.insert(-1, 4);

    REQUIRE( v.size() == 4 );
    REQUIRE( v.capacity() >= 4 );
    REQUIRE( v[0] == 1 );
    REQUIRE( v[1] == 3 );
    REQUIRE( v[2] == 4 );
    REQUIRE( v[3] == 5 );
  }

  SECTION("supports chaining") {
    v.insert(3, 7).insert(4, 9);

    REQUIRE( v.size() == 5 );
    REQUIRE( v[3] == 7 );
    REQUIRE( v[4] == 9 );
  }

  SECTION("throws an exception when called with an invalid index") {
    REQUIRE_THROWS_AS( v.insert(4, 9), Exception );
    REQUIRE_THROWS_AS( v.insert(-4, -1), Exception );
  }
}
