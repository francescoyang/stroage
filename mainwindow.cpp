#include "mainwindow.h"
//#include "tlq_api.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <Windowsx.h>



MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    systemtray = new SystemTray();
    connect(systemtray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));
    systemtray->show();

    setMinimumSize(900, 600);
    //    setWindowIcon(QIcon(":/img/safe.ico"));
    setWindowFlags(Qt::FramelessWindowHint);
//    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);   // 窗口一直置顶
    title_widget = new TitleWidget();
    content_widget = new ContentWidget();
    main_menu = new MainMenu();
    location = this->geometry();

    title_widget->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(192,253,123));
    //palette.setBrush(QPalette::Background, QBrush(QPixmap(":/background.png")));
    title_widget->setPalette(palette);

    QVBoxLayout *center_layout = new QVBoxLayout();
    center_layout->addWidget(content_widget);
    center_layout->setSpacing(0);
    center_layout->setContentsMargins(1, 0, 1, 1);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(title_widget);
    main_layout->addLayout(center_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    setLayout(main_layout);

    //    connect(title_widget, SIGNAL(showSkin()), this, SLOT(showSkinWidget()));
    connect(title_widget, SIGNAL(showMainMenu()), this, SLOT(showMainMenu()));
    connect(title_widget, SIGNAL(showMax()), this, SLOT(showMax()));
    connect(title_widget, SIGNAL(showMin()), this, SLOT(showMinimized()));
    connect(title_widget, SIGNAL(closeWidget()), this, SLOT(hide()));
    connect(main_menu, SIGNAL(sqlinit_signal()), content_widget, SLOT(sqlinit_slot()));
    connect(main_menu, SIGNAL(changepasswd_signal()), content_widget, SLOT(changepasswd_slot()));
//    connect(title_widget, SIGNAL(closeWidget()), qApp, SLOT(quit()));
    testTong();

    setWindowIcon(QIcon(QLatin1String("img/safe.png"))); //   设置应用 在任务栏窗口上的图标。
//    slotStyleChange(2);
}

MainWindow::~MainWindow()
{
    
}


void MainWindow::showMainMenu()
{
    //设置主菜单出现的位置
    QPoint p = rect().topRight();
    p.setX(p.x() - 150);
    p.setY(p.y() + 22);
    main_menu->exec(this->mapToGlobal(p));
}

bool MainWindow::winEvent(MSG *message, long *result)
{
//    switch(message->message)
//    {
//    case WM_NCHITTEST:
//        int xPos = GET_X_LPARAM(message->lParam) - this->frameGeometry().x();
//        int yPos = GET_Y_LPARAM(message->lParam) - this->frameGeometry().y();
//        if(this->childAt(xPos,yPos) == 0)
//        {
//            *result = HTCAPTION;
//        }else{
//            return false;
//        }
//        if(xPos > 18 && xPos < 22)
//            *result = HTLEFT;
//        if(xPos > (this->width() - 22) && xPos < (this->width() - 18))
//            *result = HTRIGHT;
//        if(yPos > 18 && yPos < 22)
//            *result = HTTOP;
//        if(yPos > (this->height() - 22) && yPos < (this->height() - 18))
//            *result = HTBOTTOM;
//        if(xPos > 18 && xPos < 22 && yPos > 18 && yPos < 22)
//            *result = HTTOPLEFT;
//        if(xPos > (this->width() - 22) && xPos < (this->width() - 18) && yPos > 18 && yPos < 22)
//            *result = HTTOPRIGHT;
//        if(xPos > 18 && xPos < 22 && yPos > (this->height() - 22) && yPos < (this->height() - 18))
//            *result = HTBOTTOMLEFT;
//        if(xPos > (this->width() - 22) && xPos < (this->width() - 18) && yPos > (this->height() - 22) && yPos < (this->height() - 18))
//            *result = HTBOTTOMRIGHT;

//        return true;
//    }
    return false;
}
void MainWindow::iconIsActived(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        //点击托盘图标之后松开
    case QSystemTrayIcon::Trigger:
        {
            showWidget();
            break;
        }
        //双击托盘图标
    case QSystemTrayIcon::DoubleClick:
        {
            showWidget();
            break;
        }
    default:
        break;
    }
}

void MainWindow::testTong()
{
    //    Tlq_Conn(TLQ_ID *gid,TLQError *err);
}

void MainWindow::showMax()
{
    static bool is_max=false;
    if(is_max)
    {
        this->setGeometry(location);
    }
    else
    {
        //获取当前界面的位置
        location = this->geometry();
        this->setGeometry(QApplication::desktop()->availableGeometry());
    }
    is_max = !is_max;
}

void MainWindow::showWidget()
{
    this->showNormal();
    this->raise();
    this->activateWindow();
}

void MainWindow::slotStyleChange(int StyleString)     //透明度
{
    //        QFile file0("./etc/qss/abc.qss");
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
