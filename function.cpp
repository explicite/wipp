#include "function.h"

Function& Function::operator=(const Function& that)
{
    new Function(that);
    return *this;
}
