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

#ifndef SintolRTI_RangeBounds_h
#define SintolRTI_RangeBounds_h

#include <limits>
#include "Message.h"
#include "Types.h"

namespace SintolRTI {

class SintolRTI_LOCAL RangeBounds : public RangeBoundsValue {
public:
  /// Note that the upper bound does not belong to the range.
  /// It is [lower, upper)
  RangeBounds()
  {
    setLowerBound(std::numeric_limits<Unsigned>::max());
    setUpperBound(std::numeric_limits<Unsigned>::min());
  }
  RangeBounds(const Unsigned& lower, const Unsigned& upper)
  {
    setLowerBound(lower);
    setUpperBound(upper);
  }
  RangeBounds(const RangeBoundsValue& rangeBoundsValue) :
    RangeBoundsValue(rangeBoundsValue)
  {
  }

  bool empty() const
  { return getUpperBound() <= getLowerBound(); }

  bool whole() const
  { return getLowerBound() == std::numeric_limits<Unsigned>::min() && getUpperBound() == std::numeric_limits<Unsigned>::max(); }

  Unsigned getCenter() const
  { return (getUpperBound() >> 1) + (getLowerBound() >> 1); }

  bool intersects(const RangeBounds& rangeBounds) const
  { return getLowerBound() < rangeBounds.getUpperBound() && rangeBounds.getLowerBound() < getUpperBound(); }

  bool includes(const RangeBounds& rangeBounds) const
  {
    if (empty())
      return false;
    return getLowerBound() <= rangeBounds.getLowerBound() && rangeBounds.getUpperBound() <= getUpperBound();
  }

  void extend(const RangeBounds& rangeBounds)
  {
    setLowerBound(std::min(getLowerBound(), rangeBounds.getLowerBound()));
    setUpperBound(std::max(getUpperBound(), rangeBounds.getUpperBound()));
  }
};

} // namespace SintolRTI

#endif
