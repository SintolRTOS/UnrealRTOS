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

#ifndef SintolRTI_ZLibProtocolLayer_h
#define SintolRTI_ZLibProtocolLayer_h

#include "NestedProtocolLayer.h"

namespace SintolRTI {

#ifdef SintolRTI_HAVE_ZLIB
class SintolRTI_API ZLibProtocolLayer : public NestedProtocolLayer {
public:
  ZLibProtocolLayer();
  virtual ~ZLibProtocolLayer();

  // Is called from the parent protocol layer when there is data to read
  virtual void read(AbstractProtocolSocket& protocolSocket);
  virtual bool getEnableRead() const;
  // Is called from the parent protocol layer when there is space to write something
  virtual void write(AbstractProtocolSocket& protocolSocket);
  virtual bool getEnableWrite() const;

  virtual void error(const Exception& e);

private:
  class ProtocolSocket;
  ProtocolSocket* _protocolSocket;
};
#endif

} // namespace SintolRTI

#endif
