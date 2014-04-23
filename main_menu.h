/**
* @文件名   main_menu.h
* @版本信息 copyright  2012-2013 Sugon. All rights reserved.
* @功能描述
*           MainMenu类包含主菜单，主要包括：关于我们、退出等
* @作者     王亮<wangliang@sugon.com>
* @日期     2012-01-07
*/

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMenu>

class MainMenu : public QMenu
{
    Q_OBJECT

public:

    explicit MainMenu(QWidget *parent = 0);

    void translateActions();

signals:

    void sqlinit_signal();
    void changepasswd_signal();

private:

    void createActions();

private:

    QAction *action_sqlinit; // 数据库初始化
    QAction *action_changepasswd;

    QAction *action_setting; //设置
    QAction *action_new_character; //新版特性
    QAction *action_check_update; //检查更新
    QAction *action_change_company; //切换为企业版
    QAction *action_help_online; //在线帮助
    QAction *action_platform_help; //论坛求助
    QAction *action_login_home; //360网站
    QAction *action_protect; //隐私保护
    QAction *action_about_us; //关于我们

};

#endif //MAINMENU_H
