#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include <QRegExp>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDebug>

class parser
{
public:
    QVector<double> getX();
    QVector<double> getY();
    parser(QString);
    parser(void);
    ~parser(void);
private:
    QFile* file;
    QVector<double> x, y;

};

#endif // PARSER_H
