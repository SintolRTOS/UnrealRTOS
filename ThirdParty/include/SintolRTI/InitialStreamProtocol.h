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

#ifndef SintolRTI_InitialStreamProtocol_h
#define SintolRTI_InitialStreamProtocol_h

#include "Buffer.h"
#include "StreamBufferProtocol.h"
#include "StringUtils.h"

namespace SintolRTI {

class SintolRTI_API InitialStreamProtocol : public StreamBufferProtocol {
public:
  InitialStreamProtocol();
  virtual ~InitialStreamProtocol();

  virtual void readOptionMap(const StringStringListMap& stringStringListMap) = 0;
  void writeOptionMap(const StringStringListMap& stringStringListMap);

  virtual void readPacket(const Buffer& buffer);
  virtual void writePacket();
  virtual bool getMoreToSend() const;

  virtual void read(AbstractProtocolSocket& protocolSocket);
  virtual bool getEnableRead() const;

  virtual void write(AbstractProtocolSocket& protocolSocket);
  virtual bool getEnableWrite() const;

  virtual void error(const Exception& e);

protected:
  void setFollowupProtocol(const SharedPtr<AbstractProtocolLayer>& followupProtocol);

private:
  void activateFollowupProtocol(AbstractProtocolSocket& protocolSocket);

  class DecodeStream;
  class EncodeStream;

  // Once negotiated, this should be set.
  SharedPtr<AbstractProtocolLayer> _followupProtocol;
};

} // namespace SintolRTI

#endif
