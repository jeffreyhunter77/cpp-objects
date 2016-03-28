#include <StaticArray.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string.h>

using namespace Objects;

struct Num {
  int value;

  Num(int val = 100) :value(val) { }
  bool operator==(const Num& n) const { return value == n.value; }
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

  SECTION("allows copy construction") {
    IntStaticArray a((int[]){1, 3, 5}, 3);
    IntStaticArray b(a);

    REQUIRE( a == b );
    REQUIRE( a.cArray() != b.cArray() );
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

TEST_CASE("StaticArray.operator==", "[StaticArray]") {
  IntStaticArray a((int[]){1, 3, 5, 7, 9}, 5);

  SECTION("returns true for its own identity") {
    REQUIRE( a == a );
  }

  SECTION("returns true for the empty set") {
    IntStaticArray empty1;
    IntStaticArray empty2;

    REQUIRE(empty1 == empty2 );
  }

  SECTION("returns true when both sets have equivalent contents") {
    IntStaticArray b((int[]){1, 3, 5, 7, 9}, 5);

    REQUIRE( a == b );
  }

  SECTION("returns false for sets with different lengths") {
    IntStaticArray b((int[]){1, 3, 5, 7, 9, 11, 13}, 7);

    REQUIRE( ! (a == b) );
    REQUIRE( ! (b == a) );
  }

  SECTION("returns false for sets with different contents") {
    IntStaticArray b((int[]){2, 4, 6, 8, 10}, 5);

    REQUIRE( ! (a == b) );
  }

  SECTION("returns false for sets with contents in different order") {
    IntStaticArray b((int[]){1, 3, 7, 5, 9}, 5);

    REQUIRE( ! (a == b) );
  }
}

TEST_CASE("StaticArray.operator!=", "[StaticArray]") {
  IntStaticArray a((int[]){1, 3, 5, 7, 9}, 5);
  IntStaticArray b((int[]){1, 3, 7, 5, 9}, 5);

  SECTION("is the opposite of ==") {
    REQUIRE( a != b );
  }
}

TEST_CASE("StaticArray.slice(start, length)", "[StaticArray]") {
  IntStaticArray a((int[]){1, 3, 5, 7, 9, 11, 13}, 7);
  IntStaticArray empty;

  SECTION("returns a deep copy starting at offset for the given length") {
    REQUIRE( a.slice(2, 3) == IntStaticArray((int[]){5, 7, 9}, 3) );
    REQUIRE( a.slice(2, 3).cArray() != a.cArray() );
  }

  SECTION("can return a zero-length slice") {
    REQUIRE( a.slice(2, 0) == empty );
    REQUIRE( empty.slice(0, 0) == empty );
  }

  SECTION("accepts a negative offset as distance from the end") {
    REQUIRE( a.slice(-3, 3) == IntStaticArray((int[]){9, 11, 13}, 3) );
  }

  SECTION("accepts a negative length as distance from the end") {
    REQUIRE( a.slice(2, -2) == IntStaticArray((int[]){5, 7, 9}, 3) );
  }

  SECTION("ignores an offset beyond the end of the array") {
    REQUIRE( a.slice(12, 3) == empty );
  }

  SECTION("ignores an offset before the start of the array") {
    REQUIRE( a.slice(-12, 3) == empty );
    REQUIRE( a.slice(-9, 3) == IntStaticArray((int[]){1}, 1) );
  }

  SECTION("ignores length beyond the end of the array") {
    REQUIRE( a.slice(3, 12) == IntStaticArray((int[]){7, 9, 11, 13}, 4) );
  }

  SECTION("ignores length before the starting offset") {
    REQUIRE( a.slice(3, -12) == empty );
  }
}

TEST_CASE("StaticArray.slice(start)", "[StaticArray]") {
  IntStaticArray a((int[]){1, 3, 5, 7, 9, 11, 13}, 7);
  IntStaticArray empty;

  SECTION("returns a deep copy from start to the end of the string") {
    REQUIRE( a.slice(2) == IntStaticArray((int[]){5, 7, 9, 11, 13}, 5) );
    REQUIRE( a.slice(2).cArray() != a.cArray() );
  }

  SECTION("can return a zero-length slice") {
    REQUIRE( empty.slice(0) == empty );
  }

  SECTION("accepts a negative offset as distance from the end") {
    REQUIRE( a.slice(-3) == IntStaticArray((int[]){9, 11, 13}, 3) );
  }

  SECTION("ignores an offset beyond the end of the array") {
    REQUIRE( a.slice(12) == empty );
  }

  SECTION("ignores an offset before the start of the array") {
    REQUIRE( a.slice(-12) == a );
  }
}

TEST_CASE("StaticArray.operator=", "[StaticArray]") {
  SECTION("allows assignment") {
    IntStaticArray a((int[]){1, 3, 5}, 3);
    IntStaticArray b;

    REQUIRE( a != b );

    b = a;

    REQUIRE( a == b );
    REQUIRE( a.cArray() != b.cArray() );
  }
}

TEST_CASE("StaticArray.errorValue()", "[StaticArray]") {
  IntStaticArray a;

  SECTION("throws an error value") {
    REQUIRE_THROWS_AS( a.errorValue(), Exception );
  }
}

TEST_CASE("StaticArray.hasErrorValue", "[StaticArray]") {
  IntStaticArray a;

  SECTION("returns false") {
    REQUIRE( ! a.hasErrorValue() );
  }
}
