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

#ifndef SintolRTI_SocketServerAcceptEvent_h
#define SintolRTI_SocketServerAcceptEvent_h

#include "AbstractSocketEvent.h"
#include "SharedPtr.h"
#include "SocketServer.h"

namespace SintolRTI {

class AbstractServer;

class SintolRTI_API SocketServerAcceptEvent : public AbstractSocketEvent {
public:
  SocketServerAcceptEvent(const SharedPtr<SocketServer>& socketServer,
                          AbstractServer& abstractServer);
  virtual ~SocketServerAcceptEvent();

  virtual void read(SocketEventDispatcher& dispatcher);
  virtual bool getEnableRead() const;

  virtual void write(SocketEventDispatcher& dispatcher);
  virtual bool getEnableWrite() const;

  virtual SocketServer* getSocket() const;

private:
  SharedPtr<SocketServer> _socketServer;
  AbstractServer& _abstractServer;
};

} // namespace SintolRTI

#endif
