/********************************************************************************
** Form generated from reading UI file 'graphUI.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHUI_H
#define UI_GRAPHUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_graphDlg
{
public:
    QHBoxLayout *horizontalLayout_3;
    QSplitter *splitter_2;
    QSplitter *splitter_1;
    QTableWidget *tableWidgetNodes;
    QTableWidget *tableWidgetEdges;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_2;
    QWidget *tab3;
    QHBoxLayout *horizontalLayout_4;

    void setupUi(QWidget *graphDlg)
    {
        if (graphDlg->objectName().isEmpty())
            graphDlg->setObjectName(QStringLiteral("graphDlg"));
        graphDlg->resize(1028, 735);
        horizontalLayout_3 = new QHBoxLayout(graphDlg);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        splitter_2 = new QSplitter(graphDlg);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter_1 = new QSplitter(splitter_2);
        splitter_1->setObjectName(QStringLiteral("splitter_1"));
        splitter_1->setOrientation(Qt::Vertical);
        tableWidgetNodes = new QTableWidget(splitter_1);
        tableWidgetNodes->setObjectName(QStringLiteral("tableWidgetNodes"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidgetNodes->sizePolicy().hasHeightForWidth());
        tableWidgetNodes->setSizePolicy(sizePolicy);
        splitter_1->addWidget(tableWidgetNodes);
        tableWidgetEdges = new QTableWidget(splitter_1);
        tableWidgetEdges->setObjectName(QStringLiteral("tableWidgetEdges"));
        sizePolicy.setHeightForWidth(tableWidgetEdges->sizePolicy().hasHeightForWidth());
        tableWidgetEdges->setSizePolicy(sizePolicy);
        splitter_1->addWidget(tableWidgetEdges);
        splitter_2->addWidget(splitter_1);
        tabWidget = new QTabWidget(splitter_2);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        horizontalLayout = new QHBoxLayout(tab_1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        graphicsView = new QGraphicsView(tab_1);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        horizontalLayout->addWidget(graphicsView);

        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout_2 = new QHBoxLayout(tab_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        tabWidget->addTab(tab_2, QString());
        tab3 = new QWidget();
        tab3->setObjectName(QStringLiteral("tab3"));
        horizontalLayout_4 = new QHBoxLayout(tab3);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        tabWidget->addTab(tab3, QString());
        splitter_2->addWidget(tabWidget);

        horizontalLayout_3->addWidget(splitter_2);


        retranslateUi(graphDlg);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(graphDlg);
    } // setupUi

    void retranslateUi(QWidget *graphDlg)
    {
        graphDlg->setWindowTitle(QApplication::translate("graphDlg", "DSRGraph", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("graphDlg", "graph", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("graphDlg", "3d", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab3), QApplication::translate("graphDlg", "2d", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class graphDlg: public Ui_graphDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHUI_H
