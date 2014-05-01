#include "function.h"

Function& Function::operator=(const Function& that)
{
    Function::Function(that);
    return *this;
}
