#include <StaticArray.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string.h>

using namespace Objects;

struct Num {
  int value;

  Num(int val = 100) :value(val) { }
};

typedef StaticArray<int> IntStaticArray;
typedef StaticArray<struct Num> NumStaticArray;

TEST_CASE("StaticArray constructor", "[StaticArray]") {

  SECTION("without arguments creates an empty array") {
    IntStaticArray a;

    REQUIRE( a.size() == 0 );
  }

  SECTION("allocates an array with the specified size") {
    IntStaticArray a(10);

    REQUIRE( a.size() == 10 );
  }

  SECTION("initializes the array") {
    NumStaticArray a(10);

    for (int i = 0; i < 10; ++i) {
      REQUIRE( a.get(i).value == 100 );
    }
  }

  SECTION("performs a copy when initialized with an array and size") {
    int evens[] = {2, 4, 6, 8, 10, 12, 14};
    IntStaticArray a(evens, 7);

    REQUIRE( a.size() == 7 );

    for (int i = 0; i < 7; ++i) {
      REQUIRE( a.get(i) == evens[i] );
    }

    REQUIRE( a.cArray() != evens );
  }

  SECTION("throws an exception when given an invalid size") {
    REQUIRE_THROWS_AS( IntStaticArray a(-40), Exception );
  }

}

TEST_CASE("StaticArray.classInfo", "[StaticArray]") {
  IntStaticArray a;

  SECTION("returns the StaticArray class info object") {
    REQUIRE( strcmp(a.classInfo().name(), "StaticArray") == 0 );
  }

}

TEST_CASE("StaticArray.get", "[StaticArray]") {
  int odds[] = {1, 3, 5, 7, 9, 11, 13};
  IntStaticArray a(odds, 7);

  SECTION("returns the item at the provided zero-based index") {
    REQUIRE( a.get(2) == 5 );
  }

  SECTION("returns items offset from the end of the list when given a negative index") {
    REQUIRE( a.get(-3) == 9 );
  }

  SECTION("throws an exception when given an index past the end of the list") {
    REQUIRE_THROWS_AS( a.get(7), Exception );
    REQUIRE_THROWS_AS( a.get(-12), Exception );
  }
}


TEST_CASE("StaticArray.operator[]", "[StaticArray]") {
  int odds[] = {1, 3, 5, 7, 9, 11, 13};
  IntStaticArray a(odds, 7);

  SECTION("returns the item at the provided zero-based index") {
    REQUIRE( a[2] == 5 );
  }

  SECTION("returns items offset from the end of the list when given a negative index") {
    REQUIRE( a[-3] == 9 );
  }

  SECTION("throws an exception when given an index past the end of the list") {
    REQUIRE_THROWS_AS( a[7], Exception );
    REQUIRE_THROWS_AS( a[-12], Exception );
  }
}

