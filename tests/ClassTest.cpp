#include <Class.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string.h>

using namespace Objects;

TEST_CASE("Class.name", "[Class]") {
  const char* name = "[test]";
  Class c(name);

  SECTION("returns the Class name") {
    REQUIRE( strcmp(c.name(), name) == 0 );
  }

}

TEST_CASE("Class.classInfo", "[Class]") {
  Class c("[test]");

  SECTION("returns the Class class info object") {
    REQUIRE( strcmp(c.classInfo().name(), "Class") == 0 );
  }

}
