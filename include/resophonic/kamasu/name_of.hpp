/**
 *  $Id$
 *  
 *  Copyright (C) 2007
 *  Troy D. Straszheim  <troy@resophonic.com>
 *  
 *  This file is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 *  
 */

#ifndef RESOPHONIC_NAME_OF_H_INCLUDED
#define RESOPHONIC_NAME_OF_H_INCLUDED

#include <cxxabi.h>
#include <string>
#include <stdlib.h>

namespace resophonic {

  // takes a typename an returns a (hopefully) identical string.  Note
  // name_of<string>() returns "std::string"...

  template <typename T>
  struct reference_to
  { };

  template <typename T>
  struct name_of_impl
  {
    const std::type_info& operator()() {
      return typeid(T);
    }
  };

  template <typename T>
  struct name_of_impl<T&>
  {
    const std::type_info& operator()() 
    {
      return typeid(reference_to<T>);
    }
  };

  template <typename T>
  inline static std::string name_of()
  {
    int status;
    char *realname;
    std::string to_return;
    const static char *const notavailable = "N/A";
    const std::type_info &ti = typeid(T); //name_of_impl<T>()();
    const char* mangled = ti.name();
    if (!mangled)
       to_return = notavailable;
    else
    {
      realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);
      if (realname)
      {
        to_return = realname;
        free(realname);
      }
      else
        to_return = notavailable;
    }
    return to_return;
  }

  template <typename T>
  inline static std::string name_of(T &t)
  {
    int status;
    char *realname;
    std::string to_return;
    const static char *const notavailable = "N/A";
    const std::type_info &ti = typeid(T);
    const char* mangled = ti.name();
    if (!mangled)
       to_return = notavailable;
    else
    {
      realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);
      if (realname)
      {
        to_return = realname;
        free(realname);
      }
      else
        to_return = notavailable;
    }
    return to_return;
  }

  template <typename T>
  inline static std::string name_of(const T &t)
  {
    int status;
    char *realname;
    std::string to_return;
    const static char *const notavailable = "N/A";
    const std::type_info &ti = typeid(T);
    const char* mangled = ti.name();
    if (!mangled)
       to_return = notavailable;
    else
    {
      realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);
      if (realname)
      {
        to_return = realname;
        free(realname);
      }
      else
        to_return = notavailable;
    }
    return to_return;
  }

  inline static std::string name_of(const std::type_info &ti)
  {
    int status;
    char *realname;
    std::string to_return;

    realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);
    to_return = realname;
    free(realname);
    return to_return;
  }

}
#endif
