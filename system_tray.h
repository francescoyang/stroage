#ifndef SYSYTEMTRAY_H
#define SYSYTEMTRAY_H

#include <QtGui>
#include <QSystemTrayIcon>
#include <QMenu>

class SystemTray : public QSystemTrayIcon
{
	Q_OBJECT

public:

	explicit SystemTray(QWidget *parent = 0);
	~SystemTray();
	void translateLanguage();

private:

	void createAction();

private:

	QMenu *tray_menu; //托盘菜单

	QAction *action_open; //打开360安全卫士
	QAction *action_help_center; //求助中心
	QAction *action_kill_mummy; //查杀木马
	QAction *action_clear; //清理垃圾
	QAction *action_optimize; //一键优化
	QAction *action_fireproof; //检查更新
	QAction *action_show_speed; //显示加速球
	QAction *action_soft_manage; //软件管家
	QAction *action_safe_notice; //安全通知
	QAction *action_rise; //升级
	QAction *action_login; //360用户登录
	QAction *action_separate; //隔离沙箱
	QAction *action_logout; //退出
private slots:
    void exitlog();

};

#endif //SYSYTEMTRAY_H
