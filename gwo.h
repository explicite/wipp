#ifndef GWO_H
#define GWO_H

#include "kolmogorovzurbenko.h"
#include "function.h"
#include "optimum.h"
#include <limits.h>
#include <QVector>
#include <time.h>
#include <math.h>
#include <omp.h>

class GWO
{
public:
    GWO() {}
    GWO(Function &function) : function(&function) {}
    QVector<double> *min(unsigned int numberOfWolfs, unsigned int numberOfIterations);
    QVector<double> *max(unsigned int numberOfWolfs, unsigned int numberOfIterations);
    QVector<double> *minKZ(unsigned int numberOfWolfs, unsigned int numberOfIterations, KolmogorovZurbenko *kolmogorovZurbenko);
    QVector<double> *maxKZ(unsigned int numberOfWolfs, unsigned int numberOfIterations, KolmogorovZurbenko *kolmogorovZurbenko);

protected:
    QVector<double> *optimize(enum Optimum optimum, unsigned int numberOfWolfs, unsigned int numberOfIterations);
    QVector<double> *optimizeKZ(enum Optimum optimum, unsigned int numberOfWolfs, unsigned int numberOfIterations, KolmogorovZurbenko *kolmogorovZurbenko);
    double nextRandom(double min, double max);
    double **generatePack(unsigned int numberOfWolfs);
    void backToSpace(double **pack, unsigned int numberOfWolfs);

private:
    Function *function;
    KolmogorovZurbenko *kolmogorovZurbenko;
};

#endif // GWO_H
