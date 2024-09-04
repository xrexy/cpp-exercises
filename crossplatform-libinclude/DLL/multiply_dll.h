#pragma once

#if defined(_WIN32) || defined(_WIN64)
// --- WINDOWS
#ifdef VSLIBINCLUDE_EXPORTS
#define MULTIPLY_API __declspec(dllexport)
#else
#define MULTIPLY_API __declspec(dllimport)
#endif
// --- WINDOWS
#else
// --- LINUX
#ifdef VSLIBINCLUDE_EXPORTS
#define MULTIPLY_API __attribute__((visibility("default")))
#else
#define MULTIPLY_API
#endif
// --- LINUX
#endif

extern "C" MULTIPLY_API int multiplyDLL(const int a, const int b);
