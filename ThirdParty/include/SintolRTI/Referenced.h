/* -*-c++-*- SintolRTI - Copyright (C) 2004-2014 Mathias Froehlich
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

#ifndef SintolRTI_Referenced_h
#define SintolRTI_Referenced_h

#include "Export.h"
#include "SintolRTIConfig.h"
#include "Atomic.h"

namespace SintolRTI {

class SintolRTI_API Referenced {
public:
  Referenced(void) : _refcount(0u)
  {}
  /// Do not copy reference counts. Each new object has it's own counter
  Referenced(const Referenced&) : _refcount(0u)
  {}
  /// Do not copy reference counts. Each new object has it's own counter
  Referenced& operator=(const Referenced&)
  { return *this; }

  static void get(const Referenced* ref)
  { if (!ref) return; ref->_refcount.incFetch(Atomic::MemoryOrderRelease); }
  static void getFirst(const Referenced* ref)
  { get(ref); }
  static unsigned put(const Referenced* ref)
  { if (ref) return ref->_refcount.decFetch(Atomic::MemoryOrderAcqRel); else return ~0u; }
  static void release(const Referenced* ref)
  { if (!ref) return; ref->_refcount.decFetch(Atomic::MemoryOrderRelease); }
  static unsigned count(const Referenced* ref)
  { if (ref) return ref->_refcount; else return 0u; }
  static bool shared(const Referenced* ref)
  { if (ref) return 1u < ref->_refcount; else return false; }

  template<typename T>
  static void destruct(T* ref)
  { delete ref; }

private:
  mutable Atomic _refcount;
};

} // namespace SintolRTI

#endif
