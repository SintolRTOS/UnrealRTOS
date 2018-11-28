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

#ifndef SintolRTI_ThreadLocal_h
#define SintolRTI_ThreadLocal_h

#include "Export.h"

namespace SintolRTI {

class SintolRTI_API AbstractThreadLocal {
protected:
  AbstractThreadLocal();
  ~AbstractThreadLocal();

  struct SintolRTI_API _AbstractData {
    virtual ~_AbstractData();
  };

  _AbstractData* _get();
  void _set(_AbstractData*);

private:
  AbstractThreadLocal(const AbstractThreadLocal&);
  AbstractThreadLocal& operator=(const AbstractThreadLocal&);

  struct _Provider;

  unsigned _index;
};

template<typename T>
class SintolRTI_API ThreadLocal : public AbstractThreadLocal {
public:
  T* instance()
  {
    _Data* value;
    value = static_cast<_Data*>(_get());
    if (!value) {
      value = new _Data();
      _set(value);
    }
    return &value->_value;
  }
private:
  struct _Data : public _AbstractData {
    T _value;
  };
};

} // namespace SintolRTI

#endif
