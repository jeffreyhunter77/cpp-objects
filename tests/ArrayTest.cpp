#include <Array.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string.h>

using namespace Objects;

struct Num {
  int value;

  Num(int val = 100) :value(val) { }
};

typedef Array<int> IntArray;
typedef Array<struct Num> NumArray;

TEST_CASE("Array constructor", "[Array]") {

  SECTION("without arguments creates an empty array") {
    IntArray a;

    REQUIRE( a.size() == 0 );
  }

  SECTION("allocates an array with the specified size") {
    IntArray a(10);

    REQUIRE( a.size() == 10 );
  }

  SECTION("initializes the array") {
    NumArray a(10);

    for (int i = 0; i < 10; ++i) {
      REQUIRE( a.get(i).value == 100 );
    }
  }

  SECTION("performs a copy when initialized with an array and size") {
    int evens[] = {2, 4, 6, 8, 10, 12, 14};
    IntArray a(evens, 7);

    REQUIRE( a.size() == 7 );

    for (int i = 0; i < 7; ++i) {
      REQUIRE( a.get(i) == evens[i] );
    }

    REQUIRE( a.cArray() != evens );
  }

  SECTION("throws an exception when given an invalid size") {
    REQUIRE_THROWS_AS( IntArray a(-40), Exception );
  }

}

TEST_CASE("Array.classInfo", "[Array]") {
  IntArray a;

  SECTION("returns the Array class info object") {
    REQUIRE( strcmp(a.classInfo().name(), "Array") == 0 );
  }

}

TEST_CASE("Array.get", "[Array]") {
  int odds[] = {1, 3, 5, 7, 9, 11, 13};
  IntArray a(odds, 7);

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


TEST_CASE("Array.operator[]", "[Array]") {
  int odds[] = {1, 3, 5, 7, 9, 11, 13};
  IntArray a(odds, 7);

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

TEST_CASE("Array.set", "[Array]") {
  int odds[] = {1, 3, 5, 7, 9, 11, 13};
  IntArray a(odds, 7);

  SECTION("sets the item at the provided zero-based index") {
    a.set(2, 3);
    REQUIRE( a.get(2) == 3 );
  }

  SECTION("sets item offset from the end of the list when given a negative index") {
    a.set(-3, 11);
    REQUIRE( a.get(4) == 11 );
  }

  SECTION("throws an exception when given an index past the end of the list") {
    REQUIRE_THROWS_AS( a.set(7, 0), Exception );
    REQUIRE_THROWS_AS( a.set(-12, 0), Exception );
  }
}

TEST_CASE("Array.operator[]=", "[Array]") {
  int odds[] = {1, 3, 5, 7, 9, 11, 13};
  IntArray a(odds, 7);

  SECTION("sets the item at the provided zero-based index") {
    a[2] = 3;
    REQUIRE( a.get(2) == 3 );
  }

  SECTION("sets item offset from the end of the list when given a negative index") {
    a[-3] = 11;
    REQUIRE( a.get(4) == 11 );
  }

  SECTION("throws an exception when given an index past the end of the list") {
    REQUIRE_THROWS_AS( a[7] = 0, Exception );
    REQUIRE_THROWS_AS( a[-12] = 0, Exception );
  }
}
