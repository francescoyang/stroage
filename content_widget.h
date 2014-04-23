#ifndef CONTENT_WIDGET_H
#define CONTENT_WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>

#include "excelengine.h"
#include "sqlapi.h"
#include "configure.h"
#include "QSplitter"
#include "about_us.h"
#include "gmpmath.h"

//name   ,amount   ,state   ,price   ,total_price   ,controller   ,remark   ,time
typedef struct __storage_t{
    QString name;
    QString price;
    QString amount;
    QString total_price;
    QString state;
    QString controller;
    QString remark;
    QString v_id;
    QString signature;
    QString time;

    int total_goods;
    int total_amount;
    QString f_total_price;
}storage_t;

class ContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContentWidget(QWidget *parent = 0);
private:
    QMap<int,QTableWidget *> tablewidget_map;
    ExcelEngine *excelengine;
    QTableWidget *storage_table;
    QTableWidget *product_table;
    SqlApi *sqlapi;
    Configure *configure;

    QWidget *tools_widget;
    QWidget *main_widget;
    QWidget *left_widget;
    QWidget *show_widget;

    QSplitter *main_splitter;
    QSplitter *right_splitter;
    QSplitter *up_splitter;
    QSplitter *down_splitter;
    QSqlDatabase db;
    QPushButton *btn_plus;
    QPushButton *btn_minus;
    QPushButton *btn_add;
    QPushButton *btn_cancel;
    QPushButton *btn_outinto;
    QPushButton *btn_delete;
    QPushButton *btn_detail;
    QPushButton *btn_return;

    QLineEdit * E_name;
    QLineEdit * E_price;
    QLineEdit * E_amount;
    QLineEdit * E_controller;
    QLineEdit * E_search;

    AboutUsDialog * inputdialog;
    GmpMath *gmpmath;

    int sql_x;
    int sql_y;

    bool tab_page;          // table 切换标志
    bool search_page;       // 搜索页标志

    void setToolsWidget();
    void setTabWidget();
    void setProductTab();
    void setStorageTab();
    bool sqlInit(bool);


    bool sqlupdate(storage_t);
    void tabShow();
    bool sqlminus(storage_t);  // 出库
    void showwidget(int ,QString);
    void slotStyleChange(int StyleString);     //透明度
    QString gettime();
    void backup();

signals:
    void saveExecl(QMap<int,QTableWidget *>);
    
public slots:
    storage_t sqlsearch(storage_t);

    bool product_add(storage_t tmp);
    void product_show(storage_t tmp);
    bool sqlplus(storage_t tmp_tmp);   // 入库
    bool sqladd(storage_t);    // 新增商品
    void sqldelete(); // 删除商品
    void sqlcancel(); // 撤销操作
    void excelSave(); // 导出execl 表格

    void addwidget();
    void minuswidget();
    void pluswidget();
    void saveas();
    void product_table_clicked(int,int);
    void storage_table_clicked(int,int);
    void search();
    void back_1();
    void detail_1();
    void setinput(QStringList,int);
    void sqlinit_slot();
    void changepasswd_slot();
    void btnEnable(bool enabled);

protected:
    virtual void resizeEvent(QResizeEvent *event);
};

#endif // CONTENT_WIDGET_H
