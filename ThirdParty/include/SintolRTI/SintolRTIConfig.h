/* -*-c++-*- SintolRTI - Copyright (C) 2004-2014 Mathias Froehlich
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

#ifndef SintolRTI_SintolRTIConfig_h
#define SintolRTI_SintolRTIConfig_h

#define SintolRTI_VERSION_STRING "1.0"

// Defaults for server connects
#define SintolRTI_DEFAULT_HOST_STRING "localhost"
// Just a free port from my /etc/services ...
#define SintolRTI_DEFAULT_PORT_STRING "14321"
#define SintolRTI_DEFAULT_PIPE_PATH ".SintolRTI"

#define SintolRTI_VERSION_CHECK(REQ_MAJ, REQ_MIN, AVAIL_MAJ, AVAIL_MIN) \
  ((((REQ_MAJ) == (AVAIL_MAJ)) && ((REQ_MIN) <= (AVAIL_MIN))) || ((REQ_MAJ) < (AVAIL_MAJ)))

#if defined(__GNUC__) && (((4 <= __GNUC__) && (1 <= __GNUC_MINOR__)) || (5 <= __GNUC__))
#define SintolRTI_DEPRECATED __attribute__ ((deprecated))
#else
#define SintolRTI_DEPRECATED
#endif

#if 201103L <= __cplusplus
// In any case this is the best choice as this provides a reliable api for any future
# define SintolRTI_ATOMIC_USE_STD_ATOMIC
#else
# if defined(__GNUC__) && SintolRTI_VERSION_CHECK(4, 7, __GNUC__, __GNUC_MINOR__)
// No need to include something. Is a Compiler API ...
#  define SintolRTI_ATOMIC_USE_GCC47_BUILTINS
# elif defined(__clang__) && SintolRTI_VERSION_CHECK(3, 3, __clang_major__, __clang_minor__)
// No need to include something. Is a Compiler API. Note that clang aims to be gcc compatible ...
#  define SintolRTI_ATOMIC_USE_GCC47_BUILTINS
# elif defined _WIN32
// Neat old Win32 functions
#  define SintolRTI_ATOMIC_USE_WIN32_INTERLOCKED
# elif defined(__GNUC__) && SintolRTI_VERSION_CHECK(4, 1, __GNUC__, __GNUC_MINOR__) && defined(__x86_64__)
// No need to include something. Is a Compiler API ...
#  define SintolRTI_ATOMIC_USE_GCC4_BUILTINS
# elif defined(__GNUC__) && defined(__i386)
#  define SintolRTI_ATOMIC_USE_GCC_ASM
# elif defined(__sgi) && defined(_COMPILER_VERSION) && (_COMPILER_VERSION>=730)
// No need to include something. Is a Compiler API ...
#  define SintolRTI_ATOMIC_USE_MIPSPRO_BUILTINS
// FIXME
// #elif defined(__sun)
// # define SintolRTI_ATOMIC_USE_SUN
# elif defined(__APPLE__)
#  define SintolRTI_ATOMIC_USE_BSD
# else
// The sledge hammer ...
#  define SintolRTI_ATOMIC_USE_MUTEX
# endif
#endif

/* #undef SintolRTI_HAVE_CSTDINT */
#define SintolRTI_HAVE_STDINT_H
#define SintolRTI_HAVE_INTTYPES_H

/* #undef SintolRTI_HOST_IS_BIG_ENDIAN */
#define SintolRTI_HOST_IS_LITTLE_ENDIAN

/* #undef SintolRTI_HAVE_ALLOCA */
/* #undef SintolRTI_HAVE_DLADDR */
#define SintolRTI_DATAROOTDIR "D:/SintolRTOS/SintolRTOS/build/share/SintolRTI"

#endif
