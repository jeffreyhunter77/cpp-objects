#include <Exception.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string.h>

using namespace Objects;

TEST_CASE("Exception constructor", "[Exception]") {

  SECTION("accepts a message string") {
    Exception ex("a message");

    REQUIRE( strcmp(ex.message(), "a message") == 0 );
  }

  SECTION("copy constructor performs a deep copy") {
    Exception ex("a message");
    Exception exCopy(ex);

    REQUIRE( strcmp(exCopy.message(), ex.message()) == 0 );
    REQUIRE( exCopy.message() != ex.message() );
  }

}

TEST_CASE("Exception.operator=", "[Exception]") {
  Exception ex("an error");
  Exception exOther("another error");

  SECTION("performs a deep assignment of properties") {
    exOther = ex;

    REQUIRE( strcmp(exOther.message(), ex.message()) == 0);
    REQUIRE( exOther.message() != ex.message() );
  }
}

TEST_CASE("Exception.classInfo", "[Exception]") {
  Exception ex("a message");

  SECTION("returns the Exception class info object") {
    REQUIRE( strcmp(ex.classInfo().name(), "Exception") == 0 );
  }

}
