#ifndef KOLMOGOROVZURBENKO_H
#define KOLMOGOROVZURBENKO_H
#include <QVector>
#include <math.h>

#define WINDOW 10
#define NO_ITERATIONS 500
#define NO_WOLFS 500

class KolmogorovZurbenko
{
public:
    KolmogorovZurbenko(){}
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

    QVector<double>* kz1d(int);
    QVector<double>* kza1d(int, int, int, double);

private:
    const QVector<double> *x;
    const QVector<double> *y;
    const QVector<int> *index;

    double error(double *params);
    static double mavg1d(const QVector<double>* , int, int);
    void differenced(QVector<double>*, QVector<double>*, int);
    static double adaptive(double, double);    
};



#endif // KOLMOGOROVZURBENKO_H
