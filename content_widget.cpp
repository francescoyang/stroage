//#include "gmpxx.h"
//#include "gmp.h"
#include "content_widget.h"
#include "toolswidget.h"
#include <QLabel>
#include <QSqlQuery>
#include <QVBoxLayout>
#include <QSplitter>
#include <QLineEdit>
#include <QSpacerItem>
#include <QHeaderView>
#include <QLatin1String>
#include <QFile>
#include <QSettings>
#include <QDebug>
#include <QThread>




ContentWidget::ContentWidget(QWidget *parent) :
    QWidget(parent)
{
    sql_x = -1;
    sql_y = -1;
    tab_page = true;
    search_page = false;

    if(!sqlInit(false)){
        QMessageBox message(QMessageBox::NoIcon, "提示", "请先选中一件库存商品");
        message.setIconPixmap(QPixmap(":/img/safe"));
        message.exec();
        return;
    }

    //    configure = new Configure;
    //    configure->readconfigure();

    excelengine = new ExcelEngine;
    QThread* daemon_thread = new QThread;
    excelengine->moveToThread(daemon_thread);
    daemon_thread->start(QThread::IdlePriority);
    //    connect(this, SIGNAL(saveExecl(QMap<int,QTableWidget *>)),excelengine, SIGNAL(signals_saveExecl(QMap<int,QTableWidget *>)));
    //    saveExecl(product_table);


    main_widget = new QWidget(this);
    storage_table = new QTableWidget(this);
    product_table = new QTableWidget(this);
    gmpmath = new GmpMath;


    setToolsWidget();

    setProductTab();
    setStorageTab();
    setTabWidget();
    tabShow();
    QPalette palette;

    tools_widget->setAutoFillBackground(true);
    main_widget->setAutoFillBackground(true);
    palette.setColor(QPalette::Background,QColor(155,225,123));

    tools_widget->setPalette(palette);
    tools_widget->setFixedHeight(75);

    main_splitter = new QSplitter(this);

    main_splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_splitter->setOrientation(Qt::Vertical);
    main_splitter->setHandleWidth(0);
    main_splitter->setStyleSheet("QSplitter::handle{background:lightgray;}");


    main_splitter->addWidget(tools_widget);
    //    main_splitter->addWidget(left_widget);
    main_splitter->addWidget(main_widget);

    for(int i = 0; i<main_splitter->count();i++)
    {
        QSplitterHandle *handle = main_splitter->handle(i);
        handle->setEnabled(false);
    }
    qDebug() << "content_ widget ok";

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(main_splitter);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    connect(btn_add, SIGNAL(clicked()),this, SLOT(addwidget()));
    connect(btn_minus, SIGNAL(clicked()),this, SLOT(minuswidget()));
    connect(btn_plus, SIGNAL(clicked()),this, SLOT(pluswidget()));
    connect(btn_delete, SIGNAL(clicked()),this, SLOT(sqldelete()));
    connect(btn_cancel, SIGNAL(clicked()),this, SLOT(sqlcancel()));
    connect(btn_outinto, SIGNAL(clicked()),this, SLOT(saveas()));
    setLayout(main_layout);
    //    slotStyleChange(0);
    btnEnable(false);

}


void ContentWidget::btnEnable(bool enabled)
{
    btn_minus->setEnabled(enabled);
    btn_plus->setEnabled(enabled);
    btn_delete->setEnabled(enabled);
    btn_cancel->setEnabled(!enabled);

}

void ContentWidget::addwidget()
{
    showwidget(1,"");
}

void ContentWidget::minuswidget()
{
    if(sql_x < 0)
    {

        QMessageBox message(QMessageBox::NoIcon, "提示", "请先选中一件库存商品");
        message.setIconPixmap(QPixmap(":/img/safe"));
        message.exec();
        return;
    }
    showwidget(2,"");
}

void ContentWidget::pluswidget()
{
    if(sql_x < 0)
    {

        QMessageBox message(QMessageBox::NoIcon, "提示", "请先选中一件库存商品");
        message.setIconPixmap(QPixmap(":/img/safe"));
        message.exec();
        return;
    }
    showwidget(3,"");
}

void ContentWidget::saveas()
{
    excelSave();
}

void ContentWidget::showwidget(int index,QString tmp)
{
    switch(index)
    {
    case 1:
    {
        inputdialog =  new AboutUsDialog(this,index,QString(""));
        break;
    }
    case 2:
    case 3:
    {
        inputdialog =  new AboutUsDialog(this,index,storage_table->item(sql_x,1)->text());
        break;
    }
    case 4:
    {
        inputdialog =  new AboutUsDialog(this,index,tmp);
        break;
    }
    case 5:
    {
        inputdialog =  new AboutUsDialog(this,index,"");
        break;
    }
    case 6:
    {
        inputdialog =  new AboutUsDialog(this,index,"");
        break;
    }
    default:
        break;
    }
    inputdialog->open();
    connect(inputdialog,SIGNAL(setinput(QStringList,int)),this,SLOT(setinput(QStringList,int)));
}

void ContentWidget::sqlinit_slot()
{
    showwidget(5,"");
}

void ContentWidget::changepasswd_slot()
{
    showwidget(6,"");
}


void ContentWidget::setinput(QStringList tmp,int index)
{
    qDebug() << tmp;
    storage_t s_tmp;
    switch(index){
    case 1:
    {
        s_tmp.name = tmp.at(0);
        s_tmp.price = tmp.at(1);
        s_tmp.amount = tmp.at(2);
        s_tmp.controller = tmp.at(3);
        s_tmp.signature = tmp.at(4);
        s_tmp.remark = tmp.at(5);
        s_tmp.time = gettime();
        s_tmp.state = "新添加";
        //        s_tmp.total_price = QString("%1").arg((tmp.at(1).toInt() * tmp.at(2).toInt()));
        s_tmp.total_price = gmpmath->math(tmp.at(1),"*",tmp.at(2));
        //                QString::number((tmp.at(1).toInt() * tmp.at(2).toInt()),10);
        //        show_widget->close();
        sqladd(s_tmp);
        break;
    }
    case 2:
    {
        s_tmp.name = tmp.at(0);
        s_tmp.amount = tmp.at(1);
        s_tmp.controller = tmp.at(2);
        s_tmp.signature = tmp.at(3);
        s_tmp.remark = tmp.at(4);
        s_tmp.time = gettime();
        s_tmp.state = "出库";
        sqlminus(s_tmp);
        break;
    }
    case 3:
    {

        s_tmp.name = tmp.at(0);
        s_tmp.price = tmp.at(1);
        s_tmp.amount = tmp.at(2);
        s_tmp.controller = tmp.at(3);
        s_tmp.signature = tmp.at(4);
        s_tmp.remark = tmp.at(5);
        s_tmp.time = gettime();
        s_tmp.state = "入库";
        //        s_tmp.total_price = QString::number((tmp.at(1).toInt() * tmp.at(2).toInt()),10);
        sqlplus(s_tmp);

        break;
    }
    case 5:
    {
        db.close();
        backup();
        if(!sqlInit(true)){
            QMessageBox message(QMessageBox::NoIcon, "提示", "初始化数据库失败");
            message.setIconPixmap(QPixmap(":/img/safe"));
            message.exec();
            return;
        }else {
            tabShow();
        }
        break;
    }
    default:
        break;

    }

    //    tmp.append(E_name->text());
    //    tmp.append(E_price->text());
    //    tmp.append(E_amount->text());
    //    tmp.append(E_controller->text());
    //    tmp.append(E_sign->text());
    //    tmp.append(E_remark->text());
}

void ContentWidget::backup()
{
    QDateTime DateTime;
    QTime Time;
    QDate Date;
    DateTime = QDateTime::currentDateTime();
    Time = DateTime.time();
    Date = DateTime.date();


    QDir dir(QDir::currentPath());
    QString tmp = dir.absolutePath();

    QFile file(tmp + "//sql//" +"nbut.zh");
    file.copy(tmp + "//sql//" +"nbut.zh",tmp + "//backup//init" +Date.toString("yyyyMMdd") + Time.toString("hhmmsszzz"));
}
bool ContentWidget::product_add(storage_t tmp)
{

    QSqlQuery querylist;
    //        qDebug() << "create " << querylist.exec("create table storage (id integer primary key,name varchar(45),price varchar(20),amount varchar(20),controller varchar(20),time varchar(20))");//创建表,已经创建
    qDebug() << QString("insert into sql_product_table (v_id,name,state,amount,price,total_price,controller,signature,remark,time)values('" \
                        + tmp.v_id + "','"  + tmp.name+ "','"+ tmp.amount + "','" + tmp.state + "','"  + tmp.price + "','" + tmp.total_price  + "','" +  tmp.controller +  "','" + tmp.signature + "','" + tmp.remark +  "','" +  tmp.time + "')");

    if(!querylist.exec(QString("insert into sql_product_table (v_id,name,state,amount,price,total_price,controller,signature,remark,time)values('" \
                               + tmp.v_id + "','" + tmp.name+ "','"+ tmp.state + "','"  + tmp.amount + "','"    + tmp.price + "','" + tmp.total_price  + "','" +  tmp.controller +  "','" + tmp.signature + "','" + tmp.remark +  "','" +  tmp.time + "')")))
    {
        QMessageBox msgBox;
        msgBox.setText("添加商品入库日志失败");
        msgBox.setInformativeText("请联系管理员");
        msgBox.setIconPixmap(QPixmap(":/img/safe"));
        msgBox.exec();
        return false;
    }
}

void ContentWidget::product_show(storage_t tmp_tmp)
{
    int i = 0;
    QSqlQuery query;
    storage_t tmp;
    qDebug() << "product_show(storage_t tmp_tmp)" << query.exec("select * from sql_product_table where name='" + tmp_tmp.name + "'");

    product_table->setRowCount(0);
    while(query.next())
    {
        //       v_id,name,state,amount,price,total_price,controller,signature,remark,time
        //        QString id = query.value(0).toString();
        tmp.name = query.value(2).toString();
        tmp.state = query.value(3).toString();
        tmp.amount = query.value(4).toString();
        tmp.price = query.value(5).toString();
        tmp.total_price = query.value(6).toString();
        tmp.controller = query.value(7).toString();
        tmp.signature = query.value(8).toString();
        tmp.remark = query.value(9).toString();
        tmp.time = query.value(10).toString();

        product_table->insertRow((product_table->rowCount()));

        //        product_table->setItem(i,0,new QTableWidgetItem(id));
        product_table->setItem(i,0,new QTableWidgetItem(tmp.name));
        product_table->setItem(i,1,new QTableWidgetItem(tmp.state));
        product_table->setItem(i,2,new QTableWidgetItem(tmp.amount));
        product_table->setItem(i,3,new QTableWidgetItem(tmp.price));
        product_table->setItem(i,4,new QTableWidgetItem(tmp.total_price));
        product_table->setItem(i,5,new QTableWidgetItem(tmp.controller));
        product_table->setItem(i,6,new QTableWidgetItem(tmp.signature));
        product_table->setItem(i,7,new QTableWidgetItem(tmp.remark));
        product_table->setItem(i,8,new QTableWidgetItem(tmp.time));
        i++;
    }
    //    product_table->resizeColumnToContents(0);  // 根据内容自动调整行宽和列宽

}

bool ContentWidget::sqladd(storage_t tmp)
{

    int i = -1;
    QSqlQuery querylist;
    qDebug() <<	querylist.exec(QString("select * from sql_storage_table where name=\"") + tmp.name +"\";");
    while(querylist.next())
    {
        i++;
    }
    //	qDebug() << i;
    if(i != -1){
        qDebug() << tmp.name << "is aready exits";
        QMessageBox msgBox;
        msgBox.setText(QString("添加商品 %1").arg(E_name->text()));
        msgBox.setInformativeText("库存中已有该名称商品");
        msgBox.setIconPixmap(QPixmap(":/img/safe"));
        msgBox.exec();
        return false;
    } else{
        //        qDebug() << "create " << querylist.exec("create table storage (id integer primary key,name varchar(45),price varchar(20),amount varchar(20),controller varchar(20),time varchar(20))");//创建表,已经创建
        qDebug() << QString("insert into sql_storage_table (name,state,amount,price,total_price,controller,remark,time)values('" \
                            + tmp.name+ "','"+ tmp.amount + "','" + tmp.state + "','"  + tmp.price + "','" + tmp.total_price  + "','" +  tmp.controller +  "','" + tmp.remark +  "','" +  tmp.time + "')");

        if(!querylist.exec(QString("insert into sql_storage_table (name,state,amount,price,total_price,controller,remark,time)values('" \
                                   + tmp.name+ "','"+  tmp.state + "','" + tmp.amount + "','"   + tmp.price + "','" + tmp.total_price  + "','" +  tmp.controller +  "','" + tmp.remark +  "','" +  tmp.time + "')")))
        {
            QMessageBox msgBox;
            msgBox.setText("数据库添加内容失败");
            msgBox.setInformativeText("请联系管理员");
            msgBox.setIconPixmap(QPixmap(":/img/safe"));
            msgBox.exec();
            return false;
        }else{
            storage_t p_tmp;
            p_tmp = sqlsearch(tmp);
            product_add(p_tmp);
        }
        tabShow();
    }
    //        query.exec("insert into storage (name,count,remark)values('姓名',101,'备注')");
}
void ContentWidget::sqlcancel()
{
    storage_t s_tmp;
    qDebug() << product_table->item(sql_x,1)->text();

    QMessageBox msgBox;
    msgBox.setText(QString("确定取消商品 %1 的 %2 操作").arg(product_table->item(sql_x,0)->text(),product_table->item(sql_x,1)->text()));
    msgBox.setInformativeText("确认操作？");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes:
    {
        if(product_table->item(sql_x,1)->text() == "新添加")
        {
            QSqlQuery querylist;
            qDebug() <<	"delete" << querylist.exec(QString("delete from sql_storage_table WHERE name='" + product_table->item(sql_x,0)->text()+ "'"));
            qDebug() <<	"delete" << querylist.exec(QString("delete from sql_product_table WHERE name='" + product_table->item(sql_x,0)->text()+ "'"));

            back_1();
            //            tabShow();
            //            goto
            break;
        }else if(product_table->item(sql_x,1)->text() == "入库")
        {
            s_tmp.name = product_table->item(sql_x,0)->text();
            s_tmp.amount = product_table->item(sql_x,2)->text();
            s_tmp.controller = product_table->item(sql_x,5)->text();
            s_tmp.signature = product_table->item(sql_x,6)->text();
            s_tmp.remark = product_table->item(sql_x,7)->text();
            s_tmp.time = gettime();
            s_tmp.state = "取消入库操作";
            sqlminus(s_tmp);
        }else if(product_table->item(sql_x,1)->text() == "出库")
        {
            s_tmp.name = product_table->item(sql_x,0)->text();
            s_tmp.amount = product_table->item(sql_x,2)->text();
            s_tmp.price = product_table->item(sql_x,3)->text();
            s_tmp.controller = product_table->item(sql_x,5)->text();
            s_tmp.signature = product_table->item(sql_x,6)->text();
            s_tmp.remark = product_table->item(sql_x,7)->text();
            s_tmp.time = gettime();
            s_tmp.state = "取消入库操作";
            sqlminus(s_tmp);

        }else {

        }

        //        QSqlQuery querylist;
        //        qDebug() <<	"delete" << querylist.exec(QString("delete from sql_storage_table WHERE name='" + storage_table->item(sql_x,1)->text()+ "'"));
        //        qDebug() <<	"delete" << querylist.exec(QString("delete from sql_product_table WHERE name='" + storage_table->item(sql_x,1)->text()+ "'"));

        //        tabShow();
        break;
    }
    case QMessageBox::No:

        break;
    default:

        break;
    }
}

void ContentWidget::sqldelete()
{
    if(sql_x < 0)
    {

        QMessageBox message(QMessageBox::NoIcon, "提示", "请先选中一件库存商品");
        message.setIconPixmap(QPixmap(":/img/safe"));
        message.exec();
        return;
    }
    QMessageBox msgBox;
    msgBox.setText(QString("你选中了 %1").arg(storage_table->item(sql_x,1)->text()));
    msgBox.setInformativeText("确定彻底删除？");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes:
    {
        QSqlQuery querylist;
        qDebug() <<	"delete" << querylist.exec(QString("delete from sql_storage_table WHERE name='" + storage_table->item(sql_x,1)->text()+ "'"));
        qDebug() <<	"delete" << querylist.exec(QString("delete from sql_product_table WHERE name='" + storage_table->item(sql_x,1)->text()+ "'"));

        tabShow();
        break;
    }
    case QMessageBox::No:

        break;
    default:

        break;
    }
}

bool ContentWidget::sqlupdate(storage_t tmp)
{
    QSqlQuery querylist;
    qDebug() << QString("UPDATE sql_storage_table SET amount='" + tmp.amount + "',total_price ='"  + tmp.total_price + "',price ='"  + tmp.price + "' WHERE name='" + tmp.name+ "'");
    return querylist.exec(QString("UPDATE sql_storage_table SET amount='" + tmp.amount + "',total_price ='"  + tmp.total_price + "',price ='"  + tmp.price +  "' WHERE name='" + tmp.name+ "'"));
    //    qDebug() <<	"update" << querylist.exec(QString("update storage set amount = \'"+ tmp.amount + "\' where name= \"" + tmp.name));

}

storage_t ContentWidget::sqlsearch(storage_t tmp)
{
    //name   ,amount   ,state   ,price   ,total_price   ,controller   ,remark   ,time
    int i = -1;
    QSqlQuery querylist;
    qDebug() <<	querylist.exec(QString("select * from sql_storage_table where name=\"") + tmp.name +"\";");
    while(querylist.next())
    {
        i++;
        tmp.v_id = querylist.value(0).toString();
        tmp.name = querylist.value(1).toString();

        tmp.state = querylist.value(2).toString();
        tmp.amount = querylist.value(3).toString();
        tmp.price = querylist.value(4).toString();
        tmp.total_price = querylist.value(5).toString();
        tmp.controller = querylist.value(6).toString();
        tmp.remark = querylist.value(7).toString();
        tmp.time = querylist.value(8).toString();
    }
    if(i != -1){
        qDebug() << "get your search name " << tmp.name;
        return tmp;
    } else{
        tmp.name = "";
        return tmp;
    }
}

bool ContentWidget::sqlminus(storage_t tmp_tmp)
{
    qDebug() << tmp_tmp.name << tmp_tmp.state  << tmp_tmp.amount;
    storage_t tmp;
    int count = -1;
    tmp = sqlsearch(tmp_tmp);
    count = tmp.amount.toInt() - tmp_tmp.amount.toInt();
    if(count  < 0){
        showwidget(4,QString("商品 %1 库存不足 %2 件").arg(tmp_tmp.name,tmp_tmp.amount));
        qDebug() << "库余不足 " << tmp_tmp.amount;
    }else {
        tmp.amount = QString::number(count,10);
        //        tmp.total_price = QString::number((count * tmp.price.toInt()),10);
        tmp.total_price = gmpmath->math(tmp.amount,"*",tmp.price);

        //        tmp_tmp.total_price = QString::number((tmp_tmp.amount.toInt() * tmp.price.toInt()),10);
        if(tmp_tmp.price == ""){
            tmp_tmp.total_price = gmpmath->math(tmp_tmp.amount,"*",tmp.price);
        }else {
            tmp_tmp.total_price = gmpmath->math(tmp_tmp.amount,"*",tmp_tmp.price);
        }
        qDebug() << tmp.amount;
        if(sqlupdate(tmp)){
            tabShow();
            //            tmp_tmp.state = "出库";
            product_add(tmp_tmp);
        }else {
            qDebug() << "minus update error";
        }
    }
    return true;
}

bool ContentWidget::sqlplus(storage_t tmp_tmp)
{
    qDebug() << tmp_tmp.name << tmp_tmp.state << tmp_tmp.amount;
    storage_t tmp;
    int count = -1;
    tmp = sqlsearch(tmp_tmp);
    count = tmp.amount.toInt() + tmp_tmp.amount.toInt();

    tmp.amount = QString::number(count,10);


    //    tmp.total_price = QString::number((tmp.total_price.toInt() + tmp_tmp.amount.toInt()* tmp_tmp.price.toInt()),10);
    //    tmp.price = QString::number(tmp.total_price.toInt()/count,10);
    //    tmp_tmp.total_price = QString::number(tmp_tmp.amount.toInt() * tmp_tmp.price.toInt(),10);

    tmp.total_price = gmpmath->math(tmp.total_price,"+",gmpmath->math(tmp_tmp.amount,"*",tmp_tmp.price));
    tmp.price = gmpmath->math(tmp.total_price,"/",tmp.amount);
    tmp_tmp.total_price = gmpmath->math(tmp_tmp.amount,"*",tmp_tmp.price);




    qDebug() << tmp.amount;
    if(sqlupdate(tmp)){
        tabShow();
        //        tmp_tmp.state = "入库";
        product_add(tmp_tmp);
    }else {

        qDebug() << "plus update file";
    }
    return true;
}

bool ContentWidget::sqlInit(bool INIT)
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sql/nbut.zh"); // 数据库名与路径, 此时是放在同目录下
    if(!db.open()){ // 连接数据库, 然后就可以使用了
        qDebug() << "sql open error";
        return false;
    }

    QSqlQuery query;
    qDebug() << "drop table" << query.exec("DROP TABLE sql_users_table");
    qDebug() << "create users table" <<  query.exec("create table sql_users_table (id integer primary key,user_name varchar(45),user_passwd varchar(20))");
    qDebug() << "insert sql_users_table table" << query.exec(QString("insert into sql_users_table (user_name,user_passwd)values('admin','123456')"));

    //    if(!querylist.exec(QString("insert into sql_storage_table (name,state,amount,price,total_price,controller,remark,time)values('" \
    //                               + tmp.name+ "','"+  tmp.state + "','" + tmp.amount + "','"   + tmp.price + "','" + tmp.total_price  + "','" +  tmp.controller +  "','" + tmp.remark +  "','" +  tmp.time + "')")))



    //    query.exec("create table sql_storage_table (id integer primary key,name varchar(45),state varchar(20),amount varchar(20),price varchar(20),total_price varchar(20),controller varchar(20),remark varchar(100),time varchar(20))");
    //    query.exec("create table sql_product_table (id integer primary key,v_id varchar(15),name varchar(45),state varchar(20),amount varchar(20),price varchar(20),total_price varchar(20),controller varchar(20),signature varchar(20),remark varchar(100),time varchar(20))");
    if(INIT){
        if(query.exec("DROP TABLE sql_storage_table")){
            if(query.exec("DROP TABLE sql_product_table")){
                if(query.exec("create table sql_storage_table (id integer primary key,name varchar(45),state varchar(20),amount varchar(20),price varchar(20),total_price varchar(20),controller varchar(20),remark varchar(100),time varchar(20))"))    //创建表,已经创建
                {
                    if(query.exec("create table sql_product_table (id integer primary key,v_id varchar(15),name varchar(45),state varchar(20),amount varchar(20),price varchar(20),total_price varchar(20),controller varchar(20),signature varchar(20),remark varchar(100),time varchar(20))"))
                    {

                        return true;
                    }else{
                        qDebug() << "create table sql_product_table error";
                        return false;
                    }
                }else {
                    qDebug() << "create table sql_product_table error";
                    return false;
                }

            }
            else{
                return false;
            }
        }else {
            return false;
        }


    }else {

    }
    //    qDebug() << "create sql table " << query.exec("create table sql_product_table (id integer primary key,v_id varchar(15),name varchar(45),state varchar(20),amount varchar(20),price varchar(20),total_price varchar(20),controller varchar(20),signature varchar(20),remark varchar(100),time varchar(20))"); //创建表,已经创建
}

void ContentWidget::tabShow()
{
    search_page = false;

    QSqlQuery query;
    storage_t tmp;
    QString id;
    int count_id = 0;
    tmp.total_amount = 0;
    tmp.f_total_price = "0";

    //    query.exec("create table sql_storage_table (id integer primary key,name varchar(20),count int,remark varchar(255))");//创建表,已经创建

    query.exec("select count(*) from sql_storage_table");
    //    query.exec("select count(id) as iCount from sql_storage_table_table");
    //查询数据库里记录数量
    //    query.exec("select * from sql_storage_table_table");
    int amount = 0;//记录总数
    if (query.next())
    {
        amount=query.value(0).toInt();
    }
    query.exec("select * from sql_storage_table order by id desc");
    storage_table->setRowCount(0);
    storage_table->setRowCount(amount + 2);//设置表格有多少行
    int i=0;
    while(query.next())
    {
        if(i == 0)
        {
            count_id = query.value(0).toInt();
        }
        //        labels << tr("序号") << tr("商品") << tr("状态") <<  tr("件数") << tr("单品价格") << tr("总价") << tr("管理员")<< tr("备注") << tr("时间");
        id = query.value(0).toString();
        tmp.name = query.value(1).toString();
        tmp.state = query.value(2).toString();
        tmp.amount = query.value(3).toString();
        tmp.price = query.value(4).toString();
        tmp.total_price = query.value(5).toString();
        tmp.controller = query.value(6).toString();
        //        tmp.signature = tmp.at(4);
        tmp.remark = query.value(7).toString();
        tmp.time = query.value(8).toString();



        tmp.total_amount += tmp.amount.toInt();
        //        tmp.f_total_price += tmp.total_price.toInt();
        tmp.f_total_price = gmpmath->math(tmp.total_price,"+",tmp.f_total_price);

        storage_table->setItem(i,0,new QTableWidgetItem(id));
        storage_table->setItem(i,1,new QTableWidgetItem(tmp.name));
        storage_table->setItem(i,2,new QTableWidgetItem(tmp.state));
        storage_table->setItem(i,3,new QTableWidgetItem(tmp.amount));
        storage_table->setItem(i,4,new QTableWidgetItem(tmp.price));
        storage_table->setItem(i,5,new QTableWidgetItem(tmp.total_price));
        storage_table->setItem(i,6,new QTableWidgetItem(tmp.controller));
        storage_table->setItem(i,7,new QTableWidgetItem(tmp.remark));
        storage_table->setItem(i,8,new QTableWidgetItem(tmp.time));
        i++;
    }
    i++;
    storage_table->setItem(i,0,new QTableWidgetItem("总计"));
    storage_table->setItem(i,1,new QTableWidgetItem(QString::number(i - 1,10)));
    storage_table->setItem(i,2,new QTableWidgetItem("总件数"));
    storage_table->setItem(i,3,new QTableWidgetItem(QString::number(tmp.total_amount,10)));
    storage_table->setItem(i,4,new QTableWidgetItem("总金额"));
    storage_table->setItem(i,5,new QTableWidgetItem(tmp.f_total_price));
    //    storage_table->setItem(i,6,new QTableWidgetItem(tmp.controller));
    //    storage_table->setItem(i,7,new QTableWidgetItem(tmp.remark));
    storage_table->setItem(i,8,new QTableWidgetItem(gettime()));
}

QString ContentWidget::gettime()
{
    QDateTime DateTime;
    QTime Time;
    QDate Date;
    DateTime = QDateTime::currentDateTime();
    Time = DateTime.time();
    Date = DateTime.date();
    return (Date.toString("yyyy-MMdd") + "/" + Time.toString("hh:mm"));

}

void ContentWidget::resizeEvent(QResizeEvent *event)
{
    //	QWidget::resizeEvent(event);
    qDebug() << "resizeEvent;" << this->height() << this->width();
    for(int i = 0;i < 9;i ++){
        product_table->setColumnWidth(i,(this->width())/9);
        storage_table->setColumnWidth(i,(this->width())/9);
        //        product_table->horizontalHeader()->setResizeMode();
    }
    //    product_table->resizeColumnToContents(0);  // 根据内容自动调整行宽和列宽
    //    storage_table->resizeColumnToContents(0);  // 根据内容自动调整行宽和列宽
}

void ContentWidget::setProductTab()
{
    product_table->setFrameShape(QFrame::NoFrame);  //无边框
    product_table->setAutoScroll(false);
    product_table->setShowGrid(false); //设置不显示格子线
    product_table->setColumnCount(9);
    product_table->setMouseTracking(true);
    product_table->setSelectionMode(QAbstractItemView::SingleSelection);
    product_table->setSelectionBehavior(QAbstractItemView::SelectRows); //line to choose
    for(int i = 0;i < 9;i ++){
        product_table->setColumnWidth(i,900/9);
        //        product_table->horizontalHeader()->setResizeMode();
    }

    product_table->verticalHeader()->setVisible(false);
    product_table->horizontalHeader()->setVisible(true);
    product_table->setEditTriggers ( QAbstractItemView::NoEditTriggers ); // no edit
    product_table->setAlternatingRowColors(true);  //奇偶行底色不同


    QStringList labels;
    labels << tr("商品") << tr("操作") <<  tr("件数") << tr("单品价格") << tr("总金额") << tr("管理员")<<  tr("签字人") << tr("备注") << tr("时间");
    product_table->setHorizontalHeaderLabels(labels);
    product_table->setRowCount(0);

    connect(product_table,SIGNAL(cellClicked(int,int)),this,SLOT(product_table_clicked(int,int)));
}

void ContentWidget::setStorageTab()
{
    storage_table->setFrameShape(QFrame::NoFrame);  //无边框
    storage_table->setAutoScroll(false);
    storage_table->setShowGrid(false); //设置不显示格子线
    storage_table->setColumnCount(9);
    storage_table->setMouseTracking(true);
    storage_table->setSelectionMode(QAbstractItemView::SingleSelection);
    storage_table->setSelectionBehavior(QAbstractItemView::SelectRows); //line to choose
    for(int i = 0;i < 9;i ++){
        storage_table->setColumnWidth(i,900/9);
        //        product_table->horizontalHeader()->setResizeMode();
    }
    storage_table->verticalHeader()->setVisible(false);
    storage_table->horizontalHeader()->setVisible(true);
    storage_table->setEditTriggers ( QAbstractItemView::NoEditTriggers ); // no edit
    storage_table->setAlternatingRowColors(true);  //奇偶行底色不同

    storage_table->resizeColumnToContents(0);  // 根据内容自动调整行宽和列宽
    QStringList labels;
    labels << tr("序号") << tr("商品") << tr("状态") <<  tr("件数") << tr("单品价格") << tr("总价") << tr("管理员")<< tr("备注") << tr("时间");
    storage_table->setHorizontalHeaderLabels(labels);
    storage_table->setRowCount(0);

    connect(storage_table,SIGNAL(cellClicked(int,int)),this,SLOT(storage_table_clicked(int,int)));
}

void ContentWidget::setTabWidget()
{


    QVBoxLayout *test = new QVBoxLayout();
    test->addWidget(product_table);
    test->addWidget(storage_table);
    test->setSpacing(0);
    test->setContentsMargins(0, 0, 0, 0);
    main_widget->setLayout(test);

    storage_table->setHidden(false);
    product_table->setHidden(true);

}

void ContentWidget::product_table_clicked(int x, int y)
{
    sql_x = x;
    sql_y = y;
    btn_cancel->setEnabled(true);
}

void ContentWidget::storage_table_clicked(int x, int y)
{
    sql_x = x;
    sql_y = y;
    //    qDebug() << "table clicked " << x << "rowcount" << storage_table->rowCount();

    if(storage_table->rowCount() - x > 2 || search_page){
        btnEnable(true);
    }else {
        btnEnable(false);
    }
}

void ContentWidget::excelSave()
{
    if(!excelengine->Open("test.xls",1,false))
        qDebug() << "open xls error";
    if(tab_page){
        //        emit saveExecl(storage_table);
        if(!excelengine->SaveDataFrTable(storage_table)){
            qDebug() << "SaveDataFrTable error";
            showwidget(4,QString("导出 Excel 表格失败"));
        }
    }else {
        //        emit saveExecl(product_table);
        if(!excelengine->SaveDataFrTable(product_table)){
            qDebug() << "SaveDataFrTable error";
            showwidget(4,QString("导出 Excel 表格失败"));
        }
    }
    excelengine->Close();



    //    if(tab_page){
    //        tablewidget_map[1] = storage_table;
    ////        void saveExecl(QMap<int,QTableWidget *> tmp);
    //        emit saveExecl(tablewidget_map);
    ////        if(!excelengine->SaveDataFrTable(storage_table)){
    ////            qDebug() << "SaveDataFrTable error";
    ////            showwidget(4,QString("导出 Excel 表格失败"));
    ////        }
    //    }else {
    //        tablewidget_map[1] = product_table;
    //        emit saveExecl(tablewidget_map);
    ////        if(!excelengine->SaveDataFrTable(product_table)){
    ////            qDebug() << "SaveDataFrTable error";
    ////            showwidget(4,QString("导出 Excel 表格失败"));
    ////        }
    //    }
}

void ContentWidget::setToolsWidget()
{
    tools_widget = new QWidget(this);
    E_search = new QLineEdit();
    E_search->setFixedWidth(150);
    E_search->setPlaceholderText(QString("查找"));
    //    QLineEdit *QLedt2 = new QLineEdit();
    //    QLineEdit *QLedt3 = new QLineEdit();
    //    QLineEdit *QLedt4 = new QLineEdit();
    //    QLineEdit *QLedt5 = new QLineEdit();
    //    QLineEdit *QLedt6 = new QLineEdit();
    //    QLineEdit *QLedt7 = new QLineEdit();
    //    QLineEdit *QLedt8 = new QLineEdit();



    QSpacerItem *horizontalSpacer = new QSpacerItem(5000, 700, QSizePolicy::Expanding, QSizePolicy::Minimum);
    //    QSpacerItem *horizontalSpacer_1 = new QSpacerItem(5000, 700, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QPushButton *btn_search = new QPushButton("查找");

    btn_search->setFixedWidth(45);

    btn_plus = new QPushButton("入库");
    btn_minus= new QPushButton("出库");
    btn_add= new QPushButton("新增");
    btn_outinto = new QPushButton("导出");
    btn_delete = new QPushButton("删除");
    btn_cancel = new QPushButton("取消操作");
    btn_return = new QPushButton("返回总库");
    btn_detail = new QPushButton("详情");

    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->addItem(horizontalSpacer);
    h_layout->addWidget(E_search,0,Qt::AlignLeft);
    h_layout->addWidget(btn_search);
    ////    h_layout->addWidget(QLedt2);
    //    h_layout->addWidget(power_button2);
    ////    h_layout->addWidget(QLedt3);
    //    h_layout->addWidget(power_button3);
    ////    h_layout->addWidget(QLedt4);
    //    h_layout->addWidget(power_button4);
    h_layout->addStretch();
    h_layout->setSpacing(10);           //控件 与 控件之间的间隔距离
    h_layout->setContentsMargins(10, 0, 10, 0); // 左 上 右 下

    QHBoxLayout *h_layout1 = new QHBoxLayout();

    h_layout1->addWidget(btn_plus);
    h_layout1->addWidget(btn_minus);
    h_layout1->addWidget(btn_add);
    h_layout1->addWidget(btn_outinto);
    h_layout1->addWidget(btn_delete);
    h_layout1->addWidget(btn_cancel);
    h_layout1->addWidget(btn_detail);
    h_layout1->addWidget(btn_return);

    h_layout1->addStretch();
    h_layout1->setSpacing(10);
    h_layout1->setContentsMargins(0, 0, 0, 5);

    //    QLabel test2(tools_widget);
    //    test2.setText("12341234");
    QVBoxLayout *test = new QVBoxLayout();
    test->addLayout(h_layout);
    test->addLayout(h_layout1);
    test->setSpacing(0);
    test->setContentsMargins(0, 0, 0, 0);
    tools_widget->setLayout(test);

    connect(btn_search, SIGNAL(clicked()), this, SLOT(search()));
    connect(btn_return, SIGNAL(clicked()), this, SLOT(back_1()));
    connect(btn_detail, SIGNAL(clicked()), this, SLOT(detail_1()));
}

void ContentWidget::back_1()
{
    this->tabShow();
    btnEnable(false);
    btn_add->setEnabled(true);
    storage_table->setHidden(false);
    product_table->setHidden(true);
    tab_page = true;
}

void ContentWidget::detail_1()
{
    storage_t tmp;
    tmp.name = storage_table->item(sql_x,1)->text();
    product_show(tmp);
    storage_table->setHidden(true);
    product_table->setHidden(false);
    btn_add->setEnabled(false);
    btnEnable(false);
    tab_page = false;
}

void ContentWidget::search()
{
    btnEnable(false);
    qDebug() << "ContentWidget::search";
    QSqlQuery query;
    storage_t tmp;
    query.exec("select count(*) from sql_storage_table");
    //    query.exec("select count(id) as iCount from sql_storage_table");
    //查询数据库里记录数量

    int amount;//记录总数
    if (query.next())
    {
        amount=query.value(0).toInt();
    }
    query.exec("select * from sql_storage_table order by id desc");
    //    query.exec(QString("select * from sql_storage_table where name=\'") + E_search->text() +"'");
    //         query.exec("select * from sql_storage_table");
    storage_table->setRowCount(0);//设置表格有多少行
    int i=0;
    while(query.next())
    {

        QString id = query.value(0).toString();
        tmp.name =  query.value(1).toString();
        if(tmp.name.contains(E_search->text())){
            storage_table->insertRow((storage_table->rowCount()));

            tmp.state = query.value(2).toString();
            tmp.amount = query.value(3).toString();
            tmp.price = query.value(4).toString();
            tmp.total_price = query.value(5).toString();
            tmp.controller = query.value(6).toString();
            tmp.remark = query.value(7).toString();
            tmp.time = query.value(8).toString();

            storage_table->setItem(i,0,new QTableWidgetItem(id));
            storage_table->setItem(i,1,new QTableWidgetItem(tmp.name));
            storage_table->setItem(i,2,new QTableWidgetItem(tmp.state));
            storage_table->setItem(i,3,new QTableWidgetItem(tmp.amount));
            storage_table->setItem(i,4,new QTableWidgetItem(tmp.price));
            storage_table->setItem(i,5,new QTableWidgetItem(tmp.total_price));
            storage_table->setItem(i,6,new QTableWidgetItem(tmp.controller));
            storage_table->setItem(i,7,new QTableWidgetItem(tmp.remark));
            storage_table->setItem(i,8,new QTableWidgetItem(tmp.time));

            i++;
        }
    }
    if(i == 0){
        QMessageBox message(QMessageBox::NoIcon, "提示", QString("库存中没有包含 %1 %2").arg(E_search->text(),"的商品"));
        message.setIconPixmap(QPixmap(":/img/safe"));
        message.exec();
        tabShow();
    }else {
        //        tabShow();
        search_page = true;
        storage_table->setHidden(false);
        product_table->setHidden(true);
    }
}


void ContentWidget::slotStyleChange(int StyleString)     //透明度
{
    QFile file0("skin//style0.qss");
    QFile file1("skin//style1.qss");
    QFile file2("skin//style2.qss");
    QFile file3("skin//style3.qss");
    QFile file4("skin//style4.qss");
    QFile file5("skin//style5.qss");

    QSettings *settings;
    settings = new QSettings("muyi","storage");
    QString styleSheet;
    switch(StyleString)
    {
    case 0:
        file0.open(QFile::ReadOnly);
        styleSheet = QLatin1String(file0.readAll());
        this->setStyleSheet(styleSheet);
        file0.close();
        settings->setValue( "skin", 0);
        break;
    case 1:
        file1.open(QFile::ReadOnly);
        styleSheet = QLatin1String(file1.readAll());
        this->setStyleSheet(styleSheet);
        file1.close();
        settings->setValue( "skin", 1);
        break;
    case 2:

        file2.open(QFile::ReadOnly);
        styleSheet = QLatin1String(file2.readAll());
        this->setStyleSheet(styleSheet);
        file2.close();
        settings->setValue( "skin", 2);
        break;
    case 3:
        file3.open(QFile::ReadOnly);
        styleSheet = QLatin1String(file3.readAll());
        this->setStyleSheet(styleSheet);
        file3.close();
        settings->setValue( "skin", 3);
        break;
    case 4:
        file4.open(QFile::ReadOnly);
        styleSheet = QLatin1String(file4.readAll());
        this->setStyleSheet(styleSheet);
        file4.close();
        settings->setValue( "skin", 4);
        break;
    case 5:
        file5.open(QFile::ReadOnly);
        styleSheet = QLatin1String(file5.readAll());
        this->setStyleSheet(styleSheet);
        file5.close();
        settings->setValue( "skin", 5);
        break;
    default:
        break;
    }
}







//    //    QLabel * lab = new QLabel();
//    //    lab->setText("test by acanoe");
//        storage_table = new QTableWidget(this);
//    //    storage_table = new QTableWidget();
//    //    layout2p1 -> addWidget(storage_table);
//    //    storage_table->setHidden(true);

//        //	qDebug() << Tab_user->width() << Tab_user->height();
//    //    storage_table->setFrameShape(QFrame::NoFrame);  //无边框
//    //    storage_table->setAutoScroll(false);
//    //    storage_table->setShowGrid(false); //设置不显示格子线
//        storage_table->setColumnCount(10);
//    //    storage_table->setMouseTracking(true);
//    ////    storage_table->verticalHeader()->setDefaultSectionSize(30);
//    //    storage_table->setSelectionMode(QAbstractItemView::SingleSelection);
//    //    //	storage_table->setSelectionBehavior(QAbstractItemView::SelectRows); //line to choose
//    //    //	storage_table->setColumnWidth(0,30);
//    ////    storage_table->verticalHeader()->setVisible(false);
//            storage_table->horizontalHeader()->setVisible(true);
//    //    //	storage_table->setEditTriggers ( QAbstractItemView::NoEditTriggers ); // no edit
//    //    storage_table->setAlternatingRowColors(true);  //奇偶行底色不同
//    //    QStringList labels;
//    //    labels << tr("姓名") << tr("管辖范围") << tr("维护单位") << tr("创建人") << tr("工作单位")<< tr("职务")<< tr("所属用户组")<< tr("电话")<< tr("手机")<< tr("操作");
//    //    storage_table->setHorizontalHeaderLabels(labels);
//        storage_table->setRowCount(20);

//    ////    QPushButton * pBtn = new QPushButton ("继续添加");
//    ////    QPushButton * pBtn1 = new QPushButton ("完成");
//    ////    QPushButton * pBtn2 = new QPushButton ("取消");
//    ////    connect(pBtn, SIGNAL(clicked()), this, SLOT(addAgain()));
//    ////    connect(pBtn1, SIGNAL(clicked()), this, SLOT(addFinish()));
//    ////    connect(pBtn2, SIGNAL(clicked()), this, SLOT(addCancel()));
//    ////    storage_table->setCellWidget(1,0,pBtn);
//    ////    storage_table->setCellWidget(1,1,pBtn1);
//    ////    storage_table->setCellWidget(1,2,pBtn2);

//    //    for(int z = 0; z < 10; z++){
//    //        storage_table->setItem(0,z,new QTableWidgetItem());
//    //    }

//        storage_table->setItem(0,0,new QTableWidgetItem("acanoe"));
//        storage_table->setItem(0,1,new QTableWidgetItem("acanoe11"));
//        excelengine = new ExcelEngine;
//    //    if(!excelengine->Open("D:\\code\\svn\\acanoe_brower\\testnew.xls",1,false))
//        if(!excelengine->Open("test.xls",1,false))
//            qDebug() << "open xls error";

//        QSqlDatabase db;
//        db = QSqlDatabase::addDatabase("QSQLITE");
//        db.setDatabaseName("sql/nbut.zh"); // 数据库名与路径, 此时是放在同目录下
//        qDebug() <<  "open sql" << db.open(); // 连接数据库, 然后就可以使用了
//        QSqlQuery query;
//    //    query.exec("create table storage (id integer primary key,name varchar(20),count int,remark varchar(255))");//创建表,已经创建
//        query.exec("insert into storage (name,count,remark)values('姓名',101,'备注')");
//    //    query.exec("select count(*) from sql_storage_table");
//        query.exec("select count(id) as iCount from sql_storage_table");
//        //查询数据库里记录数量
//        int amount;//记录总数
//        if (query.next())
//        {
//            amount=query.value(0).toInt();
//        }
//        query.exec("select * from sql_storage_table order by id desc");
//        storage_table->setRowCount(amount);//设置表格有多少行
//        int i=0;
//        while(query.next())
//        {
//            int id=query.value(0).toInt();
//            QString name=query.value(1).toString();
//            int count=query.value(2).toInt();
//            QString remark=query.value(3).toString();

//            storage_table->setItem(i,0,new QTableWidgetItem(QString::number(id)));
//            storage_table->setItem(i,1,new QTableWidgetItem(name));
//            storage_table->setItem(i,2,new QTableWidgetItem(QString::number(count)));
//            storage_table->setItem(i,3,new QTableWidgetItem(remark));
//            i++;
//        }


//    //    sqlapi = new SqlApi;
//    //    if(!excelengine->ReadDataToTable(storage_table))
//    //        qDebug() << "ReadDataToTable error";

//    //    if(!excelengine->SaveDataFrTable(storage_table)){
//    //        qDebug() << "SaveDataFrTable error";
//    //    }
//        excelengine->Close();



//    setMinimumSize(900, 500);
