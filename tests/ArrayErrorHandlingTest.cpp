#include <StaticArray.hpp>
#include <Array.hpp>
#include <Vector.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string.h>

using namespace Objects;

typedef StaticArray<int> IntStaticArray;
typedef StaticArrayWithErrorHandling<int> IntStaticArrayWithErrorHandling;
typedef Array<int> IntArray;
typedef ArrayWithErrorHandling<int> IntArrayWithErrorHandling;
typedef Vector<int> IntVector;
typedef VectorWithErrorHandling<int> IntVectorWithErrorHandling;

TEST_CASE("StaticArray.withErrorHandling", "[StaticArray][ArrayErrorHandling]") {
  IntStaticArray orig((int[]){1, 3, 5, 7, 9}, 5);
  IntStaticArrayWithErrorHandling a(orig);

  SECTION("without args uses same error handling") {
    REQUIRE_THROWS_AS( orig.withErrorHandling().get(5), Exception );
  }

  SECTION("with an arguments sets the error value") {
    REQUIRE( orig.withErrorHandling(-1).get(5) == -1 );
  }

  SECTION("allows configuration of an error value to return in place of an exception") {
    a.errorValue(-1);
    REQUIRE( a.get(7) == -1 );
    REQUIRE( a.get(-12) == -1 );
    REQUIRE( a[7] == -1 );
    REQUIRE( a[-12] == -1 );
  }
}

TEST_CASE("StaticArrayWithErrorHandling.errorValue()", "[ArrayErrorHandling]") {
  IntStaticArray orig;
  IntStaticArrayWithErrorHandling a(orig);

  SECTION("returns the current error value") {
    a.errorValue(-1);
    REQUIRE( a.errorValue() == -1 );
  }

  SECTION("throws an error value if none is configured") {
    REQUIRE_THROWS_AS( a.errorValue(), Exception );
  }
}

TEST_CASE("StaticArrayWithErrorHandling.errorValue(values)", "[ArrayErrorHandling]") {
  IntStaticArray orig;
  IntStaticArrayWithErrorHandling a(orig);

  SECTION("sets the error value to use in place of an exception") {
    a.errorValue(0);
    REQUIRE( a.get(5) == 0 );
  }
}

TEST_CASE("StaticArrayWithErrorHandling.resetErrorValue()", "[ArrayErrorHandling]") {
  IntStaticArray orig;
  IntStaticArrayWithErrorHandling a(orig);
  a.errorValue(-1);

  SECTION("restores exception throwing as the error behavior") {
    REQUIRE( a.hasErrorValue() );

    a.resetErrorValue();

    REQUIRE( !a.hasErrorValue() );
    REQUIRE_THROWS_AS( a.get(5), Exception );
  }
}

TEST_CASE("StaticArrayWithErrorHandling.hasErrorValue", "[ArrayErrorHandling]") {
  IntStaticArray orig;
  IntStaticArrayWithErrorHandling a(orig);

  SECTION("returns false if no error handling is configured") {
    REQUIRE( ! a.hasErrorValue() );
  }

  SECTION("returns true if error handling is configured") {
    a.errorValue(0);
    REQUIRE( a.hasErrorValue() );
  }
}

TEST_CASE("Array.withErrorHandling", "[Array][ArrayErrorHandling]") {
  IntArray orig((int[]){1, 3, 5, 7, 9, 11, 13}, 7);
  IntArrayWithErrorHandling a(orig);

  SECTION("without args uses same error handling") {
    REQUIRE_THROWS_AS( orig.withErrorHandling().get(7), Exception );
  }

  SECTION("with an arguments sets the error value") {
    REQUIRE( orig.withErrorHandling(-1).get(7) == -1 );
  }

  SECTION("allows configuration of an error value to return in place of an exception") {
    a.errorValue(-1);
    REQUIRE( a.get(7) == -1 );
    REQUIRE( a.get(-12) == -1 );
  }
}

TEST_CASE("Vector.withErrorHandling", "[Vector][ArrayErrorHandling]") {
  IntVector orig((int[]){1, 3, 5, 7, 9, 11, 13}, 7);
  IntVectorWithErrorHandling v(orig);

  SECTION("without args uses same error handling") {
    REQUIRE_THROWS_AS( orig.withErrorHandling().get(7), Exception );
  }

  SECTION("with an arguments sets the error value") {
    REQUIRE( orig.withErrorHandling(-1).get(7) == -1 );
  }

  SECTION("allows configuration of an error value to return in place of an exception") {
    IntVectorWithErrorHandling empty;
    empty.errorValue(-1);
    v.errorValue(-1);

    REQUIRE( empty.shift() == -1 );
    REQUIRE( empty.pop() == -1 );
    REQUIRE( empty.size() == 0 );

    REQUIRE( v.get(7) == -1 );
    REQUIRE( v.get(-12) == -1 );

    REQUIRE( v.remove(7) == -1 );
    REQUIRE( v.remove(-8) == -1 );
    REQUIRE( v.size() == 7 );
  }
}
