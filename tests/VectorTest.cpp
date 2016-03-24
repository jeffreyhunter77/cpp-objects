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

}

TEST_CASE("Vector.classInfo", "[Vector]") {
  IntVector v;

  SECTION("returns the Vector class info object") {
    REQUIRE( strcmp(v.classInfo().name(), "Vector") == 0 );
  }

}
