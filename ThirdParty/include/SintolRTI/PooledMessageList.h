/* -*-c++-*- SintolRTI - Copyright (C) 2009-2013 Mathias Froehlich
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

#ifndef SintolRTI_PooledMessageList_h
#define SintolRTI_PooledMessageList_h

#include <list>
#include "AbstractMessage.h"

namespace SintolRTI {

class SintolRTI_API PooledMessageList {
public:
  bool empty() const
  { return _list.empty(); }
  void push_back(const SharedPtr<const AbstractMessage>& message)
  {
    // Take the list entry from the pool if possible
    if (_pool.empty()) {
      _list.push_back(message);
    } else {
      _list.splice(_list.end(), _pool, _pool.begin());
      _list.back() = message;
    }
  }
  SharedPtr<const AbstractMessage> pop_front()
  {
    if (_list.empty())
      return 0;
    // take away the front message and move the empty list entry to the pool.
    SharedPtr<const AbstractMessage> message;
    message.swap(_list.front());
    _pool.splice(_pool.begin(), _list, _list.begin());
    return message;
  }

private:
  typedef std::list<SharedPtr<const AbstractMessage> > List;
  List _list;
  List _pool;
};

} // namespace SintolRTI

#endif
