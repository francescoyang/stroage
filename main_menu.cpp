#include "main_menu.h"

MainMenu::MainMenu(QWidget *widget)
    : QMenu(widget)
{
    this->createActions();
    this->translateActions();
}

void MainMenu::createActions()
{
    //创建菜单项
    action_sqlinit = new QAction(this);
    action_changepasswd = new QAction(this);
    action_sqlinit->setIcon(QIcon("img/safe.png"));

    //添加菜单项
    this->addAction(action_sqlinit);
    this->addAction(action_changepasswd);


    //设置信号连接
    QObject::connect(action_sqlinit, SIGNAL(triggered()), this, SIGNAL(sqlinit_signal()));
    QObject::connect(action_changepasswd, SIGNAL(triggered()), this, SIGNAL(changepasswd_signal()));
}

void MainMenu::translateActions()
{
    action_sqlinit->setText(tr("初始化数据库"));
    action_changepasswd->setText(tr("修改管理员密码"));
}
