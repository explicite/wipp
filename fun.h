#ifndef FUN_H
#define FUN_H

typedef struct
{
    unsigned int size;
    double* bounds;
    double (*val)(double);
} fun;

#endif // FUN_H
