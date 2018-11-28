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

#ifndef SintolRTI_AbstractProtocolSocket_h
#define SintolRTI_AbstractProtocolSocket_h

#include "Buffer.h"
#include "SharedPtr.h"

namespace SintolRTI {

class AbstractProtocolLayer;

class SintolRTI_API AbstractProtocolSocket {
public:
  AbstractProtocolSocket();
  virtual ~AbstractProtocolSocket();

  /// Can be called from the consuming layer to receive ready to read data
  virtual ssize_t recv(const BufferRange& bufferRange, bool peek) = 0;

  /// Can be called from the consuming layer to send something into this protocol layer
  virtual ssize_t send(const ConstBufferRange& bufferRange, bool more) = 0;

  /// Call when the user wants to close this socket.
  /// Closing a socket means:
  /// * We can no longer write anything,
  /// * Pending writes are flushed.
  /// * Reads are just discarded.
  virtual void close() = 0;

  // FIXME rethink
  virtual void replaceProtocol(const SharedPtr<AbstractProtocolLayer>& protocolLayer) = 0;
};

} // namespace SintolRTI

#endif
