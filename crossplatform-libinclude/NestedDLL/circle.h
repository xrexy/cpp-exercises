#pragma once

#if defined(_WIN32) || defined(_WIN64)
// --- WINDOWS
#ifdef NESTEDDLL_EXPORTS
#define CIRCLE_API __declspec(dllexport)
#else
#define CIRCLE_API __declspec(dllimport)
#endif
// --- WINDOWS
#else
// --- LINUX
#ifdef NESTEDDLL_EXPORTS
#define CIRCLE_API __attribute__((visibility("default")))
#else
#define CIRCLE_API
#endif
// --- LINUX
#endif

extern "C" CIRCLE_API int calculateCircleDiameter(const int radius);
