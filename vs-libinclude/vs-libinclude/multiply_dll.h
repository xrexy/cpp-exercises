#pragma once

#ifdef VSLIBINCLUDE_EXPORTS
#define MULTIPLY_API __declspec(dllexport)
#else
#define MULTIPLY_API __declspec(dllimport)
#endif

extern "C" MULTIPLY_API int multiplyDLL(const int a, const int b);
