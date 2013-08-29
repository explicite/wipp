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
    void setRect(QPointF*, QCPAbstractPlottable*);
    QVector<QPoint>* getPoints();
private:
    QVector<double>* x;
    QVector<double>* y;
    QCPItemRect* rect;
    double minY;
    double maxY;
};

#endif // TAB_H
