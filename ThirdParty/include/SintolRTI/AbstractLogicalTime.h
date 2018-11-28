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

#ifndef SintolRTI_AbstractLogicalTime_h
#define SintolRTI_AbstractLogicalTime_h

#include "Referenced.h"

namespace SintolRTI {

class AbstractLogicalTime : public Referenced {
public:
  virtual ~AbstractLogicalTime() {}
  virtual bool operator<(const AbstractLogicalTime& logicalTime) const = 0;
};

} // namespace SintolRTI

#endif
