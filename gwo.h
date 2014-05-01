#ifndef GWO_H
#define GWO_H

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

protected:
    QVector<double> *optimize(enum Optimum optimum, unsigned int numberOfWolfs, unsigned int numberOfIterations);
    double nextRandom(double min, double max);
    double **generatePack(unsigned int numberOfWolfs);
    void backToSpace(double **pack, unsigned int numberOfWolfs);

private:
    Function *function;
};

#endif // GWO_H
