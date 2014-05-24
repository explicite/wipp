#ifndef KOLMOGOROVZURBENKO_H
#define KOLMOGOROVZURBENKO_H
#include <QVector>
#include <math.h>
#include "gwo.h"

#define WINDOW 10
#define NO_ITERATIONS 500
#define NO_WOLFS 500

class KolmogorovZurbenko
{
public:
    KolmogorovZurbenko(QVector<double> x, QVector<double> y, int nodes) {
        this->x = &x;
        this->y = &y;

        double refMin = *std::min_element(std::begin(x), std::end(x));
        double refMax = *std::max_element(std::begin(x), std::end(x));
        double slice = (refMax - refMin)/nodes;

        double nSlice = refMin;

        QVector<int> index;

        for(int i = 0; i < x.size()-1; i++){
            if(x[i] <= nSlice && x[i+1] >= nSlice){
                nSlice += slice;
                index.append(i);
            }
        }

        index.append(x.last());

        this->index = &index;

        double *bounds = (double*) malloc(2*sizeof(double));
        bounds[0] = 0.1;
        bounds[1] = 5;
    }

    QVector<double>* filtering();

private:
    const QVector<double> *x;
    const QVector<double> *y;
    const QVector<int> *index;
    Function* function;
    QVector<double>* kz1d(int);
    QVector<double>* kza1d(int, int, int, double);
    static double mavg1d(const QVector<double>* , int, int);
    static void differenced(const QVector<double>*, QVector<double>*, QVector<double>*, int);
    static double adaptive(double, double);
    double error(double *params);
};



#endif // KOLMOGOROVZURBENKO_H
