/* -*-c++-*- SintolRTI - Copyright (C) 2010-2012 Mathias Froehlich
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

#ifndef SintolRTI_ParenthesesReader_h
#define SintolRTI_ParenthesesReader_h

#include <iosfwd>

#include "Export.h"
#include "StringUtils.h"

namespace SintolRTI {

/// Parser for lisp like parentheses syntax files.
/// Is used to parse rti 1.3 fed files.
class SintolRTI_API ParenthesesReader {
public:
  class SintolRTI_API ContentHandler {
  public:
    virtual ~ContentHandler();

    virtual void startDocument();
    virtual void endDocument();

    virtual void startElement(const ParenthesesReader& parenthesesReader, const StringVector& tokens);
    virtual void endElement();
  };

  class SintolRTI_API ErrorHandler {
  public:
    virtual ~ErrorHandler(void);

    virtual void error(const ParenthesesReader& parenthesesReader, const char* msg);
  };

  ParenthesesReader();
  ~ParenthesesReader();

  bool parse(std::istream& stream, ContentHandler& contentHandler, ErrorHandler& errorHandler);

  unsigned getLine() const
  { return _line; }
  unsigned getColumn() const
  { return _column; }

private:
  unsigned _line;
  unsigned _column;
};

} // namespace SintolRTI

#endif
