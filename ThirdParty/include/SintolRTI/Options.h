/* -*-c++-*- SintolRTI - Copyright (C) 2009-2012 Mathias Froehlich 
 *
 * This file is part of SintolRTI.
 *
 * SintolRTI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * SintolRTI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with SintolRTI.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef SintolRTI_Options_h
#define SintolRTI_Options_h

#include <string>
#include <vector>
#include "Export.h"

namespace SintolRTI {

// Simple portable getopt rplacement.
class SintolRTI_API Options {
public:
  Options(int argc, const char* const argv[]);
  ~Options();

  // The current options character
  char getOptChar() const
  { return _optChar; }

  // The current option argument, if the option character is != 0
  // A usual non option argument if the option character is == 0
  const std::string& getArgument() const
  { return _argument; }

  // Returns true as long as there are options to process.
  // Takes the current list of arguments on getopt style
  bool next(const char *opts);
  
private:
  int _argc;
  const char* const* _argv;
  std::string _argument;
  unsigned _optCharIndex;
  int _optIndex;
  char _optChar;
};

};

#endif
