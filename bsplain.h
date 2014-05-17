#ifndef BSPLAIN_H
#define BSPLAIN_H

#include <QVector>

struct SplineSet{
    double a;
    double b;
    double c;
    double d;
    double x;
};

class BSplain
{
public:
    BSplain(){}
    BSplain(QVector<double> &, QVector<double> &, int);
    double interpolate(double);

private:
    QVector<SplineSet> splineSets;
    SplineSet spline(double);
};

#endif // BSPLAIN_H
