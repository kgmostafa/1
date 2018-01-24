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
#include <QtWidgets/QGroupBox>
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
    QPushButton *pushButton_open;
    QGroupBox *groupBox_cellType;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radioButton_cellType_pyramid;
    QRadioButton *radioButton_cellType_cube;
    QRadioButton *radioButton_cellType_icosphere;
    QRadioButton *radioButton_cellType_custom;
    QPushButton *pushButton_loadCell;
    QGroupBox *groupBox_infillDensity;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioButton_density_low;
    QRadioButton *radioButton_density_medium;
    QRadioButton *radioButton_density_high;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_layerThickness;
    QLabel *label_2;
    QPushButton *pushButton_process;
    QLabel *labelNTriangles;
    QLabel *labelWidthX;
    QLabel *labelWidthY;
    QLabel *labelHeightZ;
    QCheckBox *checkBox_wireframe;
    QCheckBox *checkBox_basePart;
    QPushButton *pushButton_save;
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
        pushButton_open = new QPushButton(centralWidget);
        pushButton_open->setObjectName(QStringLiteral("pushButton_open"));

        verticalLayout->addWidget(pushButton_open);

        groupBox_cellType = new QGroupBox(centralWidget);
        groupBox_cellType->setObjectName(QStringLiteral("groupBox_cellType"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_cellType);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        radioButton_cellType_pyramid = new QRadioButton(groupBox_cellType);
        radioButton_cellType_pyramid->setObjectName(QStringLiteral("radioButton_cellType_pyramid"));
        radioButton_cellType_pyramid->setChecked(true);
        radioButton_cellType_pyramid->setAutoExclusive(true);

        horizontalLayout_4->addWidget(radioButton_cellType_pyramid);

        radioButton_cellType_cube = new QRadioButton(groupBox_cellType);
        radioButton_cellType_cube->setObjectName(QStringLiteral("radioButton_cellType_cube"));

        horizontalLayout_4->addWidget(radioButton_cellType_cube);

        radioButton_cellType_icosphere = new QRadioButton(groupBox_cellType);
        radioButton_cellType_icosphere->setObjectName(QStringLiteral("radioButton_cellType_icosphere"));

        horizontalLayout_4->addWidget(radioButton_cellType_icosphere);

        radioButton_cellType_custom = new QRadioButton(groupBox_cellType);
        radioButton_cellType_custom->setObjectName(QStringLiteral("radioButton_cellType_custom"));

        horizontalLayout_4->addWidget(radioButton_cellType_custom);


        verticalLayout->addWidget(groupBox_cellType);

        pushButton_loadCell = new QPushButton(centralWidget);
        pushButton_loadCell->setObjectName(QStringLiteral("pushButton_loadCell"));
        pushButton_loadCell->setEnabled(false);

        verticalLayout->addWidget(pushButton_loadCell);

        groupBox_infillDensity = new QGroupBox(centralWidget);
        groupBox_infillDensity->setObjectName(QStringLiteral("groupBox_infillDensity"));
        groupBox_infillDensity->setEnabled(false);
        horizontalLayout_3 = new QHBoxLayout(groupBox_infillDensity);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        radioButton_density_low = new QRadioButton(groupBox_infillDensity);
        radioButton_density_low->setObjectName(QStringLiteral("radioButton_density_low"));
        radioButton_density_low->setChecked(true);

        horizontalLayout_3->addWidget(radioButton_density_low);

        radioButton_density_medium = new QRadioButton(groupBox_infillDensity);
        radioButton_density_medium->setObjectName(QStringLiteral("radioButton_density_medium"));

        horizontalLayout_3->addWidget(radioButton_density_medium);

        radioButton_density_high = new QRadioButton(groupBox_infillDensity);
        radioButton_density_high->setObjectName(QStringLiteral("radioButton_density_high"));

        horizontalLayout_3->addWidget(radioButton_density_high);


        verticalLayout->addWidget(groupBox_infillDensity);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit_layerThickness = new QLineEdit(centralWidget);
        lineEdit_layerThickness->setObjectName(QStringLiteral("lineEdit_layerThickness"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_layerThickness->sizePolicy().hasHeightForWidth());
        lineEdit_layerThickness->setSizePolicy(sizePolicy);
        lineEdit_layerThickness->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(lineEdit_layerThickness);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout);

        pushButton_process = new QPushButton(centralWidget);
        pushButton_process->setObjectName(QStringLiteral("pushButton_process"));
        pushButton_process->setEnabled(true);

        verticalLayout->addWidget(pushButton_process);

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

        checkBox_wireframe = new QCheckBox(centralWidget);
        checkBox_wireframe->setObjectName(QStringLiteral("checkBox_wireframe"));
        checkBox_wireframe->setChecked(true);

        verticalLayout->addWidget(checkBox_wireframe);

        checkBox_basePart = new QCheckBox(centralWidget);
        checkBox_basePart->setObjectName(QStringLiteral("checkBox_basePart"));
        checkBox_basePart->setChecked(true);

        verticalLayout->addWidget(checkBox_basePart);

        pushButton_save = new QPushButton(centralWidget);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setEnabled(false);

        verticalLayout->addWidget(pushButton_save);


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
        pushButton_open->setText(QApplication::translate("MainWindow", "Open base part", nullptr));
        groupBox_cellType->setTitle(QApplication::translate("MainWindow", "Cell type", nullptr));
        radioButton_cellType_pyramid->setText(QApplication::translate("MainWindow", "Pyramid", nullptr));
        radioButton_cellType_cube->setText(QApplication::translate("MainWindow", "Cube", nullptr));
        radioButton_cellType_icosphere->setText(QApplication::translate("MainWindow", "Icosphere", nullptr));
        radioButton_cellType_custom->setText(QApplication::translate("MainWindow", "Custom", nullptr));
        pushButton_loadCell->setText(QApplication::translate("MainWindow", "Load cell", nullptr));
        groupBox_infillDensity->setTitle(QApplication::translate("MainWindow", "Infill density", nullptr));
        radioButton_density_low->setText(QApplication::translate("MainWindow", "Low", nullptr));
        radioButton_density_medium->setText(QApplication::translate("MainWindow", "Medium", nullptr));
        radioButton_density_high->setText(QApplication::translate("MainWindow", "High", nullptr));
        label->setText(QApplication::translate("MainWindow", "Layer thickness:", nullptr));
        lineEdit_layerThickness->setText(QApplication::translate("MainWindow", "1.0", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "mm", nullptr));
        pushButton_process->setText(QApplication::translate("MainWindow", "Process", nullptr));
        labelNTriangles->setText(QApplication::translate("MainWindow", "Number of triangles: 0", nullptr));
        labelWidthX->setText(QApplication::translate("MainWindow", "Width in X: -", nullptr));
        labelWidthY->setText(QApplication::translate("MainWindow", "Width in Y: -", nullptr));
        labelHeightZ->setText(QApplication::translate("MainWindow", "Height in Z: -", nullptr));
        checkBox_wireframe->setText(QApplication::translate("MainWindow", "Wireframe", nullptr));
        checkBox_basePart->setText(QApplication::translate("MainWindow", "Show base part", nullptr));
        pushButton_save->setText(QApplication::translate("MainWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
