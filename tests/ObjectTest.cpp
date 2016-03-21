#include <Object.hpp>
#include <Class.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string.h>

using namespace Objects;

TEST_CASE("Object.classInfo", "[Object]") {
  Object o;

  SECTION("returns the Object class info object") {
    REQUIRE( strcmp(o.classInfo().name(), "Object") == 0 );
  }

}
