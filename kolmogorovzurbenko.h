#ifndef KOLMOGOROVZURBENKO_H
#define KOLMOGOROVZURBENKO_H
#include <QVector>
#include <math.h>

#define WINDOW 5

class KolmogorovZurbenko
{
public:
    static QVector<double>* Filter(const QVector<double>*, const QVector<double>*, int);

private:
    static double mavg1d(QVector<double>* , int, int);
    static int window(QVector<double>*, int);


};

#endif // KOLMOGOROVZURBENKO_H
