#include "parser.h"

QVector<double> *parser::getTime()
{
    return &time;
}

QVector<double> *parser::getForce()
{
    return &force;
}

QVector<double> *parser::getJaw()
{
    return &jaw;
}

QVector<double> *parser::getPTemp()
{
    return &ptemp;
}

QVector<double> *parser::getStrain()
{
    return &strain;
}

QVector<double> *parser::getTC1()
{
    return &tc1;
}

QVector<double> *parser::getTC2()
{
    return &tc2;
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

    double max = *std::max_element(std::begin(force), std::end(force));

    // cut end of the function
    for(int i = 0; i < force.size(); i++) {
        if(force[i] == max) {
            time.remove(i + 1, time.size() - i - 1);
            force.remove(i + 1, force.size() - i - 1);
            jaw.remove(i + 1, jaw.size() - i - 1);
            ptemp.remove(i + 1, ptemp.size() - i - 1);
            strain.remove(i + 1, strain.size() - i - 1);
            stress.remove(i + 1, stress.size() - i - 1);
            stroke.remove(i + 1, stroke.size() - i - 1);
            tc1.remove(i + 1, tc1.size() - i - 1);
            tc2.remove(i + 1, tc2.size() - i - 1);
            break;
        }
    } 
    // squize vectors
    time.squeeze();
    force.squeeze();
    jaw.squeeze();
    ptemp.squeeze();
    strain.squeeze();
    stroke.squeeze();
    tc1.squeeze();
    tc2.squeeze();

    double avgDerivative = 0;
    // TODO: find
    int start = force.size()*0.7;
    int stop =  force.size()*0.71;
    for(int i = start; i < stop ; i++) {
        if(force[i+1] > force[i])
            avgDerivative += abs((force[i+1] - force[i])/2);
        else
            avgDerivative += abs((force[i] - force[i+1])/2);
    }
    avgDerivative = avgDerivative/(stop - start);

    int maxIndex = 0;
    for(int i = 0; i < force.size()*0.5; i++) {
        double deriv;
        if(force[i+1] > force[i])
            deriv = abs((force[i+1] - force[i])/2);
        else
            deriv = abs((force[i] - force[i+1])/2);

        if(deriv > avgDerivative*avgDerivative){
            maxIndex = i;
        }
    }

    // TODO: cut begining on the function
    for(int i = 0; i < maxIndex; i++) {
        time.pop_front();
        force.pop_front();
        jaw.pop_front();
        ptemp.pop_front();
        strain.pop_front();
        stroke.pop_front();
        tc1.pop_front();
        tc2.pop_front();
    }

}

parser::parser()
{
}

parser::~parser()
{
}
