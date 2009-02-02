/**
 *  $Id$
 *  
 *  Copyright (C) 2009
 *  Troy D. Straszheim  <troy@icecube.umd.edu>
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
#include <fstream>
#include <resophonic/kamasu/logging.hpp>

namespace resophonic {
  namespace kamasu {

    namespace {
      struct start_message {
	bool start;
	start_message() : start(true) { }
      };
    }

    std::ofstream& ofs() 
    {
      static start_message sm;
      static std::ofstream ofs_("kamasu.log", std::ios::app);

      if (sm.start)
	{
	  sm.start = false;
	  ofs_ << "*****************************************************************\n"
	       << "*****************************************************************\n"
	       << "*****************************************************************\n";
	}

      return ofs_;
    }

  }
}
