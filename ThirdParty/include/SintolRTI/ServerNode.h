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

#ifndef SintolRTI_ServerNode_h
#define SintolRTI_ServerNode_h

#include <string>
#include "AbstractMessageSender.h"
#include "AbstractServerNode.h"
#include "Referenced.h"
#include "SharedPtr.h"
#include "StringUtils.h"

namespace SintolRTI {

class ConnectHandle;
class ServerMessageDispatcher;
class ServerOptions;

class SintolRTI_LOCAL ServerNode : public AbstractServerNode {
public:
  ServerNode();
  virtual ~ServerNode();

  const std::string& getServerName() const;
  void setServerName(const std::string& name);

  /// Returns true if the server is idle.
  /// Whare idle means that it is save to shut down the server completely.
  /// This is false for any root server or, for a child server that has child connects.
  virtual bool isIdle() const;

  /// Hmm, make that more callback based during connection setup, but for now ...
  virtual ServerOptions& getServerOptions();
  virtual const ServerOptions& getServerOptions() const;

  virtual ConnectHandle _insertConnect(const SharedPtr<AbstractMessageSender>& messageSender, const StringStringListMap& clientOptions);
  virtual ConnectHandle _insertParentConnect(const SharedPtr<AbstractMessageSender>& messageSender, const StringStringListMap& parentOptions);
  virtual void _eraseConnect(const ConnectHandle& connectHandle);
  virtual void _dispatchMessage(const AbstractMessage* message, const ConnectHandle& connectHandle);

private:
  ServerNode(const ServerNode&);
  ServerNode& operator=(const ServerNode&);

  ServerMessageDispatcher* _serverMessageDispatcher;
};

} // namespace SintolRTI

#endif
