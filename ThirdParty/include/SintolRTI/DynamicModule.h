/* -*-c++-*- SintolRTI - Copyright (C) 2013-2013 Mathias Froehlich
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

#ifndef SintolRTI_DynamicModule_h
#define SintolRTI_DynamicModule_h

#include <string>
#include "Export.h"

namespace SintolRTI {

class SintolRTI_API DynamicModule {
public:

  /// Returns the file name of the code object that contains the given address.
  /// If the system does not support this functionality or some error occurs the
  /// returned file name is empty.
  static std::string getFileNameForAddress(const void* address);

private:
  DynamicModule(const DynamicModule&);
  DynamicModule& operator=(const DynamicModule&);

  // struct PrivateData;
  // PrivateData* _privateData;
};

} // namespace SintolRTI

#endif
