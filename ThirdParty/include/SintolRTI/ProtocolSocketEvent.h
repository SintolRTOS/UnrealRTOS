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

#ifndef SintolRTI_ProtocolSocketEvent_h
#define SintolRTI_ProtocolSocketEvent_h

#include "AbstractSocketEvent.h"
#include "SharedPtr.h"
#include "SocketStream.h"

namespace SintolRTI {

class AbstractProtocolLayer;

/// This is the top level protocol layer that just puts data into the actual operating system socket
/// In a next step this shouold just become the top level socket dispatcher event.
class SintolRTI_API ProtocolSocketEvent : public AbstractSocketEvent {
public:
  ProtocolSocketEvent(const SharedPtr<SocketStream>& socketStream);
  virtual ~ProtocolSocketEvent();

  // Is called from the parent protocol layer when there is data to read
  virtual void read(SocketEventDispatcher& dispatcher);
  virtual bool getEnableRead() const;

  // Is called from the parent protocol layer when there is space to write something
  virtual void write(SocketEventDispatcher& dispatcher);
  virtual bool getEnableWrite() const;

  virtual void error(const Exception& e);

  virtual SocketStream* getSocket() const;

  void setProtocolLayer(const SharedPtr<AbstractProtocolLayer>& protocolLayer);
  const SharedPtr<AbstractProtocolLayer>& getProtocolLayer() const;

private:
  ProtocolSocketEvent(const ProtocolSocketEvent&);
  ProtocolSocketEvent& operator=(ProtocolSocketEvent&);

  struct ProtocolSocket;
  ProtocolSocket* _protocolSocket;
};

} // namespace SintolRTI

#endif
