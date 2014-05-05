#include "tab.h"
QVector<QPoint>* tab::getPoints()
{
    return NULL;
}

tab::tab(QVector<double>* x, QVector<double>* y)
{
    tab();
    this->x = x;
    this->y = y;
    this->maxY = *std::max_element(std::begin(*y), std::end(*y));
    this->minY = *std::min_element(std::begin(*y), std::end(*y));
}

tab::tab()
{
    this->x = nullptr;
    this->y = nullptr;
    this->minY = 0;
    this->maxY = 0;
}

void tab::clean()
{
    this->x = nullptr;
    this->y = nullptr;
    this->minY = 0;
    this->maxY = 0;
}
