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

#ifndef SintolRTI_AbstractProtocolLayer_h
#define SintolRTI_AbstractProtocolLayer_h

#include "AbstractProtocolSocket.h"
#include "Referenced.h"

namespace SintolRTI {

class SintolRTI_API AbstractProtocolLayer : public Referenced {
public:
  AbstractProtocolLayer();
  virtual ~AbstractProtocolLayer();

  // Is called from the parent protocol layer when there is data to read
  virtual void read(AbstractProtocolSocket&) = 0;
  // True if the protocol is ready to recieive
  virtual bool getEnableRead() const = 0;
  // Is called from the parent protocol layer when there is space to write something
  virtual void write(AbstractProtocolSocket&) = 0;
  // True if there is something to send
  virtual bool getEnableWrite() const = 0;

  // Is called from the parent protocol layer when an unrecoverable error happenes.
  // FIXME rethink
  virtual void error(const Exception& e) = 0;

private:
  AbstractProtocolLayer(const AbstractProtocolLayer&);
  AbstractProtocolLayer& operator=(const AbstractProtocolLayer&);
};

} // namespace SintolRTI

#endif
