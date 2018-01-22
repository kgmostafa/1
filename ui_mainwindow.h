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
#include <QtWidgets/QRadioButton>
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
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_9;
    QRadioButton *radioButton_cellType_pyramid;
    QRadioButton *radioButton_cellType_cube;
    QRadioButton *radioButton_cellType_icosphere;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_size;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_posX;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QLineEdit *lineEdit_posY;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QLineEdit *lineEdit_posZ;
    QLabel *label_8;
    QPushButton *pushButton_Place;
    QLabel *labelNTriangles;
    QLabel *labelWidthX;
    QLabel *labelWidthY;
    QLabel *labelHeightZ;
    QCheckBox *checkBoxWireFrame;
    QCheckBox *checkBox_baseCube;
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

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_8->addWidget(label_9);

        radioButton_cellType_pyramid = new QRadioButton(centralWidget);
        radioButton_cellType_pyramid->setObjectName(QStringLiteral("radioButton_cellType_pyramid"));
        radioButton_cellType_pyramid->setChecked(true);

        horizontalLayout_8->addWidget(radioButton_cellType_pyramid);

        radioButton_cellType_cube = new QRadioButton(centralWidget);
        radioButton_cellType_cube->setObjectName(QStringLiteral("radioButton_cellType_cube"));

        horizontalLayout_8->addWidget(radioButton_cellType_cube);

        radioButton_cellType_icosphere = new QRadioButton(centralWidget);
        radioButton_cellType_icosphere->setObjectName(QStringLiteral("radioButton_cellType_icosphere"));

        horizontalLayout_8->addWidget(radioButton_cellType_icosphere);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(false);

        horizontalLayout->addWidget(label);

        lineEdit_size = new QLineEdit(centralWidget);
        lineEdit_size->setObjectName(QStringLiteral("lineEdit_size"));
        lineEdit_size->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_size->sizePolicy().hasHeightForWidth());
        lineEdit_size->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEdit_size);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setEnabled(false);

        horizontalLayout->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_posX = new QLineEdit(centralWidget);
        lineEdit_posX->setObjectName(QStringLiteral("lineEdit_posX"));
        sizePolicy.setHeightForWidth(lineEdit_posX->sizePolicy().hasHeightForWidth());
        lineEdit_posX->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(lineEdit_posX);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_3->addWidget(label_6);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_6->addWidget(label_4);

        lineEdit_posY = new QLineEdit(centralWidget);
        lineEdit_posY->setObjectName(QStringLiteral("lineEdit_posY"));
        sizePolicy.setHeightForWidth(lineEdit_posY->sizePolicy().hasHeightForWidth());
        lineEdit_posY->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(lineEdit_posY);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_6->addWidget(label_7);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_7->addWidget(label_5);

        lineEdit_posZ = new QLineEdit(centralWidget);
        lineEdit_posZ->setObjectName(QStringLiteral("lineEdit_posZ"));
        sizePolicy.setHeightForWidth(lineEdit_posZ->sizePolicy().hasHeightForWidth());
        lineEdit_posZ->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(lineEdit_posZ);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_7->addWidget(label_8);


        verticalLayout->addLayout(horizontalLayout_7);

        pushButton_Place = new QPushButton(centralWidget);
        pushButton_Place->setObjectName(QStringLiteral("pushButton_Place"));

        verticalLayout->addWidget(pushButton_Place);

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

        checkBox_baseCube = new QCheckBox(centralWidget);
        checkBox_baseCube->setObjectName(QStringLiteral("checkBox_baseCube"));
        checkBox_baseCube->setChecked(true);

        verticalLayout->addWidget(checkBox_baseCube);

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
        pushButton_test->setText(QApplication::translate("MainWindow", "Load a test cube", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Cell type:", nullptr));
        radioButton_cellType_pyramid->setText(QApplication::translate("MainWindow", "Pyramid", nullptr));
        radioButton_cellType_cube->setText(QApplication::translate("MainWindow", "Cube", nullptr));
        radioButton_cellType_icosphere->setText(QApplication::translate("MainWindow", "Icosphere", nullptr));
        label->setText(QApplication::translate("MainWindow", "Cell size:", nullptr));
        lineEdit_size->setText(QApplication::translate("MainWindow", "10", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "mm", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Fill X with:", nullptr));
        lineEdit_posX->setText(QApplication::translate("MainWindow", "1", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "cells", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Fill Y with:", nullptr));
        lineEdit_posY->setText(QApplication::translate("MainWindow", "1", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "cells", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Fill Z with:", nullptr));
        lineEdit_posZ->setText(QApplication::translate("MainWindow", "1", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "cells", nullptr));
        pushButton_Place->setText(QApplication::translate("MainWindow", "Place cells", nullptr));
        labelNTriangles->setText(QApplication::translate("MainWindow", "Number of triangles: 0", nullptr));
        labelWidthX->setText(QApplication::translate("MainWindow", "Width in X: -", nullptr));
        labelWidthY->setText(QApplication::translate("MainWindow", "Width in Y: -", nullptr));
        labelHeightZ->setText(QApplication::translate("MainWindow", "Height in Z: -", nullptr));
        checkBoxWireFrame->setText(QApplication::translate("MainWindow", "Wireframe", nullptr));
        checkBox_baseCube->setText(QApplication::translate("MainWindow", "Show base cube", nullptr));
        pushButtonSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
