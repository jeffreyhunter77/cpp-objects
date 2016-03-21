#include <Object.hpp>
#include <Class.hpp>

using namespace Objects;

static const Class THIS_CLASS("Object");

/** Destructor */
Object::~Object() {
}

/** Return a reference to this object's class */
const Class& Object::classInfo() const {
  return THIS_CLASS;
}
