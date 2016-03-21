#ifndef __included_Objects_Class_hpp__
#define __included_Objects_Class_hpp__

#include <Object.hpp>

namespace Objects {

  class Class : public Object {
  public:
    Class(const char* name);
    ~Class();

    const char* name() const { return _name; }
    const Class& classInfo() const;

  private:
    Class(Class& c) : _name(0) { /* not allowed */ }

    char* _name;
  };

};

#endif // __included_Objects_Class_hpp__
