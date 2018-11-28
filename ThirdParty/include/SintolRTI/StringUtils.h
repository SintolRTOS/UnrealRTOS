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

#ifndef SintolRTI_StringUtils_h
#define SintolRTI_StringUtils_h

#include <algorithm>
#include <iosfwd>
#include <list>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>

#include "Export.h"
#include "VariableLengthData.h"

namespace SintolRTI {

typedef std::set<std::string> StringSet;
typedef std::list<std::string> StringList;
typedef std::vector<std::string> StringVector;
typedef std::pair<std::string, std::string> StringPair;
typedef std::list<StringPair> StringPairList;
typedef std::vector<StringPair> StringPairVector;
typedef std::map<std::string, std::string> StringMap;
typedef std::map<std::string, StringList> StringStringListMap;

inline bool contains(const StringSet& stringSet, const std::string& string)
{ return stringSet.find(string) != stringSet.end(); }
inline bool contains(const StringList& stringList, const std::string& string)
{ return std::find(stringList.begin(), stringList.end(), string) != stringList.end(); }
inline bool contains(const StringVector& stringVector, const std::string& string)
{ return std::find(stringVector.begin(), stringVector.end(), string) != stringVector.end(); }

SintolRTI_API bool
caseCompare(const std::string& s, const char* cmp);

SintolRTI_API bool
endsWith(const std::string& s, const char* tail);

/// checks for a file case insensitive extension
SintolRTI_API bool
matchExtension(const std::string& name, const char* extension);

/// Internationalization concept:
/// All internal computations are done in ucs{32,16} aka wchar_t
/// Strings are sent over the wire in utf8, that means all the indices are
/// relatively easy to compute, but transferred size is kind of small.
SintolRTI_API std::string
ucsToUtf8(const std::wstring& ucs);

SintolRTI_API std::wstring
utf8ToUcs(const std::string& utf);

SintolRTI_API std::wstring
utf8ToUcs(const char* utf);

SintolRTI_API std::wstring
localeToUcs(const char* loc);

inline std::wstring localeToUcs(const std::string& loc)
{ return localeToUcs(loc.c_str()); }

SintolRTI_API std::string
ucsToLocale(const std::wstring& ucs);

inline std::string localeToUtf8(const std::string& locale)
{ return ucsToUtf8(localeToUcs(locale)); }

inline std::string localeToUtf8(const char* locale)
{ return ucsToUtf8(localeToUcs(locale)); }

inline std::string utf8ToLocale(const std::string& utf)
{ return ucsToLocale(utf8ToUcs(utf)); }

inline std::string utf8ToLocale(const char* utf)
{ return ucsToLocale(utf8ToUcs(utf)); }

SintolRTI_API std::string
asciiToUtf8(const char* ascii);

SintolRTI_API VariableLengthData
utf8ToUtf16BE(const std::string& utf8, bool bom = false);

SintolRTI_API std::vector<std::string>
split(const std::string& s, const char* c = ", \t\n");

inline std::vector<std::string>
split(const char* s, const char* c = ", \t\n")
{
  if (!s)
    return std::vector<std::string>();
  return split(std::string(s), c);
}

SintolRTI_API std::string
trim(std::string s, const char* c = " \t\n");

inline std::string
trim(const char* s, const char* c = " \t\n")
{
  if (!s)
    return std::string();
  return trim(std::string(s), c);
}

SintolRTI_API std::string
fqClassName(const StringVector& name);

inline std::string
classNamePart(const StringVector& name)
{
  if (name.empty())
    return std::string();
  return name.back();
}

inline std::string
classNamePart(const std::string& name)
{
  return classNamePart(split(name, "."));
}

SintolRTI_API std::pair<std::string, std::string>
parseInetAddress(const std::string& address);

SintolRTI_API std::string
getFilePart(const std::string& path);

SintolRTI_API std::string
getBasePart(const std::string& path);

inline std::ostream&
operator<<(std::ostream& stream, const std::wstring& s)
{ return stream << ucsToLocale(s); }

} // namespace SintolRTI

#endif
