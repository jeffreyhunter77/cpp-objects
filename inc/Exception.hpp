#ifndef __included_Objects_Exception_hpp__
#define __included_Objects_Exception_hpp__

#include <Object.hpp>
#include <Class.hpp>

namespace Objects {

  class Exception : public Object {
  public:
    Exception(const char* message);
    Exception(const Exception& ex);
    ~Exception();

    const char* message() const { return _message; }

    Exception& operator=(const Exception& ex);

    const Class& classInfo() const;

  private:
    char* _message;
  };

};

#endif // __included_Objects_Exception_hpp__
