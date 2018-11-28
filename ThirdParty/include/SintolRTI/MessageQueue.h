/* -*-c++-*- SintolRTI - Copyright (C) 2009-2015 Mathias Froehlich
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

#ifndef SintolRTI_MessageQueue_h
#define SintolRTI_MessageQueue_h

#include "AbstractMessageQueue.h"
#include "Condition.h"
#include "PooledMessageList.h"
#include "Mutex.h"
#include "ScopeLock.h"

namespace SintolRTI {

// Unlocked queue implementation,
// For single threaded use.
// The timeout in the receive call is just ignored since
// single threaded use does not have any chance to fill the queue
// if that single thread is waiting for exactly that queue.
class SintolRTI_LOCAL LocalMessageQueue : public AbstractMessageQueue {
public:
  LocalMessageQueue() :
    _isClosed(false)
  { }
  virtual SharedPtr<const AbstractMessage> receive()
  { return _messageList.pop_front(); }
  virtual SharedPtr<const AbstractMessage> receive(const Clock&)
  { return _messageList.pop_front(); }
  virtual bool isOpen() const
  { return !_isClosed; }
  virtual bool empty() const
  { return _messageList.empty(); }

protected:
  virtual void append(const SharedPtr<const AbstractMessage>& message)
  { _messageList.push_back(message); }
  virtual void close()
  { _isClosed = true; }

private:
  PooledMessageList _messageList;
  bool _isClosed;
};

// Thread safe queue with condition/mutex based signaling of new messages
class SintolRTI_LOCAL ThreadMessageQueue : public AbstractMessageQueue {
public:
  ThreadMessageQueue() :
    _isClosed(false)
  { }
  virtual SharedPtr<const AbstractMessage> receive()
  {
    ScopeLock scopeLock(_mutex);
    if (_messageList.empty())
      return 0;
    return _messageList.pop_front();
  }
  virtual SharedPtr<const AbstractMessage> receive(const Clock& timeout)
  {
    ScopeLock scopeLock(_mutex);
    while (_messageList.empty()) {
      // We must not rely on the timeout return before checking the predicate.
      bool signaledOrSpurious = _condition.wait_until(scopeLock, timeout);
      if (!_messageList.empty())
        break;
      if (_isClosed)
        return 0;
      // Timeout was hit
      if (!signaledOrSpurious)
        return 0;
    }
    return _messageList.pop_front();
  }
  virtual bool isOpen() const
  {
    ScopeLock scopeLock(_mutex);
    return !_isClosed;
  }
  virtual bool empty() const
  {
    ScopeLock scopeLock(_mutex);
    return _messageList.empty();
  }

protected:
  virtual void append(const SharedPtr<const AbstractMessage>& message)
  {
    ScopeLock scopeLock(_mutex);
    bool needSignal = _messageList.empty();
    _messageList.push_back(message);
    if (needSignal)
      _condition.notify_one();
  }
  virtual void close()
  {
    ScopeLock scopeLock(_mutex);
    _isClosed = true;
    _condition.notify_one();
  }

private:
  mutable Mutex _mutex;
  Condition _condition;
  PooledMessageList _messageList;
  bool _isClosed;
};

} // namespace SintolRTI

#endif
