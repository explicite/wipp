#include "kolmogorovzurbenko.h"

QVector<double> KolmogorovZurbenko::Filter(const QVector<double> *xs, int k)
{
    QVector<double> derivative = KolmogorovZurbenko::derivative(xs);

    QVector<double> *tmp = new QVector<double>(*xs);
    QVector<double> *ans = new QVector<double>(xs->length());
    ans->fill(0.0);
    for(int x = 0; x < k; x++){
        for(int i = 0; i < xs->length(); i++){
            ans->operator [](i) = mavg1d(tmp, i, abs(window(&derivative, i)));
        }
        ans->swap(*tmp);
    }

    return *ans;
}

double KolmogorovZurbenko::mavg1d(QVector<double> *v, int col, int w)
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

QVector<double> KolmogorovZurbenko::derivative(const QVector<double> *xs)
{
    QVector<double> derivative;
    double h = (xs->last() - xs->first()) / xs->size();

    //first point
    derivative.append((xs->operator [](3)-(3*xs->operator [](2))+(3*xs->operator [](1))-xs->operator [](0))/(h*h*h));

    //second point
    derivative.append((xs->operator [](4)-(3*xs->operator [](3))+(3*xs->operator [](2))-xs->operator [](1))/(h*h*h));


    for(int x = 2; x < xs->length()-2; x++){
        double x0 = xs->operator [](x-2);
        double x1 = xs->operator [](x-1);
        double x2 = xs->operator [](x+1);
        double x3 = xs->operator [](x+2);
        derivative.append((x0-(8*x1)+(8*x2)-x3)/(12*h));
    }

    //n - 1
    derivative.append((xs->operator [](xs->length()-2) - (3*xs->operator [](xs->length()-3)) + (3*xs->operator [](xs->length()-4)) - xs->operator [](xs->length()-5))/(h*h*h));

    //n
    derivative.append((xs->operator [](xs->length()-1) - (3*xs->operator [](xs->length()-2)) + (3*xs->operator [](xs->length()-3)) - xs->operator [](xs->length()-4))/(h*h*h));


    return derivative;
}

int KolmogorovZurbenko::window(QVector<double> *derivative, int index)
{
    return derivative->operator [](index)/20;
}
