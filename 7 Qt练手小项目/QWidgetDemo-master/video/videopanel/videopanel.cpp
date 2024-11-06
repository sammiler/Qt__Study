﻿#pragma execution_character_set("utf-8")

#include "videopanel.h"
#include "videobox.h"
#include "qevent.h"
#include "qmenu.h"
#include "qlayout.h"
#include "qlabel.h"
#include "qtimer.h"
#include "qdebug.h"

VideoPanel::VideoPanel(QWidget *parent) : QWidget(parent)
{
    this->initControl();
    this->initForm();
    this->initMenu();
    QTimer::singleShot(1000, this, SLOT(playAll()));
}

bool VideoPanel::eventFilter(QObject *watched, QEvent *event)
{
    int type = event->type();
    if (type == QEvent::MouseButtonDblClick) {
        QLabel *widget = (QLabel *) watched;
        if (!videoMax) {
            videoMax = true;
            videoBox->hide_all();
            gridLayout->addWidget(widget, 0, 0);
            widget->setVisible(true);
        } else {
            videoMax = false;
            videoBox->show_all();
        }

        widget->setFocus();
    } else if (type == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        if (mouseEvent->button() == Qt::RightButton) {
            videoMenu->exec(QCursor::pos());
        }
    }

    return QWidget::eventFilter(watched, event);
}

QSize VideoPanel::sizeHint() const
{
    return QSize(800, 600);
}

QSize VideoPanel::minimumSizeHint() const
{
    return QSize(80, 60);
}

void VideoPanel::initControl()
{
    gridLayout = new QGridLayout;
    gridLayout->setSpacing(1);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(gridLayout);
}

void VideoPanel::initForm()
{
    //设置样式表
#ifndef no_style
    QStringList qss;
    qss.append("QFrame{border:2px solid #000000;}");
    qss.append("QLabel{font:75 25px;color:#F0F0F0;border:2px solid #AAAAAA;background:#303030;}");
    qss.append("QLabel:focus{border:2px solid #00BB9E;background:#555555;}");
    this->setStyleSheet(qss.join(""));
#endif

    videoMax = false;
    videoCount = 64;
    layoutType = "1_16";

    for (int i = 0; i < videoCount; ++i) {
        QLabel *widget = new QLabel;
        widget->setObjectName(QString("video%1").arg(i + 1));
        widget->installEventFilter(this);
        widget->setFocusPolicy(Qt::StrongFocus);
        widget->setAlignment(Qt::AlignCenter);
        widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        //二选一可以选择显示文字,也可以选择显示背景图片
        widget->setText(QString("通道 %1").arg(i + 1));
        //widget->setPixmap(QPixmap(":/bg_novideo.png"));
        widgets << widget;
    }
}

void VideoPanel::initMenu()
{
    videoMenu = new QMenu(this);

    //单独关联信号槽
    actionFull = new QAction("切换全屏模式", videoMenu);
    connect(actionFull, SIGNAL(triggered(bool)), this, SLOT(full()));
    actionPoll = new QAction("启动轮询视频", videoMenu);
    connect(actionPoll, SIGNAL(triggered(bool)), this, SLOT(poll()));

    //通过QAction类方式添加子菜单
    videoMenu->addAction(actionFull);
    videoMenu->addAction(actionPoll);
    videoMenu->addSeparator();

    //直接通过文字的形式添加子菜单
    videoMenu->addAction("截图当前视频", this, SLOT(snapOne()));
    videoMenu->addAction("截图所有视频", this, SLOT(snapAll()));
    videoMenu->addSeparator();

    //实例化通道布局类
    videoBox = new VideoBox(this);
    videoBox->initMenu(videoMenu);
    videoBox->setLayoutType(layoutType);
    videoBox->setLayout(gridLayout);
    videoBox->setWidgets(widgets);
    videoBox->show_all();
}

void VideoPanel::full()
{
    if (actionFull->text() == "切换全屏模式") {
        Q_EMIT fullScreen(true);
        actionFull->setText("切换正常模式");
    } else {
        Q_EMIT fullScreen(false);
        actionFull->setText("切换全屏模式");
    }

    //执行全屏处理
}

void VideoPanel::poll()
{
    if (actionPoll->text() == "启动轮询视频") {
        actionPoll->setText("停止轮询视频");
    } else {
        actionPoll->setText("启动轮询视频");
    }

    //执行轮询处理
}

void VideoPanel::playAll()
{

}

void VideoPanel::snapOne()
{

}

void VideoPanel::snapAll()
{

}
