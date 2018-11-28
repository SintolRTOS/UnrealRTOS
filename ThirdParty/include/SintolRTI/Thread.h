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

#ifndef SintolRTI_Thread_h
#define SintolRTI_Thread_h

#include "Export.h"
#include "SharedPtr.h"
#include "WeakReferenced.h"

namespace SintolRTI {

class SintolRTI_API Thread : public WeakReferenced {
public:
  Thread(void);

  static void destruct(Thread* thread);

  bool start();
  void wait();

protected:
  virtual ~Thread(void);

  virtual void run() = 0;

private:
  Thread(const Thread&);
  Thread& operator=(const Thread&);

  struct PrivateData;
  PrivateData* _privateData;
};

} // namespace SintolRTI

#endif
