#include "tab.h"
void tab::setRect(QPointF* pointf, QCPAbstractPlottable* abstractPlottable)
{
    abstractPlottable->parentPlot()->clearItems();
    rect = new QCPItemRect(abstractPlottable->parentPlot());
    abstractPlottable->parentPlot()->addItem(rect);
    rect->topLeft->setCoords(0, (int) minY);
    QPointF* p = new QPointF(pointf->rx(),(int) abstractPlottable->parentPlot()->yAxis->coordToPixel(maxY));
    rect->bottomRight->setPixelPoint(*p);
}

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
    this->rect = nullptr;
    this->minY = 0;
    this->maxY = 0;
}

void tab::clean()
{
    this->x = nullptr;
    this->y = nullptr;
    this->rect = nullptr;
    this->minY = 0;
    this->maxY = 0;
}
