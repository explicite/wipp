#include "bsplain.h"

BSplain::BSplain(QVector<double> &xr, QVector<double> &yr, int slices)
{
    double min = *std::min_element(std::begin(xr), std::end(xr));
    double max = *std::max_element(std::begin(xr), std::end(xr));
    double slice = (max - min)/slices;

    double nSlice = min;

    QVector<double> x;
    QVector<double> y;

    for(int i = 0; i < xr.size() - 1; i++){
        if(xr[i] <= nSlice && xr[i+1] >= nSlice){
            nSlice += slice;
            x.append((xr[i]+xr[i+1])/2);
            y.append(yr[i]);
        }
    }
    x.append(xr.last());
    y.append(yr.last());

    int n = x.size()-1;
    QVector<double> a(y);
    QVector<double> b(n);
    QVector<double> d(n);
    QVector<double> h;

    for(int i = 0; i < n; ++i)
        h.push_back(x[i+1]-x[i]);

    QVector<double> alpha;
    for(int i = 1; i < n; ++i)
        alpha.push_back(3*(a[i+1]-a[i])/h[i] - 3*(a[i]-a[i-1])/h[i-1]);

    QVector<double> c(n+1);
    QVector<double> l(n+1);
    QVector<double> mu(n+1);
    QVector<double> z(n+1);
    l[0] = 1;
    mu[0] = 0;
    z[0] = 0;

    for(int i = 1; i < n-1; ++i)
    {
        l[i] = 2 *(x[i+1]-x[i-1])-h[i-1]*mu[i-1];
        mu[i] = h[i]/l[i];
        z[i] = (alpha[i]-h[i-1]*z[i-1])/l[i];
    }

    l[n] = 1;
    z[n] = 0;
    c[n] = 0;

    for(int j = n-1; j >= 0; --j)
    {
        c[j] = z [j] - mu[j] * c[j+1];
        b[j] = (a[j+1]-a[j])/h[j]-h[j]*(c[j+1]+2*c[j])/3;
        d[j] = (c[j+1]-c[j])/3/h[j];
    }

    this->splineSets = QVector<SplineSet>(n);
    for(int i = 0; i < n; ++i)
    {
        this->splineSets[i].a = a[i];
        this->splineSets[i].b = b[i];
        this->splineSets[i].c = c[i];
        this->splineSets[i].d = d[i];
        this->splineSets[i].x = x[i];
    }
}

double BSplain::interpolate(double x)
{
    SplineSet set = spline(x);
    double ai = set.a;
    double bi = set.b;
    double ci = set.c;
    double di = set.d;
    double xi = set.x;

    return (di*(x-xi)*(x-xi)*(x-xi))+(ci*(x-xi)*(x-xi))+(bi*(x-xi))+ai;
}

SplineSet BSplain::spline(double x)
{
    SplineSet set = splineSets[0];
    for(int i = 1; i < splineSets.size() - 1; i++){
        double xi = splineSets[i-1].x;
        double xii = splineSets[i+1].x;

        if(xi <= x && xii >= x){
            set = splineSets[i];
            break;
        }
    }

    return set;
}
