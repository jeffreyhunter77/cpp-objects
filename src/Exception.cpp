#include <Exception.hpp>

#include <string.h>
#include <stdlib.h>

using namespace Objects;

static const Class THIS_CLASS("Exception");

/** Constructor */
Exception::Exception(const char* message) : _message(0) {
  _message = strdup(message);
}

/** Copy constructor */
Exception::Exception(const Exception& ex) : _message(0) {
  _message = strdup(ex.message());
}

/** Destructor */
Exception::~Exception() {
  if (_message) {
    free(_message);
    _message = 0;
  }
}

/** Assignment operator */
Exception& Exception::operator=(const Exception& ex) {
  if (_message)
    free(_message);

  _message = strdup(ex.message());
  
  return *this;
}

/** Return a reference to this object's class */
const Class& Exception::classInfo() const {
  return THIS_CLASS;
}
