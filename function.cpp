#include "function.h"

Function& Function::operator=(const Function& that)
{
    Function::Function(that);
    return *this;
}


double hanselSpittel(double * args)
{
    double strain = args[1];
    double temp = args[2];
    double area = args[3];
    double n = args[4];
    double q = args[5];
    double m = args[6];
    double B = args[7];

    return area * pow(strain, n) * exp(-q*strain) * pow(1/strain,m) * exp(-B*temp);
}
