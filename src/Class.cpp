#include <Class.hpp>

#include <string.h>
#include <stdlib.h>

using namespace Objects;

static const Class THIS_CLASS("Class");

/** Constructor */
Class::Class(const char* name) : _name(0) {
  _name = strdup(name);
}

/** Destructor */
Class::~Class() {
  if (_name) {
    free(_name);
    _name = 0;
  }
}

/** Return a reference to this object's class */
const Class& Class::classInfo() const {
  return THIS_CLASS;
}
