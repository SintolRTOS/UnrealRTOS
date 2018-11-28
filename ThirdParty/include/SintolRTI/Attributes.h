/* -*-c++-*- SintolRTI - Copyright (C) 2004-2012 Mathias Froehlich 
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

#ifndef SintolRTI_XML_Attributes_h
#define SintolRTI_XML_Attributes_h

namespace SintolRTI {
namespace XML {

enum Type {
  CDATA,
  ID,
  IDREF,
  IDREFS,
  NMTOKEN,
  NMTOKENS,
  ENTITY,
  ENTITIES,
  NOTATION
};

class Attributes {
public:
  virtual ~Attributes(void);

  virtual int getIndex(const char* qName) const = 0;
//   virtual int getIndex(const char* uri, const char* localName) = 0;
  virtual int getLength(void) const = 0;
  virtual const char* getLocalName(int index) const = 0;
//   virtual const char* getQName(int index) const = 0;
  virtual Type getType(int index) const = 0;
  virtual Type getType(const char* qName) const = 0;
//   virtual Type getType(const char* uri, const char* localName) const = 0;
//   virtual const char* getURI(int index) const = 0;
  virtual const char* getValue(int index) const = 0;
  virtual const char* getValue(const char* qName) const = 0;
//   virtual const char* getValue(const char* uri, const char* localName) const = 0;
};

} // namespace XML
} // namespace SintolRTI

#endif
