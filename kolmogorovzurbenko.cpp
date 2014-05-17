#include "kolmogorovzurbenko.h"

QVector<double>* KolmogorovZurbenko::Filter(const QVector<double> *xs, const QVector<double> *ys, int k)
{
    QVector<double> *tmp = new QVector<double>(*ys);
    QVector<double> *ans = new QVector<double>(ys->size());
    ans->fill(0.0);
    for(int x = 0; x < k; x++){
        for(int i = 0; i < ys->size(); i++){
            ans->operator [](i) = mavg1d(tmp, i, (5 / (k / (x + 1))));
        }
        ans->swap(*tmp);
    }

    return ans;
}

double KolmogorovZurbenko::mavg1d(QVector<double> *v, int col, int w)
{
    double s = 0.0;
    int startcol, endcol;

    if (v->size() > 0) {
        startcol = (col - w > 0 ? col - w : 0);
        endcol = (col + w < v->size() ? col + w + 1 : v->size());

        for(int i = startcol; i < endcol; i++){
            s += v->operator[](i);
        }
    } else return 0.0;

    return s / ((double)(endcol - startcol));
}
