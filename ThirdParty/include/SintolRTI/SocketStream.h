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

#ifndef SintolRTI_SocketStream_h
#define SintolRTI_SocketStream_h

#include "Buffer.h"
#include "SocketData.h"

namespace SintolRTI {

class SocketAddress;
class SocketServer;

/// Desired error semantics:
/// send:
///  returns 0 on 'please try again'
///  returns -1 on 'message too big'
///  throws an exception on any 'serious' error
/// recv:
///  returns 0 on EOF
///  returns -1 on 'please try again'
///  throws an exception on any 'serious' error
/// Note that this is inconsistent but close to what the bare posix stuff
/// does with error numbers. So, when reusing the usual method names, also
/// reuse their semantics as much as possible.

class SintolRTI_API SocketStream : public SocketData {
public:

  ssize_t send(const ConstBufferRange& bufferRange, bool more);
  ssize_t recv(const BufferRange& bufferRange, bool peek);
  virtual void cork(bool enable);
  virtual void shutdown();

  SocketAddress getpeername() const;

protected:
  SocketStream(PrivateData* privateData);
  virtual ~SocketStream();

  friend class SocketServer;
};

} // namespace SintolRTI

#endif
