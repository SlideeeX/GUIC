#pragma once

#if defined(_WIN32)
    #if defined(GUIC_STATIC)
        #define GUIC_API
    #elif defined(GUIC_BUILDING_DLL)
        #define GUIC_API __declspec(dllexport)
    #else
        #define GUIC_API __declspec(dllimport)
    #endif
#else
    #define GUIC_API __attribute__((visibility("default")))
#endif
