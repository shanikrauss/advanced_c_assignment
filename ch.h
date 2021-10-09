#ifndef CH_H
#define CH_H
#include <stdbool.h>

#define isStar(c) (((c) == '*') ? true : false)
#define isHash(c) (((c) == '#') ? true : false)
#define isSpace(c) (((c) == ' ') ? true : false)

#define IS_DIGIT_PTR(c) (IS_DIGIT(*(c)))

#endif