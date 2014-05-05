#include "kolmogorovzurbenko.h"

QVector<double> KolmogorovZurbenko::Filter(const QVector<double> *xs, const QVector<double> *ys, int k)
{
    QVector<double> derivative = KolmogorovZurbenko::derivative(ys, xs);

    QVector<double> *tmp = new QVector<double>(*ys);
    QVector<double> *ans = new QVector<double>(ys->length());
    ans->fill(0.0);
    for(int x = 0; x < k; x++){
        for(int i = 0; i < ys->length(); i++){
            ans->operator [](i) = mavg1d(tmp, i, window(&derivative, i));
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

QVector<double> KolmogorovZurbenko::derivative(const QVector<double> *xs, const QVector<double> *ys)
{
    QVector<double> derivative;
    double max = 0;

    for(int y = 0; y < ys->length()-2; y++){
        double h = abs((xs->operator [](y+2) - xs->operator [](y)) / 3);
        double y0 = ys->operator [](y);
        double y1 = ys->operator [](y+1);
        double y2 = ys->operator [](y+2);

        double deriv = (y2-(2*y1)+y0)/(h*h);
        derivative.append(deriv);

        if(abs(deriv) > max && abs(deriv) != std::numeric_limits<double>::infinity())
            max = abs(deriv);

    }

    //n - 1
    derivative.append(derivative.last());

    //n
    derivative.append(derivative.last());

    for(int i = 0; i < derivative.length(); i++)
        derivative[i]= derivative[i]/max;


    return derivative;
}

int KolmogorovZurbenko::window(QVector<double> *derivative, int index)
{
    return abs(derivative->operator [](index))/000000.1;
}
