/* -*-c++-*- SintolRTI - Copyright (C) 2004-2012 Mathias Froehlich 
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

#ifndef SintolRTI_XML_ErrorHandler_h
#define SintolRTI_XML_ErrorHandler_h

#include "Referenced.h"

namespace SintolRTI {
namespace XML {

class ErrorHandler : public Referenced {
public:
  virtual ~ErrorHandler(void);
  virtual void error(const char* msg, unsigned line, unsigned col);
  virtual void fatalError(const char* msg, unsigned line, unsigned col);
  virtual void warning(const char* msg, unsigned line, unsigned col);
};

} // namespace XML
} // namespace SintolRTI

#endif
