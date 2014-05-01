#ifndef FUNCTION_H
#define FUNCTION_H

#include <string.h>
#include <stdlib.h>

class Function
{
public:
    Function(){}

    Function(const Function& that)
    {
        Function(that.size, that.bounds, that.val);
    }

    Function(unsigned int size, double *bounds, double (*val)(double*))
        : size(size), bounds((double*) calloc(size, sizeof(double))), val(val)
    {
        memcpy(this->bounds, bounds, size*sizeof(double));
    }

    Function& operator=(const Function& that);

    unsigned int size;
    double* bounds;
    double (*val)(double*);
};

#endif // FUNCTION_H
