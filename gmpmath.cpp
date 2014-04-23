#include "gmpmath.h"
#include "gmpxx.h"
#include <QDebug>


GmpMath::GmpMath()
{
}
QString GmpMath::math(QString a, QString op,QString b)
{
    qDebug() << "gmpmath " << a << op << b;
    mpf_class a_g(a.toLatin1().data()), b_g(b.toLatin1().data()), f_g;
    mp_exp_t leng;


    if(op == "+")
    {
        f_g = a_g + b_g;

    }else if(op == "-")
    {
        f_g = a_g - b_g;
    }else if(op == "*")
    {
        //        qDebug() << "get * math";
        f_g = a_g * b_g;
    }else if(op == "/")
    {
        f_g = a_g / b_g;
    }else {
        return "-1";
    }

    QString tmpx =  QString::fromLocal8Bit(f_g.get_str(leng,10,20).c_str());
    count = 0;
    count = tmpx.count();
    if((int)leng >= count){

        for(int i = 0;i < ((int)leng - count);i ++){
            tmpx.append("0");
        }
        qDebug() << "leng = " << leng << "tmpx = " << tmpx << "count = " << count;
        if(tmpx == ""){
            tmpx = "0";
        }
        return tmpx;
    }else {
        qDebug() << "leng = " << leng << "tmpx = " << QString(tmpx.left((int)leng) + "." + tmpx.mid((int)leng, 4));
        return QString(tmpx.left((int)leng) + "." + tmpx.mid((int)leng, 4));
    }
}
