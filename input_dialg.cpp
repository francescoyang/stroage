
#include <QPalette>
#include <QLineEdit>
#include <QSqlQuery>


#include "about_us.h"

AboutUsDialog::AboutUsDialog(QWidget *parent,int index_tmp,QString name_tmp)
    :QDialog(parent)
{

    this->resize(520, 290);
    index = index_tmp;
    name = name_tmp;
    qDebug() << index << name;

    QPalette palette;
    this->setAutoFillBackground(true);
    palette.setColor(QPalette::Background,QColor(155,225,123));
    this->setPalette(palette);


    //初始化为未按下鼠标左键
    mouse_press = false;

    //设置标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    title_label = new QLabel();
    title_icon_label = new QLabel();
    title_info_label = new QLabel();
    info_label = new QLabel();
    version_label = new QLabel();
    mummy_label = new QLabel();
    copyright_label = new QLabel();
    icon_label = new QLabel();
    close_button = new PushButton();
    ok_button = new QPushButton();

    QPixmap title_pixmap(":/img/safe");
    title_icon_label->setPixmap(title_pixmap);
    title_icon_label->setFixedSize(16, 16);
    title_icon_label->setScaledContents(true);

    close_button->loadPixmap(":/sysButton/close");

    title_label->setFixedHeight(30);
    ok_button->setFixedSize(75, 25);
    QPixmap pixmap(":/img/360safe");
    icon_label->setPixmap(pixmap);
    icon_label->setFixedSize(pixmap.size());

    QFont title_info_font("微软雅黑", 20, QFont::Bold, false);


    QHBoxLayout *input1 = new QHBoxLayout();
    QHBoxLayout *input2 = new QHBoxLayout();
    QHBoxLayout *input3 = new QHBoxLayout();
    switch(index_tmp){
    case 1:
    {
        QLabel *L_name = new QLabel(tr("商品名 "));
        E_name = new QLineEdit;

        QLabel *L_Price = new QLabel(tr("商品价格"));
        E_Price = new QLineEdit;

        QLabel *L_amount = new QLabel(tr("数量   "));
        E_amount = new QLineEdit;

        QLabel *L_person = new QLabel(tr("管理员  "));
        E_person = new QLineEdit;

        QLabel *L_sign = new QLabel(tr("签字人 "));
        E_sign = new QLineEdit;

        QLabel *L_remark = new QLabel(tr("备注   "));
        E_remark = new QLineEdit;



        input1->addWidget(L_name);
        input1->addWidget(E_name);
        input1->addWidget(L_Price);
        input1->addWidget(E_Price);
        input1->setSpacing(10);
        input1->setContentsMargins(10, 0, 10, 0);


        input2->addWidget(L_amount);
        input2->addWidget(E_amount);
        input2->addWidget(L_person);
        input2->addWidget(E_person);
        input2->setSpacing(10);
        input2->setContentsMargins(10, 0, 10, 0);

        input3->addWidget(L_sign);
        input3->addWidget(E_sign);
        input3->addWidget(L_remark);
        input3->addWidget(E_remark);
        input3->setSpacing(10);
        input3->setContentsMargins(10, 0, 10, 0);
        break;
    }
    case 2:
    {
        QLabel *L_name = new QLabel(QString("商品 ") + name + " 出库");
        L_name ->setFont(title_info_font);
        E_name = new QLineEdit;

        //        QLabel *L_Price = new QLabel(tr("商品价格"));
        //        E_Price = new QLineEdit;

        QLabel *L_amount = new QLabel(tr("数量   "));
        E_amount = new QLineEdit;

        QLabel *L_person = new QLabel(tr("管理员  "));
        E_person = new QLineEdit;

        QLabel *L_sign = new QLabel(tr("签字人 "));
        E_sign = new QLineEdit;

        QLabel *L_remark = new QLabel(tr("备注   "));
        E_remark = new QLineEdit;

        input1->addWidget(L_name);
        //        input1->addWidget(E_name);
        //        input1->addWidget(L_Price);
        //        input1->addWidget(E_Price);
        input1->setSpacing(10);
        input1->setContentsMargins(10, 0, 10, 0);

        input2->addWidget(L_amount);
        input2->addWidget(E_amount);
        input2->addWidget(L_person);
        input2->addWidget(E_person);
        input2->setSpacing(10);
        input2->setContentsMargins(10, 0, 10, 0);


        input3->addWidget(L_sign);
        input3->addWidget(E_sign);
        input3->addWidget(L_remark);
        input3->addWidget(E_remark);
        input3->setSpacing(10);
        input3->setContentsMargins(10, 0, 10, 0);
        break;
    }
    case 3:
    {
        QLabel *L_name = new QLabel(QString("商品 ") + name + " 入库");
        L_name ->setFont(title_info_font);
        E_name = new QLineEdit;

        QSpacerItem *horizontalSpacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
        QLabel *L_Price = new QLabel(tr("入库价格"));
        E_Price = new QLineEdit;

        QLabel *L_amount = new QLabel(tr("数量   "));
        E_amount = new QLineEdit;

        QLabel *L_person = new QLabel(tr("管理员  "));
        E_person = new QLineEdit;

        QLabel *L_sign = new QLabel(tr("签字人 "));
        E_sign = new QLineEdit;

        QLabel *L_remark = new QLabel(tr("备注   "));
        E_remark = new QLineEdit;




        input1->addWidget(L_name);
        //        input1->addWidget(E_name);
        input1->addItem(horizontalSpacer);
        input1->addWidget(L_Price);
        input1->addWidget(E_Price);
        input1->setSpacing(10);
        input1->setContentsMargins(10, 0, 10, 0);


        input2->addWidget(L_amount);
        input2->addWidget(E_amount);
        input2->addWidget(L_person);
        input2->addWidget(E_person);
        input2->setSpacing(10);
        input2->setContentsMargins(10, 0, 10, 0);

        input3->addWidget(L_sign);
        input3->addWidget(E_sign);
        input3->addWidget(L_remark);
        input3->addWidget(E_remark);
        input3->setSpacing(10);
        input3->setContentsMargins(10, 0, 10, 0);
        break;
    }
    case 4:
    {
        QLabel *L_name = new QLabel();
        L_name->setText(name);
        L_name ->setFont(title_info_font);

        input2->addWidget(L_name);
        input2->setSpacing(10);
        input2->setContentsMargins(10, 0, 10, 0);
        break;
    }
    case 5:
    {
        QLabel *L_name = new QLabel();
        L_name->setText("请输入管理员密码:");
        L_name ->setFont(title_info_font);
        E_Price = new QLineEdit;

        input2->addWidget(L_name);
        input2->addWidget(E_Price);
        input2->setSpacing(10);
        input2->setContentsMargins(10, 0, 10, 0);
        break;
    }
    case 6:
    {
        QLabel *L_name = new QLabel(tr("现在密码 "));
        E_name = new QLineEdit;

        QLabel *L_Price = new QLabel(tr("修改为 "));
        E_Price = new QLineEdit;

        QLabel *L_amount = new QLabel(tr("再次确认"));
        E_amount = new QLineEdit;

        input1->addWidget(L_name);
        input1->addWidget(E_name);
        input1->setSpacing(10);
        input1->setContentsMargins(10, 0, 10, 0);


        input2->addWidget(L_Price);
        input2->addWidget(E_Price );
        input2->setSpacing(10);
        input2->setContentsMargins(10, 0, 10, 0);

        input3->addWidget(L_amount);
        input3->addWidget(E_amount);
        input3->setSpacing(10);
        input3->setContentsMargins(10, 0, 10, 0);
        break;
    }


    default:
    {
        return;
    }
    }
    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(title_icon_label, 0, Qt::AlignVCenter);
    title_layout->addWidget(title_label, 0, Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
    title_layout->setSpacing(5);
    title_layout->setContentsMargins(10, 0, 5, 0);



    QHBoxLayout *bottom_layout = new QHBoxLayout();
    bottom_layout->addStretch();
    bottom_layout->addWidget(ok_button);
    bottom_layout->setSpacing(0);
    bottom_layout->setContentsMargins(0, 0, 30, 20);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(title_layout);
    main_layout->addStretch();      ///  添加格挡
    main_layout->addLayout(input1);
    main_layout->addStretch();
    main_layout->addLayout(input2);
    main_layout->addStretch();
    main_layout->addLayout(input3);
    main_layout->addStretch();
    main_layout->addLayout(bottom_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    setLayout(main_layout);

    title_label->setStyleSheet("color:white;");
    copyright_label->setStyleSheet("color:gray;");
    title_info_label->setStyleSheet("color:rgb(30,170,60);");
    info_label->setStyleSheet("color:rgb(30,170,60);");
    ok_button->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);}" "QPushButton:hover{border-color:green; background:transparent;}");



    QFont info_font = info_label->font();
    info_font.setBold(true);
    info_label->setFont(info_font);
    ok_button->setText(tr("OK"));

    connect(ok_button, SIGNAL(clicked()), this, SLOT(getinput()));
    connect(close_button, SIGNAL(clicked()), this, SLOT(hide()));
}

void AboutUsDialog::getinput()
{
    QStringList tmp;
    switch(index){
    case 1:
    {
        if(E_amount->text().toInt() == 0 ){
            E_amount->setText("数量必须为大于0的整数");
            return;
        }
        if(E_Price->text().toFloat() <= 0 ){
            E_Price->setText("单品价格必须是数字可以含小数");
            return;
        }
        tmp.append(E_name->text());
        tmp.append(E_Price->text());
        tmp.append(E_amount->text());
        tmp.append(E_person->text());
        tmp.append(E_sign->text());
        tmp.append(E_remark->text());

        emit setinput(tmp,index);
        break;
    }
    case 2:
        if(E_amount->text().toInt() == 0 ){
            E_amount->setText("数量必须为大于0的整数");
            return;
        }
        tmp.append(name);
        tmp.append(E_amount->text());
        tmp.append(E_person->text());
        tmp.append(E_sign->text());
        tmp.append(E_remark->text());
        emit setinput(tmp,index);
        break;
    case 3:
        if(E_amount->text().toInt() == 0 ){
            E_amount->setText("数量必须为大于0的整数");
            return;
        }
        if(E_Price->text().toFloat() <= 0 ){
            E_Price->setText("单品价格必须是数字可以含小数");
            return;
        }
        tmp.append(name);
        tmp.append(E_Price->text());
        tmp.append(E_amount->text());
        tmp.append(E_person->text());
        tmp.append(E_sign->text());
        tmp.append(E_remark->text());
        emit setinput(tmp,index);
        break;
    case 5:
    {
        //        QSqlQuery query;
        //        query.exec("create table sql_users_table (id integer primary key,user varchar(15),passwd varchar(100)");

        int i = 0;
        QSqlQuery querylist;
        //        qDebug() <<	querylist.exec(QString("select * from sql_users_table order by id desc"));
        qDebug() <<	querylist.exec(QString("select * from sql_users_table where user_name=\"admin\"" ));
        while(querylist.next())
        {
            i++;
            if(querylist.value(2).toString() == E_Price->text()){
                emit setinput(tmp,index);

            }else {
                E_Price->setText("密码错误");
                return;
            }
            //            tmp.v_id = querylist.value(0).toString();
            //            tmp.name = querylist.value(1).toString();

            //            tmp.state = querylist.value(2).toString();
            //            tmp.amount = querylist.value(3).toString();
            //            tmp.price = querylist.value(4).toString();
            //            tmp.total_price = querylist.value(5).toString();
            //            tmp.controller = querylist.value(6).toString();
            //            tmp.remark = querylist.value(7).toString();
            //            tmp.time = querylist.value(8).toString();
        }
        if(i == 0){
            E_Price->setText("密码错误");
            return;
        }
        break;
    }
    case 6:
    {
        int i = 0;
        QSqlQuery querylist;
        //        qDebug() <<	querylist.exec(QString("select * from sql_users_table order by id desc"));
        qDebug() <<	querylist.exec(QString("select * from sql_users_table where user_name=\"admin\"" ));
        while(querylist.next())
        {
            i++;
            if(querylist.value(2).toString() == E_name->text()){
                if(E_Price->text() == E_amount->text()){
                    if(querylist.exec(QString("UPDATE sql_users_table SET user_passwd='" + E_Price->text() + "' WHERE user_name='admin'")))
                    {
                        qDebug() << "change passwd is crrect";
                    }else{
                        E_Price->setText("密码数据更新失败");
                        qDebug() << "change passwd is error";
                        return;
                    }
                    emit setinput(tmp,index);
                }else {
                    E_amount->setText("输入不匹配，请重新输入");
                    return;
                }

            }else {
                E_name->setText("密码错误");
                return;
            }
            //            tmp.v_id = querylist.value(0).toString();
            //            tmp.name = querylist.value(1).toString();

            //            tmp.state = querylist.value(2).toString();
            //            tmp.amount = querylist.value(3).toString();
            //            tmp.price = querylist.value(4).toString();
            //            tmp.total_price = querylist.value(5).toString();
            //            tmp.controller = querylist.value(6).toString();
            //            tmp.remark = querylist.value(7).toString();
            //            tmp.time = querylist.value(8).toString();
        }
        break;
    }
    default:
        break;
    }

    this->close();
}

void AboutUsDialog::translateLanguage()
{


}

AboutUsDialog::~AboutUsDialog()
{

}

void AboutUsDialog::paintEvent(QPaintEvent *)
{
}

void AboutUsDialog::mousePressEvent( QMouseEvent * event )
{
    //只能是鼠标左键移动和改变大小
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }

    //窗口移动距离
    move_point = event->globalPos() - pos();
}

void AboutUsDialog::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void AboutUsDialog::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
    if(mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
    }
}
