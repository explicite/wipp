#ifndef KOLMOGOROVZURBENKO_H
#define KOLMOGOROVZURBENKO_H
#include <QVector>
class KolmogorovZurbenko
{
public:
    static QVector<double> Filter(const QVector<double>*, int);

private:
    static double mavg1d(QVector<double>* , int, int);

};

#endif // KOLMOGOROVZURBENKO_H
