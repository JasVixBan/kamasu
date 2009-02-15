#ifndef RESOPHONIC_KAMASU_EXCEPTION_HPP_INCLUDED
#define RESOPHONIC_KAMASU_EXCEPTION_HPP_INCLUDED

#include <exception>
#include <cassert>

namespace resophonic {
  namespace kamasu {

    struct bad_index : virtual std::exception
    {
      bad_index() { }

      virtual const char* what() const throw()
      {
	return "resophonic::kamasu error: bad index";
      }
    };
  }
}

#endif
