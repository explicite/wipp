#include "kolmogorovzurbenko.h"

QVector<double>* KolmogorovZurbenko::kz1d(int iterations)
{
    QVector<double> *tmp = new QVector<double>(*y);
    QVector<double> *ans = new QVector<double>(y->size());
    ans->fill(0.0);
    for(int i = 0; i < iterations; i++){
        for(int yi = 0; yi < y->size(); yi++){
            ans->operator [](yi) = mavg1d(tmp, yi, (WINDOW / (iterations / (i + 1))));
        }
        ans->swap(*tmp);
    }

    return ans;
}

QVector<double>* KolmogorovZurbenko::kza1d(int window, int iterations, int minimumWindowLength, double tolerance)
{
    int n,q, minWindowLength;
    long qh, qt;
    double m;

    n = y->size();

    QVector<double> *d = new QVector<double>(n);
    QVector<double> *prime = new QVector<double>(n);
    QVector<double> *ans = new QVector<double>(n);
    QVector<double> *tmp = new QVector<double>(*y);

    q = window;
    minWindowLength = minimumWindowLength;

    differenced(d, prime, q);
    m = *std::max_element(std::begin(*d), std::end(*d));


    for(int i = 0; i < iterations; i++){
        for(int t = 0; t < n; t++){
            printf("%f\n", d->operator [](t));
            if(abs(prime->operator [](t)) < tolerance){
                qh = (int) floor(q*adaptive(d->operator [](t), m));
                qt = (int) floor(q*adaptive(d->operator [](t), m));
            } else if (abs(prime->operator [](t)) < 0){
                qh = q;
                qt = (int) floor(q*adaptive(d->operator [](t), m));
            } else {
                qh = (int) floor(q*adaptive(d->operator [](t), m));
                qt = q;
            }
            qt = ((qt) < minWindowLength) ? minWindowLength : qt;
            qh = ((qh) < minWindowLength) ? minWindowLength : qh;

            qh = (qh > n-t-1) ? n-t-1 : qh;
            qt = (qt > t) ? t : qt;
            ans->operator [](t) = mavg1d(tmp, t-qt, t+qh+1);
        }
        ans->swap(*tmp);
    }

    return ans;
}

double KolmogorovZurbenko::mavg1d(const QVector<double> *v, int col, int w)
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

void KolmogorovZurbenko::differenced(QVector<double>* d, QVector<double>* prime, int q)
{
    int n = x->size();

    for (int i=0; i<q; i++) d->operator[](i) = abs(x->operator[](i+q) - x->operator[](0));
    for (int i=q; i<n-q; i++) d->operator[](i) = abs(x->operator[](i+q) - x->operator[](i-q));
    for (int i=n-q; i<n; i++) d->operator[](i) = abs(x->operator[](n-1) - x->operator[](i-q));

    for(int i=0; i<n-1; i++) prime->operator[](i) = d->operator[](i+1)-d->operator[](i);
    prime->operator[](n-1) = 0;
}

double KolmogorovZurbenko::adaptive(double d, double m)
{
    return( 1 - (d/m) );
}

double KolmogorovZurbenko::error(double *params){
    double tolerance = params[0];

    QVector<double>* computed = kza1d(5, 20, 2, tolerance);

    double value = 0;

    for(int i = 0; i < index->size(); i++){
        double indexValue = index->operator [](i);
        double computedValue = computed->operator [](indexValue);
        double measuredValue = y->operator [](indexValue);
        value += abs(abs(computedValue)-abs(measuredValue));
    }

    return value;
}
