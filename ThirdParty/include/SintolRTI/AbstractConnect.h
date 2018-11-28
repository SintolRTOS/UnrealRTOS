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

#ifndef SintolRTI_AbstractConnect_h
#define SintolRTI_AbstractConnect_h

#include "AbstractMessage.h"
#include "AbstractMessageSender.h"
#include "AbstractMessageReceiver.h"
#include "Clock.h"
#include "SharedPtr.h"

namespace SintolRTI {

class Clock;

class SintolRTI_API AbstractConnect : public Referenced {
public:
  virtual ~AbstractConnect() {}
  virtual AbstractMessageSender* getMessageSender() = 0;
  virtual AbstractMessageReceiver* getMessageReceiver() = 0;

  /// Convenience methods for obvious tasks
  void send(const SharedPtr<const AbstractMessage>& message)
  { getMessageSender()->send(message); }

  /// Returns the next message. Returns 0 if no new message arrives before abstime
  SharedPtr<const AbstractMessage> receive(const Clock& abstime)
  { return getMessageReceiver()->receive(abstime); }
  /// Returns the next message if there is one.
  SharedPtr<const AbstractMessage> receive()
  { return getMessageReceiver()->receive(); }

  /// Close the message sender
  void close()
  { getMessageSender()->close(); }

  /// Return true if there is something ready to receive
  bool empty()
  { return getMessageReceiver()->empty(); }
};

} // namespace SintolRTI

#endif
