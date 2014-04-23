#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QWidgets>
#include <QtGui>
#include <QSystemTrayIcon>

#include "main_menu.h"
#include "title_widget.h"
#include "content_widget.h"
#include "system_tray.h"


class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    TitleWidget *title_widget;
    ContentWidget *content_widget;
    SystemTray * systemtray;
    MainMenu * main_menu;

    void testTong();
    QRect location;
    void slotStyleChange(int StyleString);     //透明度
    void showWidget();
private slots:
    void showMax();
    void iconIsActived(QSystemTrayIcon::ActivationReason reason);
    void showMainMenu();
protected:
    bool winEvent(MSG *message, long *result);
};

#endif // MAINWINDOW_H
