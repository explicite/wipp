#include "parser.h"

QVector<double> parser::getX()
{
    return x;
}

QVector<double> parser::getY()
{
    return y;
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
            QString line = in.readLine();
            QStringList tokens = line.split(QRegExp("(\\s+)"), QString::SkipEmptyParts);

            for(int i = 0; i < tokens.size(); i++){
                if(i == 2){
                    x.append(-1*tokens[i].toDouble());
                }else if(i == 1){
                    y.append(-1*tokens[i].toDouble());
                }
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
