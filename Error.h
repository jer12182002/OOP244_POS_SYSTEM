// compilation safegaurds
#ifndef ICT_ERROR_H_
#define ICT_ERROR_H_
#include <iostream>

namespace ict {
   class Error {
      char* m_message;
   public:
   // constructors
    Error();
    Error(const char* );
    Error(const Error& ) = delete;
    
   // destructor
    virtual ~Error();
   // deleted constructor and operator=
    Error& operator=(const Error& ) = delete;
    void operator=(const char* );
   // operator= for c-style strings
    operator const char*() const;
    operator bool()const;
   // methods
    void clear();
    bool isClear()const;
    void message(const char* );
    
   // cast overloads
    friend std::ostream &operator<<(std::ostream &,const Error &);
};
   // operator << overload prototype for cout
   std::ostream &operator<<(std::ostream &, const Error  &);
   
}

#endif
