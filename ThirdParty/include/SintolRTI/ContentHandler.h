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

#ifndef SintolRTI_XML_ContentHandler_h
#define SintolRTI_XML_ContentHandler_h

#include "Referenced.h"

namespace SintolRTI {
namespace XML {

class Attributes;

class SintolRTI_API ContentHandler : public Referenced {
public:
  virtual ~ContentHandler(void);

  virtual void characters(const char* data, unsigned length);
/*   virtual void ignorableWhitespace(const char* data, unsigned length); */

  virtual void comment(const char* commentData, unsigned length);

  virtual void startDocument(void);
  virtual void endDocument(void);

  virtual void startElement(const char* uri, const char* localName,
                            const char* qName, const Attributes* atts);
  virtual void endElement(const char* uri, const char* localName,
                          const char* qName);

  virtual void skippedEntity(const char* name);
  virtual void processingInstruction(const char* target, const char* data);

//   virtual void startPrefixMapping(const char* prefix, const char* uri);
//   virtual void endPrefixMapping(const char* prefix);

//   virtual void setDocumentLocator(Locator locator);
};

} // namespace XML
} // namespace SintolRTI

#endif
