#include "toolswidget.h"
#include <QLabel>
#include <QSqlQuery>
#include <QVBoxLayout>
#include <QSplitter>
#include <QDebug>



ToolsWidget::ToolsWidget(QWidget *parent) :
    QWidget(parent)
{

    QWidget *tools_widget;
    QWidget *main_widget;
    QSplitter * main_splitter;

    tools_widget = new QWidget(this);
    main_widget = new QWidget(this);


    QPalette palette;

    tools_widget->setAutoFillBackground(true);
    main_widget->setAutoFillBackground(true);
    palette.setColor(QPalette::Background,QColor(155,225,123));

    tools_widget->setPalette(palette);
    tools_widget->setFixedHeight(20);

    main_splitter = new QSplitter(this);
    main_splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_splitter->setOrientation(Qt::Vertical);
    main_splitter->setHandleWidth(0);
    main_splitter->setStyleSheet("QSplitter::handle{background:lightgray;}");

    main_splitter->addWidget(tools_widget);
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


    setLayout(main_layout);


}
