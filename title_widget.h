#ifndef TITLE_WIDGET_H
#define TITLE_WIDGET_H

#include <QWidget>
#include <QLabel>
#include "push_button.h"

class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = 0);
private:
    QLabel *version_title; //标题
    QPushButton *medal_button; //勋章墙
    PushButton *skin_button; //换肤
    PushButton *main_menu_button; //主菜单
    PushButton *min_button; //最小化
    PushButton *max_button; //最大化
    PushButton *close_button; //关闭

    QPoint press_point;//鼠标按下去的点
    bool is_move;

    
signals:
    void showSkin();
    void showMin();
    void showMax();
    void showMainMenu();
    void closeWidget();
    
public slots:

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    
};

#endif // TITLE_WIDGET_H
