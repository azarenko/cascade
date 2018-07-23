/*
 * debug.h
 *
 * (C) Copyright 2014 Ulrich Hecht
 *
 * This file is part of CASCADE.  CASCADE is almost free software; you can
 * redistribute it and/or modify it under the terms of the Cascade Public
 * License 1.0.  Read the file "LICENSE" for details.
 */

#include <stdio.h>
#include <stdint.h>

#define __DEBUG_WARN    0x00000010UL
#define __DEBUG_IO      0x00000100UL
#define __DEBUG_TRACE   0x00001000UL
#define __DEBUG_MEM     0x00010000UL
#define __DEBUG_OP      0x00100000UL
#define __DEBUG_INT     0x01000000UL
#define __DEBUG_LCD     0x10000000UL
#define __DEBUG_SERIAL  0x20000000UL
#define __DEBUG_ABRIDGED 0x80000000UL
#define __DEBUG_IFACE   0x00000002UL
#define __DEBUG_OS      0x00000004UL
#define __DEBUG_KEY     0x00000008UL
#define __DEBUG_HSIO    0x00000020UL
#define __DEBUG_EVENT   0x00000040UL
#define __DEBUG_HINTS   0x00000080UL
#define __DEBUG_UI      0x00000200UL

#define __DEBUG_DEFAULT (__DEBUG_WARN | __DEBUG_SERIAL | __DEBUG_ABRIDGED | __DEBUG_IFACE | __DEBUG_OS | __DEBUG_KEY | __DEBUG_HSIO | __DEBUG_HINTS | __DEBUG_UI)

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

#ifdef __MINGW32__
extern FILE *win_stderr;
#endif

#ifdef NDEBUG
#define DEBUG(level, bla...) do {} while(0)
#else
#ifdef __MINGW32__
#define DEBUG(level, bla...) \
  do { if (unlikely(debug_level & __DEBUG_ ##level)) __mingw_fprintf(win_stderr, bla); /* fflush(win_stderr); */ } while(0)
#else
#define DEBUG(level, bla...) \
  do { if (unlikely(debug_level & __DEBUG_ ##level)) fprintf(stderr, bla); } while(0)
#endif
#endif
#ifdef __MINGW32__
#undef ERROR
#define ERROR(bla...) do { __mingw_fprintf(win_stderr, bla); fflush(win_stderr); } while(0)
#else
#define ERROR(bla...) fprintf(stderr, bla)
#endif

extern uint32_t debug_level;
