#pragma once

#ifdef NESTEDDLL_EXPORTS
#define CIRCLE_API __declspec(dllexport)
#else
#define CIRCLE_API __declspec(dllimport)
#endif

extern "C" CIRCLE_API int calculateCircleDiameter(const int radius);
