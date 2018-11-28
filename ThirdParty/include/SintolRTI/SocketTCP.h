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

#ifndef SintolRTI_SocketTCP_h
#define SintolRTI_SocketTCP_h

#include "SocketAddress.h"
#include "SocketStream.h"

namespace SintolRTI {

class SocketServerTCP;

class SintolRTI_API SocketTCP : public SocketStream {
public:
  SocketTCP();

  void connect(const SocketAddress& address);
  virtual void cork(bool enable);
  virtual void shutdown();

protected:
  SocketTCP(PrivateData* privateData);
  virtual ~SocketTCP();

  friend class SocketServerTCP;
};

} // namespace SintolRTI

#endif
