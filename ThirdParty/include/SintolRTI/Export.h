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

#ifndef SintolRTI_Export_h
#define SintolRTI_Export_h

/// Revisit this??? FIXME
/// May be it is better to have public symbols explicitly public and
/// specify default=hidden on the compile line for the *shared* lib
/// When static this does not change anything???
/// Or does it harm when we are hidden when building a shared and a dynamic lib??
/// I believe that this is true on linux. But for win32???

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
# define SintolRTI_HELPER_DLL_IMPORT __declspec(dllimport)
# define SintolRTI_HELPER_DLL_EXPORT __declspec(dllexport)
# define SintolRTI_HELPER_DLL_LOCAL
#elif defined __GNUC__ && (4 <= __GNUC__)
# define SintolRTI_HELPER_DLL_IMPORT __attribute__ ((visibility("default")))
# define SintolRTI_HELPER_DLL_EXPORT __attribute__ ((visibility("default")))
# define SintolRTI_HELPER_DLL_LOCAL  __attribute__ ((visibility("hidden")))
#elif defined __SUNPRO_C && (0x550 <= __SUNPRO_C)
# define SintolRTI_HELPER_DLL_IMPORT __hidden
# define SintolRTI_HELPER_DLL_EXPORT __global
# define SintolRTI_HELPER_DLL_LOCAL  __hidden
#else
# define SintolRTI_HELPER_DLL_IMPORT
# define SintolRTI_HELPER_DLL_EXPORT
# define SintolRTI_HELPER_DLL_LOCAL
#endif

// Now we use the generic helper definitions above to define SintolRTI_API and SintolRTI_LOCAL.
// SintolRTI_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// SintolRTI_LOCAL is used for non-api symbols.

#ifdef SintolRTI_DLL // defined if SintolRTI is compiled as a DLL
# ifdef SintolRTI_DLL_EXPORTS // defined if we are building the SintolRTI DLL (instead of using it)
#  define SintolRTI_API SintolRTI_HELPER_DLL_EXPORT
# else
#  define SintolRTI_API SintolRTI_HELPER_DLL_IMPORT
# endif // SintolRTI_DLL_EXPORTS
# define SintolRTI_LOCAL SintolRTI_HELPER_DLL_LOCAL
#else // SintolRTI_DLL is not defined: this means SintolRTI is a static lib.
# define SintolRTI_API
# define SintolRTI_LOCAL
#endif // SintolRTI_DLL

#if defined _WIN32 && defined _MSC_VER
// disable warnings about a "dllexport" class using a regular class
# pragma warning(disable: 4251)
// the 'this is used in base ...' warning for WeakReferenced.
# pragma warning(disable: 4355)
#endif


#endif
