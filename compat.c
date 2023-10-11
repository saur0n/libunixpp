/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  MUSL compatibility layer
 *  
 *  © 2023, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifdef PLATFORM_MUSL

#include <locale.h>

#if 0
intmax_t strtoimax(const char *__restrict __nptr, char **__restrict __endptr, int __base);
intmax_t __isoc23_strtoimax(const char *__restrict __nptr, char **__restrict __endptr, int __base) {
    return strtoimax(__nptr, __endptr, __base);
}
#endif

long int strtol(const char *__restrict __nptr, char **__restrict __endptr, int __base);
long int __isoc23_strtol(const char *__restrict __nptr, char **__restrict __endptr, int __base) {
    return strtol(__nptr, __endptr, __base);
}

#if 0
long int strtol_l(const char *__restrict __nptr, char **__restrict __endptr, int __base, locale_t __loc);
long int __isoc23_strtol_l(const char *__restrict __nptr, char **__restrict __endptr, int __base, locale_t __loc) {
    return strtol_l(__nptr, __endptr, __base, __loc);
}
#endif

long long int strtoll(const char *__restrict __nptr, char **__restrict __endptr, int __base);
long long int __isoc23_strtoll(const char *__restrict __nptr, char **__restrict __endptr, int __base) {
    return strtoll(__nptr, __endptr, __base);
}

#if 0
long long int strtoll_l(const char *__restrict __nptr, char **__restrict __endptr, int __base, locale_t __loc);
long long int __isoc23_strtoll_l(const char *__restrict __nptr, char **__restrict __endptr, int __base, locale_t __loc) {
    return strtoll_l(__nptr, __endptr, __base, __loc);
}
#endif

unsigned long int strtoul(const char *__restrict __nptr, char **__restrict __endptr, int __base);
unsigned long int __isoc23_strtoul(const char *__restrict __nptr, char **__restrict __endptr, int __base) {
    return strtoul(__nptr, __endptr, __base);
}

#if 0
unsigned long int strtoul_l(const char *__restrict __nptr, char **__restrict __endptr, int __base, locale_t __loc);
unsigned long int __isoc23_strtoul_l(const char *__restrict __nptr, char **__restrict __endptr, int __base, locale_t __loc) {
    return strtoul_l(__nptr, __endptr, __base, __loc);
}
#endif

unsigned long long int strtoull(const char *__restrict __nptr, char **__restrict __endptr, int __base);
unsigned long long int __isoc23_strtoull(const char *__restrict __nptr, char **__restrict __endptr, int __base) {
    return strtoull(__nptr, __endptr, __base);
}

#if 0
unsigned long long int strtoull_l(const char *__restrict __nptr, char **__restrict __endptr, int __base, locale_t __loc);
unsigned long long int __isoc23_strtoull_l(const char *__restrict __nptr, char **__restrict __endptr, int __base, locale_t __loc) {
    return strtoull_l(__nptr, __endptr, __base, __loc);
}
#endif

#if 0
//weak_alias (__isoc23_strtoull, __isoc23_strtoumax)

intmax_t __isoc23_wcstoimax

__isoc23_wcstol

__isoc23_wcstol_l

__isoc23_wcstoll

__isoc23_wcstoll_l

__isoc23_wcstoul

__isoc23_wcstoul_l

unsigned long long int __isoc23_wcstoull

unsigned long long int __isoc23_wcstoull_l

__isoc23_wcstoumax
#endif

#endif
