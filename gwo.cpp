#include "gwo.h"

QVector<double> *GWO::min(unsigned int numberOfWolfs, unsigned int numberOfIterations)
{
    return GWO::optimize(MIN, numberOfWolfs, numberOfIterations);
}

QVector<double> *GWO::max(unsigned int numberOfWolfs, unsigned int numberOfIterations)
{
    return GWO::optimize(MAX, numberOfWolfs, numberOfIterations);
}


QVector<double> *GWO::optimize(enum Optimum optimum, unsigned int numberOfWolfs, unsigned int numberOfIterations)
{
    srand(time(NULL));
    double Infinity = std::numeric_limits<double>::infinity();

    switch(optimum)
    {
    case MIN:
        break;
    case MAX:
        Infinity = -Infinity;
        break;
    }

    double *alphaPosition 	= (double*) calloc(function->size, sizeof(double));
    double 	alphaScore		= Infinity;

    double *betaPosition 	= (double*) calloc(function->size, sizeof(double));
    double 	betaScore		= Infinity;

    double *deltaPosition 	= (double*) calloc(function->size, sizeof(double));
    double  deltaScore		= Infinity;

    double **pack           = generatePack(numberOfWolfs);


    for(unsigned int iteration = 0; iteration < numberOfIterations; iteration++){
            for(unsigned int wolf = 0; wolf < numberOfWolfs; wolf++){
                backToSpace(pack, numberOfWolfs);

                double fitness = function->val(pack[wolf]);

                if(fitness < alphaScore) {
                    alphaScore = fitness;
                    memcpy(alphaPosition, pack[wolf], function->size*sizeof(double));
                }

                if(fitness > alphaScore && fitness < betaScore) {
                    betaScore = fitness;
                    memcpy(betaPosition, pack[wolf], function->size*sizeof(double));
                }

                if(fitness > alphaScore && fitness > betaScore && fitness < deltaScore) {
                    deltaScore = fitness;
                    memcpy(deltaPosition, pack[wolf], function->size*sizeof(double));
                }
            }

            double a = 2.0 - iteration * (2.0 / numberOfIterations);

            #pragma omp parallel for
            for(int i = 0; i < numberOfWolfs; i++){
                for(int j = 0; j < function->size; j++){
                    double alpha 	= abs((2.0*nextRandom(0.0, 1.0))*alphaPosition[j] - pack[i][j]);
                    double x1 		= alphaPosition[j] - ((2.0*a*nextRandom(0.0, 1.0)) - 1.0) * alpha;

                    double beta 	= abs((2.0*nextRandom(0.0, 1.0))*betaPosition[j] - pack[i][j]);
                    double x2 		= betaPosition[j] - ((2.0*a*nextRandom(0.0, 1.0)) - 1.0) * beta;

                    double delta 	= abs((2.0*nextRandom(0.0, 1.0))*deltaPosition[j] - pack[i][j]);
                    double x3 		= deltaPosition[j] - ((2.0*a*nextRandom(0.0, 1.0)) - 1.0) * delta;

                    pack[i][j] = (x1 + x2 + x3) / 3.0;
                }
            }
        }

        return new QVector<double>(function->size, *alphaPosition);
}

double GWO::nextRandom(double min, double max)
{
    return (min + (rand() / (RAND_MAX / (max - min))));
}

double **GWO::generatePack(unsigned int numberOfWolfs)
{
    double **pack = (double**) malloc(numberOfWolfs*sizeof(double));
    #pragma omp parallel for
    for(int x = 0; x < numberOfWolfs; x++)
        pack[x] = (double*) malloc(this->function->size*sizeof(double));

    #pragma omp parallel for
    for(int x = 0; x < numberOfWolfs; x++)
            for(int y = 0; y < this->function->size; y++)
                pack[x][y] = nextRandom(this->function->bounds[y*2], this->function->bounds[(y*2)+1]);

    return pack;
}

void GWO::backToSpace(double **pack, unsigned int numberOfWolfs)
{
    #pragma omp parallel for
    for(int x = 0; x < numberOfWolfs; x++)
        for(int y = 0; y < this->function->size; y++)
            if(pack[x][y] >= this->function->bounds[(y*2)+1] || pack[x][y] <= this->function->bounds[(y*2)])
                pack[x][y] = nextRandom(this->function->bounds[y*2], this->function->bounds[(y*2)+1]);
}


