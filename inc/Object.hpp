#ifndef __included_Objects_Object_hpp__
#define __included_Objects_Object_hpp__

namespace Objects {

  class Class;

  class Object {
  public:
    virtual ~Object();
    virtual const Class& classInfo() const;
  };

};

#endif // __included_Objects_Object_hpp__
