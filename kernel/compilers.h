#ifndef __COMPILERS_H__
#define __COMPILERS_H__

#if defined(__GNUC__) || defined(__clang__)
    #define ATTRIBUTE_NORETURN __attribute__((noreturn))
#elif defined(_MSC_VER)
    #define ATTRIBUTE_NORETURN __declspec(noreturn)
#elif __STDC_VERSION__ >= 201112L
    #define ATTRIBUTE_NORETURN _Noreturn
#else
    #define ATTRIBUTE_NORETURN
#endif

#endif
