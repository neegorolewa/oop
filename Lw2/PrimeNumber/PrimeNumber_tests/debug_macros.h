#pragma once
#ifndef DEBUG_MACROS_H
#define DEBUG_MACROS_H

#ifdef NDEBUG
#define DEBUG_IN_RELEASE(code) code
#else
#define DEBUG_IN_RELEASE(code)
#endif

#endif // DEBUG_MACROS_H