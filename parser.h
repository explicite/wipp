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

    QVector<double> getTime();
    QVector<double> getForce();
    QVector<double> getJaw();
    QVector<double> getPTemp();
    QVector<double> getStrain();
    QVector<double> getStress();
    QVector<double> getStroke();
    QVector<double> getTC1();
    QVector<double> getTC2();

    parser(QString);
    parser(void);
    ~parser(void);
private:

    QFile* file;
    QVector<double> time, force, jaw, ptemp, strain, stress, stroke, tc1, tc2;

};

#endif // PARSER_H
