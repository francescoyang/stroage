#include "configure.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>
#include <QDir>
#include <QSettings>
#include <QLabel>


Configure::Configure(QObject *parent) :
    QObject(parent)
{
}


xmlconfigure_t Configure::readconfigure()
{
    xmlconfigure_t xml;
    QDir dir(QDir::currentPath());
    QString tmp = dir.absolutePath();
    qDebug() << "QDir::currentPath()" << tmp;
    QSettings settings("huachen","display");
//    QFile file("D:\\testftpconfigure.xml");
    QFile file(tmp + "/" +"storageconfigure.xml");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader reader(&file);
        while (!reader.atEnd())
        {
            if(reader.isStartElement())
            {
                if(reader.name() == "FromCapPath")
                {
                    xml.FromCapPath =  reader.readElementText();
                    settings.setValue("FromCapPath",xml.FromCapPath);
                    qDebug() << "1" <<  xml.FromCapPath;
                }else if(reader.name() == "FromCivilPath")
                {
                    xml.FromCivilPath =  reader.readElementText();
                    settings.setValue("FromCivilPath",xml.FromCivilPath);
                    qDebug() << "2" <<  xml.FromCivilPath;
                }else if(reader.name() == "FromEarthquakePath")
                {
                    xml.FromEarthquakePath =  reader.readElementText();
                    settings.setValue("FromEarthquakePath",xml.FromEarthquakePath);
                    qDebug() << "3" <<  xml.FromEarthquakePath;
                }else if(reader.name() == "FromForestryPath")
                {
                    xml.FromForestryPath =  reader.readElementText();
                    settings.setValue("FromForestryPath",xml.FromForestryPath);
                    qDebug() << "4" <<  xml.FromForestryPath;
                }else if(reader.name() == "FromSeaPath")
                {
                    xml.FromSeaPath =  reader.readElementText();
                    settings.setValue("FromSeaPath",xml.FromSeaPath);
                    qDebug() << "5" <<  xml.FromSeaPath;
                }else if(reader.name() == "FromWaterPath")
                {
                    xml.FromWaterPath =  reader.readElementText();
                    settings.setValue("FromWaterPath",xml.FromWaterPath );
                    qDebug() << "6" <<  xml.FromWaterPath ;
                }else if(reader.name() == "FromWeatherPath")
                {
                    xml.FromWeatherPath =  reader.readElementText();
                    settings.setValue("FromWeatherPath",xml.FromWeatherPath);
                    qDebug() << "7" <<  xml.FromWeatherPath;
                }else if(reader.name() == "UpCapPath")
                {
                    xml.UpCapPath =  reader.readElementText();
                    settings.setValue("UpCapPath",xml.UpCapPath);
                    qDebug() << "1" << xml.UpCapPath;
                }else if(reader.name() == "UpCivilPath")
                {
                    xml.UpCivilPath =  reader.readElementText();
                    settings.setValue("UpCivilPath",xml.UpCivilPath);
                    qDebug() <<"2" << xml.UpCivilPath;
                }else if(reader.name() == "UpEarthquakePath")
                {
                    xml.UpEarthquakePath =  reader.readElementText();
                    settings.setValue("UpEarthquakePath",xml.UpEarthquakePath);
                    qDebug() <<"3" << xml.UpEarthquakePath;
                }else if(reader.name() == "UpForestryPath")
                {
                    xml.UpForestryPath =  reader.readElementText();
                    settings.setValue("UpForestryPath",xml.UpForestryPath);
                    qDebug() << "4" <<xml.UpForestryPath;
                }else if(reader.name() == "UpSeaPath")
                {
                    xml.UpSeaPath =  reader.readElementText();
                    settings.setValue("UpSeaPath",xml.UpSeaPath);
                    qDebug() << "5" <<xml.UpSeaPath;
                }else if(reader.name() == "UpWaterPath")
                {
                    xml.UpWaterPath =  reader.readElementText();
                    settings.setValue("UpWaterPath",xml.UpWaterPath );
                    qDebug() <<"6" << xml.UpWaterPath ;
                }else if(reader.name() == "UpWeatherPath")
                {
                    xml.UpWeatherPath =  reader.readElementText();
                    settings.setValue("UpWeatherPath",xml.UpWeatherPath);
                    qDebug() <<"7" << xml.UpWeatherPath;
                }else if(reader.name() == "FTPIP")
                {
                    xml.FTPIP=  reader.readElementText();
                    settings.setValue("FTPIP",xml.FTPIP);
                    qDebug() << xml.FTPIP;
                }else if(reader.name() == "FTPPASSWORD")
                {
                    xml.FTPPASSWORD =  reader.readElementText();
                    settings.setValue("FTPPASSWORD",xml.FTPPASSWORD);
                    qDebug() << xml.FTPPASSWORD;
                }else if(reader.name() == "FTPPORT")
                {
                    xml.FTPPORT =  reader.readElementText();
                    settings.setValue("FTPPORT",xml.FTPPORT);
                    qDebug() << xml.FTPPORT;
                }else if(reader.name() == "FTPUSER")
                {
                    xml.FTPUSER =  reader.readElementText();
                    settings.setValue("FTPUSER",xml.FTPUSER);
                    qDebug() << xml.FTPUSER;
                }else if(reader.name() == "WebserviceIP")
                {
                    xml.WebserviceIP =  reader.readElementText();
                    settings.setValue("WebserviceIP",xml.WebserviceIP);
                    qDebug() << xml.WebserviceIP;
                }else if(reader.name() == "WebservicePort")
                {
                    xml.WebservicePort =  reader.readElementText();
                    settings.setValue("WebservicePort",xml.WebservicePort);
                    qDebug() << xml.WebservicePort;
                }
            }
            reader.readNext();
        }
         return xml;
    }else {
        QDialog *test;
        test = new QDialog;
        QLabel *labtest;
        labtest = new QLabel(test);
        labtest->setText(QString("open \"./displayconfigure.xml\" error\n please chack the configure file"));
        test->setGeometry(500,200,400,100);
        test->show();

        xml.FTPIP = "";
        return xml;
//        emit->error();
    }

}

	//by hanqiang
/*
xmlconfigure_t  Configure::GetReadConfigure()
{
}
*/
