/* -*-c++-*- SintolRTI - Copyright (C) 2009-2015 Mathias Froehlich
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

#ifndef SintolRTI_MessageEncodingRegistry_h
#define SintolRTI_MessageEncodingRegistry_h

#include "AbstractMessageEncoding.h"
#include "SocketStream.h"
#include "StringUtils.h"

// Have a central place where define the currently only supported protocol version
#define SintolRTI_ENCODING_VERSION "8"
// Define this if we want to are in the development phase and the protocol
// is expected to change without further notice! This message is printed on each connect happening then!
// #define SintolRTI_ENCODING_DEVELOPMENT_WARNING \
// "Using development message encoding!\nMessage encoding compatibility is not enforced by SintolRTI!"

namespace SintolRTI {

class Clock;
class ServerOptions;

/// MessageEncodingRegistry
///
/// Holds all the encodings we know about.
/// On connect, the client sends a message that tells something about
/// The encoding capabilities of the client. The server takes this initial
/// packet and responds with a respons of the same message encoding.
/// This response contains the selected encoding.
/// The packet format is a big endian/utf8 combination that should never change
/// and for SintolRTI messages. It contains a string map of string lists that can contain
/// any data we will need in the future to select the appropriate encoders.
///
/// At least this contains the version, endianess of the participants and the
/// supported stream encoding keys in preference order. The server compares these encodings
/// with its own available encodings and with some to be implemented policy about compression
/// and such. The server selects the used encoding and sends that back to the client.
/// The next data that is exchanged needs to happen in the selected encoding.
///
class SintolRTI_API MessageEncodingRegistry {
public:
  /// Return an encoder for a given encoding name
  SharedPtr<AbstractMessageEncoding> getEncoding(const std::string& encodingName) const;
  /// Return the list of supported encodings known to the registry.
  StringList getEncodings() const;
  /// Return the common subset of encodings from the encodingList and the ones known to the registry.
  StringList getCommonEncodings(const StringList& encodingList) const;

  /// FIXME: move this away from a singlton to something that belongs to a NetworkServer.
  /// Then just have there those encodings that we want to use in this NetworkServer instance.
  static const MessageEncodingRegistry& instance();

private:
  MessageEncodingRegistry();
  ~MessageEncodingRegistry();
};

} // namespace SintolRTI

#endif
