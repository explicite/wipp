#ifndef TAB_H
#define TAB_H
#include<QVector>
#include<QPoint>
#include"qcustomplot.h"
class tab
{
public:
    tab();
    tab(QVector<double>*, QVector<double>*);
    void clean();
    QVector<QPoint>* getPoints();
private:
    QVector<double>* x;
    QVector<double>* y;
    double minY;
    double maxY;
};

#endif // TAB_H
