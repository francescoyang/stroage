#ifndef SQLAPI_H
#define SQLAPI_H

#include <QSqlDatabase>



typedef struct __storagedetail_t{

}storagedetail_t;

class SqlApi
{
public:
    SqlApi();
private:
    QSqlDatabase db;

    void search();
    void add();
    void sqldelete();
    void update();


};

#endif // SQLAPI_H
