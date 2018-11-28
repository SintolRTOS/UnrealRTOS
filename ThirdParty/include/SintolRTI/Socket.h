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

#ifndef SintolRTI_Socket_h
#define SintolRTI_Socket_h

#include "Export.h"
#include "Referenced.h"

namespace SintolRTI {

class SocketEventDispatcher;

class SintolRTI_API Socket : public Referenced {
public:
  static void destruct(Socket* socket);

  bool isOpen() const;
  virtual void close();

  // Sigh, a strange access problem on aCC and early gcc, just disable that control here
#if !defined(__hpux) && !(defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 1)))
protected:
#endif
  struct PrivateData;
  PrivateData* _privateData;

  Socket(PrivateData* privateData);
  virtual ~Socket();

private:
  Socket(const Socket &sock);
  void operator=(const Socket &sock);

  friend class SocketEventDispatcher;
};

} // namespace SintolRTI

#endif
