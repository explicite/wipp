#include "parser.h"

QVector<double> parser::getTime()
{
    return time;
}

QVector<double> parser::getForce()
{
    return force;
}

QVector<double> parser::getJaw()
{
    return jaw;
}

QVector<double> parser::getPTemp()
{
    return ptemp;
}

QVector<double> parser::getStrain()
{
    return strain;
}

QVector<double> parser::getTC1()
{
    return tc1;
}

QVector<double> parser::getTC2()
{
    return tc2;
}

parser::parser(QString filename)
{
    file = new QFile(filename);
    if(file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(file);
        QString line = in.readLine();

        while ( !in.atEnd() )
        {
            line = in.readLine();
            QStringList tokens = line.split(QRegExp("(\\s+)"), QString::SkipEmptyParts);

            if(-1*tokens[2].toDouble()>=0)
            {
                time.append(-1*tokens[0].toDouble());
                force.append(-1*tokens[1].toDouble());
                jaw.append(-1*tokens[2].toDouble());
                ptemp.append(-1*tokens[3].toDouble());
                strain.append(-1*tokens[4].toDouble());
                stress.append(-1*tokens[5].toDouble());
                stroke.append(-1*tokens[6].toDouble());
                tc1.append(-1*tokens[7].toDouble());
                tc2.append(-1*tokens[8].toDouble());
            }
        }
    }

    file->close();
}

parser::parser()
{
}

parser::~parser()
{
}
