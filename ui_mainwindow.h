/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "stlpreview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_test;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_size;
    QLabel *label_2;
    QPushButton *pushButton_Process;
    QLabel *labelNTriangles;
    QLabel *labelWidthX;
    QLabel *labelWidthY;
    QLabel *labelHeightZ;
    QCheckBox *checkBoxWireFrame;
    QPushButton *pushButtonSave;
    STLPreview *openGLWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(837, 455);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::Canada));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_test = new QPushButton(centralWidget);
        pushButton_test->setObjectName(QStringLiteral("pushButton_test"));

        verticalLayout->addWidget(pushButton_test);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit_size = new QLineEdit(centralWidget);
        lineEdit_size->setObjectName(QStringLiteral("lineEdit_size"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_size->sizePolicy().hasHeightForWidth());
        lineEdit_size->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEdit_size);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout);

        pushButton_Process = new QPushButton(centralWidget);
        pushButton_Process->setObjectName(QStringLiteral("pushButton_Process"));

        verticalLayout->addWidget(pushButton_Process);

        labelNTriangles = new QLabel(centralWidget);
        labelNTriangles->setObjectName(QStringLiteral("labelNTriangles"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelNTriangles->sizePolicy().hasHeightForWidth());
        labelNTriangles->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(labelNTriangles);

        labelWidthX = new QLabel(centralWidget);
        labelWidthX->setObjectName(QStringLiteral("labelWidthX"));

        verticalLayout->addWidget(labelWidthX);

        labelWidthY = new QLabel(centralWidget);
        labelWidthY->setObjectName(QStringLiteral("labelWidthY"));

        verticalLayout->addWidget(labelWidthY);

        labelHeightZ = new QLabel(centralWidget);
        labelHeightZ->setObjectName(QStringLiteral("labelHeightZ"));

        verticalLayout->addWidget(labelHeightZ);

        checkBoxWireFrame = new QCheckBox(centralWidget);
        checkBoxWireFrame->setObjectName(QStringLiteral("checkBoxWireFrame"));
        checkBoxWireFrame->setChecked(true);

        verticalLayout->addWidget(checkBoxWireFrame);

        pushButtonSave = new QPushButton(centralWidget);
        pushButtonSave->setObjectName(QStringLiteral("pushButtonSave"));
        pushButtonSave->setEnabled(false);

        verticalLayout->addWidget(pushButtonSave);


        horizontalLayout_2->addLayout(verticalLayout);

        openGLWidget = new STLPreview(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        horizontalLayout_2->addWidget(openGLWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "STL Reader", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Open", nullptr));
        pushButton_test->setText(QApplication::translate("MainWindow", "Load a cube", nullptr));
        label->setText(QApplication::translate("MainWindow", "Quads size:", nullptr));
        lineEdit_size->setText(QApplication::translate("MainWindow", "10", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "mm", nullptr));
        pushButton_Process->setText(QApplication::translate("MainWindow", "Process", nullptr));
        labelNTriangles->setText(QApplication::translate("MainWindow", "Number of triangles: 0", nullptr));
        labelWidthX->setText(QApplication::translate("MainWindow", "Width in X: -", nullptr));
        labelWidthY->setText(QApplication::translate("MainWindow", "Width in Y: -", nullptr));
        labelHeightZ->setText(QApplication::translate("MainWindow", "Height in Z: -", nullptr));
        checkBoxWireFrame->setText(QApplication::translate("MainWindow", "Wireframe", nullptr));
        pushButtonSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
