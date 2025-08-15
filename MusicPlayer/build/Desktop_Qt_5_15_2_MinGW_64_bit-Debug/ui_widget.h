/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_Lyrics;
    QListWidget *listWidget;
    QSlider *playCourseSlider;
    QSlider *volumeSlider;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *curLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *totalLabel;
    QSlider *speedSlider;
    QLabel *speedlabel;
    QLabel *speedlabel_2;
    QLabel *speedlabel_3;
    QTextEdit *lyricsTextEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(715, 489);
        Widget->setStyleSheet(QString::fromUtf8("*{\n"
"	border:none;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color: rgb(216, 255, 252);\n"
"}\n"
"\n"
"\n"
""));
        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 430, 601, 61));
        widget->setMaximumSize(QSize(16777215, 64));
        widget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(32, 32));
        pushButton->setMaximumSize(QSize(32, 32));
        pushButton->setStyleSheet(QString::fromUtf8("background-image: url(:/assets/openDir.png);"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(32, 32));
        pushButton_2->setMaximumSize(QSize(32, 32));
        pushButton_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(32, 32));
        pushButton_3->setMaximumSize(QSize(32, 32));
        pushButton_3->setStyleSheet(QString::fromUtf8("icon: url(:/assets/preSong.png);"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(32, 32));
        pushButton_4->setMaximumSize(QSize(32, 32));
        pushButton_4->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(widget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(32, 32));
        pushButton_5->setMaximumSize(QSize(32, 32));
        pushButton_5->setStyleSheet(QString::fromUtf8("icon: url(:/assets/nextSong.png);"));

        horizontalLayout->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(widget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(32, 32));
        pushButton_6->setMaximumSize(QSize(32, 32));
        pushButton_6->setStyleSheet(QString::fromUtf8("icon: url(:/assets/volume.png);"));

        horizontalLayout->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(widget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(32, 32));
        pushButton_7->setMaximumSize(QSize(32, 32));
        pushButton_7->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(widget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setMinimumSize(QSize(32, 32));
        pushButton_8->setMaximumSize(QSize(32, 32));
        pushButton_8->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(pushButton_8);

        pushButton_Lyrics = new QPushButton(widget);
        pushButton_Lyrics->setObjectName(QString::fromUtf8("pushButton_Lyrics"));
        pushButton_Lyrics->setMinimumSize(QSize(32, 32));
        pushButton_Lyrics->setMaximumSize(QSize(32, 32));
        pushButton_Lyrics->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(pushButton_Lyrics);

        listWidget = new QListWidget(Widget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(490, 0, 221, 231));
        playCourseSlider = new QSlider(Widget);
        playCourseSlider->setObjectName(QString::fromUtf8("playCourseSlider"));
        playCourseSlider->setGeometry(QRect(10, 410, 331, 22));
        playCourseSlider->setOrientation(Qt::Horizontal);
        volumeSlider = new QSlider(Widget);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setGeometry(QRect(350, 380, 22, 51));
        volumeSlider->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 380, 331, 24));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        curLabel = new QLabel(layoutWidget);
        curLabel->setObjectName(QString::fromUtf8("curLabel"));

        horizontalLayout_2->addWidget(curLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        totalLabel = new QLabel(layoutWidget);
        totalLabel->setObjectName(QString::fromUtf8("totalLabel"));

        horizontalLayout_2->addWidget(totalLabel);

        speedSlider = new QSlider(Widget);
        speedSlider->setObjectName(QString::fromUtf8("speedSlider"));
        speedSlider->setGeometry(QRect(440, 420, 81, 22));
        speedSlider->setOrientation(Qt::Horizontal);
        speedlabel = new QLabel(Widget);
        speedlabel->setObjectName(QString::fromUtf8("speedlabel"));
        speedlabel->setGeometry(QRect(425, 400, 41, 20));
        speedlabel_2 = new QLabel(Widget);
        speedlabel_2->setObjectName(QString::fromUtf8("speedlabel_2"));
        speedlabel_2->setGeometry(QRect(500, 400, 41, 20));
        speedlabel_3 = new QLabel(Widget);
        speedlabel_3->setObjectName(QString::fromUtf8("speedlabel_3"));
        speedlabel_3->setGeometry(QRect(340, 360, 41, 19));
        lyricsTextEdit = new QTextEdit(Widget);
        lyricsTextEdit->setObjectName(QString::fromUtf8("lyricsTextEdit"));
        lyricsTextEdit->setGeometry(QRect(20, 20, 421, 321));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        pushButton_5->setText(QString());
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_8->setText(QString());
        pushButton_Lyrics->setText(QString());
        curLabel->setText(QCoreApplication::translate("Widget", "00:00", nullptr));
        totalLabel->setText(QCoreApplication::translate("Widget", "00:00", nullptr));
        speedlabel->setText(QString());
        speedlabel_2->setText(QString());
        speedlabel_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
