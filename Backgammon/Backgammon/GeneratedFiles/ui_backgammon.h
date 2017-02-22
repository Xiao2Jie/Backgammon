/********************************************************************************
** Form generated from reading UI file 'backgammon.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKGAMMON_H
#define UI_BACKGAMMON_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BackgammonClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWidget *left_widget;
    QGridLayout *gridLayout_3;
    QPushButton *startButton;
    QSpacerItem *verticalSpacer;
    QWidget *right_widget;
    QGridLayout *gridLayout_2;
    QGraphicsView *graphicsView;

    void setupUi(QMainWindow *BackgammonClass)
    {
        if (BackgammonClass->objectName().isEmpty())
            BackgammonClass->setObjectName(QStringLiteral("BackgammonClass"));
        BackgammonClass->resize(700, 600);
        centralWidget = new QWidget(BackgammonClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        left_widget = new QWidget(centralWidget);
        left_widget->setObjectName(QStringLiteral("left_widget"));
        gridLayout_3 = new QGridLayout(left_widget);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        startButton = new QPushButton(left_widget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setCheckable(true);

        gridLayout_3->addWidget(startButton, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 571, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 1, 0, 1, 1);


        gridLayout->addWidget(left_widget, 0, 0, 1, 1);

        right_widget = new QWidget(centralWidget);
        right_widget->setObjectName(QStringLiteral("right_widget"));
        gridLayout_2 = new QGridLayout(right_widget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(right_widget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout_2->addWidget(graphicsView, 0, 0, 1, 1);


        gridLayout->addWidget(right_widget, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 100);
        gridLayout->setColumnStretch(1, 600);
        BackgammonClass->setCentralWidget(centralWidget);

        retranslateUi(BackgammonClass);

        QMetaObject::connectSlotsByName(BackgammonClass);
    } // setupUi

    void retranslateUi(QMainWindow *BackgammonClass)
    {
        BackgammonClass->setWindowTitle(QApplication::translate("BackgammonClass", "Backgammon", 0));
        startButton->setText(QApplication::translate("BackgammonClass", "\345\274\200\345\247\213", 0));
    } // retranslateUi

};

namespace Ui {
    class BackgammonClass: public Ui_BackgammonClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKGAMMON_H
