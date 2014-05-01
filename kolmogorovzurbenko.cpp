#include "kolmogorovzurbenko.h"
#include <math.h>

QVector<double> KolmogorovZurbenko::Filter(const QVector<double>* x, int k)
{
    int window = floor(x->length() * 0.001);
    QVector<double>* tmp = new QVector<double>(*x);
    QVector<double>* ans = new QVector<double>(x->length());
    ans->fill(0.0);
    for(int z = 0; z < k; z++){
        for(int i = 0; i < x->length(); i++){
            ans->operator [](i) = mavg1d(tmp, i, window);
        }
        ans->swap(*tmp);
    }

    return *ans;
}

double KolmogorovZurbenko::mavg1d(QVector<double>* v, int col, int w)
{
    double s = 0.0;
    int startcol, endcol;

    if (v->length() > 0) {
        startcol = (col - w > 0 ? col - w : 0);
        endcol = (col + w < v->length() ? col + w + 1 : v->length());

        for(int i = startcol; i < endcol; i++){
            s += v->operator[](i);
        }
    } else return 0.0;

    return s / ((double)(endcol - startcol));
}
