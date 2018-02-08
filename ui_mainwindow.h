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
    QGroupBox *groupBox_hollowing;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *lineEdit_hollowingOffset;
    QLabel *label_3;
    QCheckBox *checkBox_shell;
    QCheckBox *checkBox_skipHollowing;
    QGroupBox *groupBox_infill;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_cellType;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *radioButton_cellType_pyramid;
    QRadioButton *radioButton_cellType_cube;
    QRadioButton *radioButton_cellType_icosphere;
    QRadioButton *radioButton_cellType_custom;
    QPushButton *pushButton_loadCell;
    QGroupBox *groupBox_infillDensity;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *radioButton_density_low;
    QRadioButton *radioButton_density_medium;
    QRadioButton *radioButton_density_high;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_cellThickness;
    QLabel *label_2;
    QCheckBox *checkBox_skipInfilling;
    QPushButton *pushButton_process;
    QGroupBox *groupBox_STLInfo;
    QVBoxLayout *verticalLayout_6;
    QLabel *labelNTriangles;
    QLabel *labelWidthX;
    QLabel *labelWidthY;
    QLabel *labelHeightZ;
    QGroupBox *groupBox_options;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *checkBox_basePart;
    QCheckBox *checkBox_wireframe;
    QPushButton *pushButton_save;
    STLPreview *openGLWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(837, 595);
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

        groupBox_hollowing = new QGroupBox(centralWidget);
        groupBox_hollowing->setObjectName(QStringLiteral("groupBox_hollowing"));
        verticalLayout_2 = new QVBoxLayout(groupBox_hollowing);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(groupBox_hollowing);
        label_4->setObjectName(QStringLiteral("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(label_4);

        lineEdit_hollowingOffset = new QLineEdit(groupBox_hollowing);
        lineEdit_hollowingOffset->setObjectName(QStringLiteral("lineEdit_hollowingOffset"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_hollowingOffset->sizePolicy().hasHeightForWidth());
        lineEdit_hollowingOffset->setSizePolicy(sizePolicy1);
        lineEdit_hollowingOffset->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(lineEdit_hollowingOffset);

        label_3 = new QLabel(groupBox_hollowing);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_5->addWidget(label_3);


        verticalLayout_2->addLayout(horizontalLayout_5);

        checkBox_shell = new QCheckBox(groupBox_hollowing);
        checkBox_shell->setObjectName(QStringLiteral("checkBox_shell"));

        verticalLayout_2->addWidget(checkBox_shell);

        checkBox_skipHollowing = new QCheckBox(groupBox_hollowing);
        checkBox_skipHollowing->setObjectName(QStringLiteral("checkBox_skipHollowing"));

        verticalLayout_2->addWidget(checkBox_skipHollowing);


        verticalLayout->addWidget(groupBox_hollowing);

        groupBox_infill = new QGroupBox(centralWidget);
        groupBox_infill->setObjectName(QStringLiteral("groupBox_infill"));
        verticalLayout_3 = new QVBoxLayout(groupBox_infill);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_cellType = new QGroupBox(groupBox_infill);
        groupBox_cellType->setObjectName(QStringLiteral("groupBox_cellType"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_cellType);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        radioButton_cellType_pyramid = new QRadioButton(groupBox_cellType);
        radioButton_cellType_pyramid->setObjectName(QStringLiteral("radioButton_cellType_pyramid"));
        radioButton_cellType_pyramid->setChecked(true);
        radioButton_cellType_pyramid->setAutoExclusive(true);

        horizontalLayout_6->addWidget(radioButton_cellType_pyramid);

        radioButton_cellType_cube = new QRadioButton(groupBox_cellType);
        radioButton_cellType_cube->setObjectName(QStringLiteral("radioButton_cellType_cube"));

        horizontalLayout_6->addWidget(radioButton_cellType_cube);

        radioButton_cellType_icosphere = new QRadioButton(groupBox_cellType);
        radioButton_cellType_icosphere->setObjectName(QStringLiteral("radioButton_cellType_icosphere"));

        horizontalLayout_6->addWidget(radioButton_cellType_icosphere);

        radioButton_cellType_custom = new QRadioButton(groupBox_cellType);
        radioButton_cellType_custom->setObjectName(QStringLiteral("radioButton_cellType_custom"));

        horizontalLayout_6->addWidget(radioButton_cellType_custom);

        pushButton_loadCell = new QPushButton(groupBox_cellType);
        pushButton_loadCell->setObjectName(QStringLiteral("pushButton_loadCell"));
        pushButton_loadCell->setEnabled(false);

        horizontalLayout_6->addWidget(pushButton_loadCell);


        horizontalLayout_4->addLayout(horizontalLayout_6);


        verticalLayout_3->addWidget(groupBox_cellType);

        groupBox_infillDensity = new QGroupBox(groupBox_infill);
        groupBox_infillDensity->setObjectName(QStringLiteral("groupBox_infillDensity"));
        groupBox_infillDensity->setEnabled(true);
        verticalLayout_4 = new QVBoxLayout(groupBox_infillDensity);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        radioButton_density_low = new QRadioButton(groupBox_infillDensity);
        radioButton_density_low->setObjectName(QStringLiteral("radioButton_density_low"));
        radioButton_density_low->setEnabled(false);
        radioButton_density_low->setChecked(true);

        horizontalLayout_7->addWidget(radioButton_density_low);

        radioButton_density_medium = new QRadioButton(groupBox_infillDensity);
        radioButton_density_medium->setObjectName(QStringLiteral("radioButton_density_medium"));
        radioButton_density_medium->setEnabled(false);

        horizontalLayout_7->addWidget(radioButton_density_medium);

        radioButton_density_high = new QRadioButton(groupBox_infillDensity);
        radioButton_density_high->setObjectName(QStringLiteral("radioButton_density_high"));
        radioButton_density_high->setEnabled(false);

        horizontalLayout_7->addWidget(radioButton_density_high);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox_infillDensity);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        lineEdit_cellThickness = new QLineEdit(groupBox_infillDensity);
        lineEdit_cellThickness->setObjectName(QStringLiteral("lineEdit_cellThickness"));
        sizePolicy1.setHeightForWidth(lineEdit_cellThickness->sizePolicy().hasHeightForWidth());
        lineEdit_cellThickness->setSizePolicy(sizePolicy1);
        lineEdit_cellThickness->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(lineEdit_cellThickness);

        label_2 = new QLabel(groupBox_infillDensity);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);


        verticalLayout_4->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(groupBox_infillDensity);

        checkBox_skipInfilling = new QCheckBox(groupBox_infill);
        checkBox_skipInfilling->setObjectName(QStringLiteral("checkBox_skipInfilling"));

        verticalLayout_3->addWidget(checkBox_skipInfilling);


        verticalLayout->addWidget(groupBox_infill);

        pushButton_process = new QPushButton(centralWidget);
        pushButton_process->setObjectName(QStringLiteral("pushButton_process"));
        pushButton_process->setEnabled(true);

        verticalLayout->addWidget(pushButton_process);

        groupBox_STLInfo = new QGroupBox(centralWidget);
        groupBox_STLInfo->setObjectName(QStringLiteral("groupBox_STLInfo"));
        verticalLayout_6 = new QVBoxLayout(groupBox_STLInfo);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        labelNTriangles = new QLabel(groupBox_STLInfo);
        labelNTriangles->setObjectName(QStringLiteral("labelNTriangles"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelNTriangles->sizePolicy().hasHeightForWidth());
        labelNTriangles->setSizePolicy(sizePolicy2);

        verticalLayout_6->addWidget(labelNTriangles);

        labelWidthX = new QLabel(groupBox_STLInfo);
        labelWidthX->setObjectName(QStringLiteral("labelWidthX"));

        verticalLayout_6->addWidget(labelWidthX);

        labelWidthY = new QLabel(groupBox_STLInfo);
        labelWidthY->setObjectName(QStringLiteral("labelWidthY"));

        verticalLayout_6->addWidget(labelWidthY);

        labelHeightZ = new QLabel(groupBox_STLInfo);
        labelHeightZ->setObjectName(QStringLiteral("labelHeightZ"));

        verticalLayout_6->addWidget(labelHeightZ);


        verticalLayout->addWidget(groupBox_STLInfo);

        groupBox_options = new QGroupBox(centralWidget);
        groupBox_options->setObjectName(QStringLiteral("groupBox_options"));
        verticalLayout_5 = new QVBoxLayout(groupBox_options);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        checkBox_basePart = new QCheckBox(groupBox_options);
        checkBox_basePart->setObjectName(QStringLiteral("checkBox_basePart"));
        checkBox_basePart->setChecked(true);

        verticalLayout_5->addWidget(checkBox_basePart);

        checkBox_wireframe = new QCheckBox(groupBox_options);
        checkBox_wireframe->setObjectName(QStringLiteral("checkBox_wireframe"));
        checkBox_wireframe->setChecked(true);

        verticalLayout_5->addWidget(checkBox_wireframe);


        verticalLayout->addWidget(groupBox_options);

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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "STL Editor", nullptr));
        pushButton_open->setText(QApplication::translate("MainWindow", "Open base part", nullptr));
        groupBox_hollowing->setTitle(QApplication::translate("MainWindow", "Hollowing", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Offset:", nullptr));
        lineEdit_hollowingOffset->setText(QApplication::translate("MainWindow", "5.0", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "mm", nullptr));
        checkBox_shell->setText(QApplication::translate("MainWindow", "External offset (shell)", nullptr));
        checkBox_skipHollowing->setText(QApplication::translate("MainWindow", "Skip hollowing", nullptr));
        groupBox_infill->setTitle(QApplication::translate("MainWindow", "Infill", nullptr));
        groupBox_cellType->setTitle(QApplication::translate("MainWindow", "Cell type", nullptr));
        radioButton_cellType_pyramid->setText(QApplication::translate("MainWindow", "Pyramid", nullptr));
        radioButton_cellType_cube->setText(QApplication::translate("MainWindow", "Cube", nullptr));
        radioButton_cellType_icosphere->setText(QApplication::translate("MainWindow", "Icosphere", nullptr));
        radioButton_cellType_custom->setText(QApplication::translate("MainWindow", "Custom", nullptr));
        pushButton_loadCell->setText(QApplication::translate("MainWindow", "Load cell", nullptr));
        groupBox_infillDensity->setTitle(QApplication::translate("MainWindow", "Density", nullptr));
        radioButton_density_low->setText(QApplication::translate("MainWindow", "Low", nullptr));
        radioButton_density_medium->setText(QApplication::translate("MainWindow", "Medium", nullptr));
        radioButton_density_high->setText(QApplication::translate("MainWindow", "High", nullptr));
        label->setText(QApplication::translate("MainWindow", "Cell thickness:", nullptr));
        lineEdit_cellThickness->setText(QApplication::translate("MainWindow", "2.5", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "mm", nullptr));
        checkBox_skipInfilling->setText(QApplication::translate("MainWindow", "Skip infilling", nullptr));
        pushButton_process->setText(QApplication::translate("MainWindow", "Process", nullptr));
        groupBox_STLInfo->setTitle(QApplication::translate("MainWindow", "STL info", nullptr));
        labelNTriangles->setText(QApplication::translate("MainWindow", "Number of triangles: 0", nullptr));
        labelWidthX->setText(QApplication::translate("MainWindow", "Width in X: -", nullptr));
        labelWidthY->setText(QApplication::translate("MainWindow", "Width in Y: -", nullptr));
        labelHeightZ->setText(QApplication::translate("MainWindow", "Height in Z: -", nullptr));
        groupBox_options->setTitle(QApplication::translate("MainWindow", "Options", nullptr));
        checkBox_basePart->setText(QApplication::translate("MainWindow", "Show base part", nullptr));
        checkBox_wireframe->setText(QApplication::translate("MainWindow", "Wireframe", nullptr));
        pushButton_save->setText(QApplication::translate("MainWindow", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
