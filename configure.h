#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QObject>
#include <QMessageBox>

typedef struct __xmlconfigure{
    QString FTPIP;
    QString FTPPORT;
    QString FTPUSER;
    QString FTPPASSWORD;
    QString UpCapPath;
    QString UpCivilPath;
    QString UpEarthquakePath;
    QString UpForestryPath;
    QString UpSeaPath;
    QString UpWaterPath;
    QString UpWeatherPath;

    QString FromCapPath;
    QString FromCivilPath;
    QString FromEarthquakePath;
    QString FromForestryPath;
    QString FromSeaPath;
    QString FromWaterPath;
    QString FromWeatherPath;
    QString WebserviceIP;
    QString WebservicePort;


}xmlconfigure_t;

class Configure : public QObject
{
    Q_OBJECT
public:
    explicit Configure(QObject *parent = 0);
    xmlconfigure_t readconfigure();

private:

    xmlconfigure_t  GetReadConfigure();

    
signals:
//    void error();
    
private slots:
    
};

#endif // CONFIGURE_H
