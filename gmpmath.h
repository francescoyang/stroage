#ifndef GMPMATH_H
#define GMPMATH_H
#include <QString>

class GmpMath
{
public:
    GmpMath();
    QString math(QString a, QString op,QString b);
    int count;
};

#endif // GMPMATH_H
