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

#ifndef SintolRTI_NestedProtocolLayer_h
#define SintolRTI_NestedProtocolLayer_h

#include "AbstractProtocolLayer.h"

namespace SintolRTI {

/// base class for all protocol layers that have a non leaf protocol layer behaviour
class SintolRTI_API NestedProtocolLayer : public AbstractProtocolLayer {
public:
  NestedProtocolLayer();
  virtual ~NestedProtocolLayer();

  // Is called from the parent protocol layer when there is data to read
  virtual void read(AbstractProtocolSocket&) = 0;
  virtual bool getEnableRead() const = 0;
  // Is called from the parent protocol layer when there is space to write something
  virtual void write(AbstractProtocolSocket&) = 0;
  virtual bool getEnableWrite() const = 0;

  virtual void error(const Exception& e) = 0;

  void setProtocolLayer(const SharedPtr<AbstractProtocolLayer>& protocolLayer)
  { _protocolLayer = protocolLayer; }
  const SharedPtr<AbstractProtocolLayer>& getProtocolLayer() const
  { return _protocolLayer; }

private:
  SharedPtr<AbstractProtocolLayer> _protocolLayer;
};

} // namespace SintolRTI

#endif
