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
#include <QtWidgets/QDoubleSpinBox>
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

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_importBase;
    QPushButton *pushButton_view;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_rotateBase;
    QGroupBox *groupBox_hollowing;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *lineEdit_hollowingOffset;
    QLabel *label_offsetUnit;
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
    QLabel *label_cellUnit;
    QCheckBox *checkBox_constantCellSize;
    QGroupBox *groupBox_infillCoordinateSystem;
    QHBoxLayout *horizontalLayout_8;
    QRadioButton *radioButton_infillCoordinateSystem_cartesian;
    QRadioButton *radioButton_infillCoordinateSystem_cylindrical;
    QRadioButton *radioButton_infillCoordinateSystem_spherical;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_infill_originX;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_infill_originY;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox_infill_originZ;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_6;
    QLineEdit *lineEdit_cellSizeX;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QLineEdit *lineEdit_cellSizeY;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_8;
    QLineEdit *lineEdit_cellSizeZ;
    QCheckBox *checkBox_variableInfill;
    QCheckBox *checkBox_skipInfilling;
    QPushButton *pushButton_process;
    QPushButton *pushButton_save;
    QVBoxLayout *verticalLayout_viewer;
    QGroupBox *groupBox_STLInfo;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_nTriangles;
    QLabel *labelWidthX;
    QLabel *labelWidthY;
    QLabel *labelHeightZ;
    QLabel *label_baseOrigin;
    QLabel *label_baseCentroid;
    QLabel *label_baseVolume;
    QGroupBox *groupBox_viewerOptions;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *checkBox_basePart;
    QCheckBox *checkBox_wireframe;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(837, 785);
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
        pushButton_importBase = new QPushButton(centralWidget);
        pushButton_importBase->setObjectName(QStringLiteral("pushButton_importBase"));

        verticalLayout->addWidget(pushButton_importBase);

        pushButton_view = new QPushButton(centralWidget);
        pushButton_view->setObjectName(QStringLiteral("pushButton_view"));

        verticalLayout->addWidget(pushButton_view);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButton_rotateBase = new QPushButton(groupBox);
        pushButton_rotateBase->setObjectName(QStringLiteral("pushButton_rotateBase"));
        pushButton_rotateBase->setEnabled(false);

        horizontalLayout_3->addWidget(pushButton_rotateBase);


        verticalLayout->addWidget(groupBox);

        groupBox_hollowing = new QGroupBox(centralWidget);
        groupBox_hollowing->setObjectName(QStringLiteral("groupBox_hollowing"));
        sizePolicy.setHeightForWidth(groupBox_hollowing->sizePolicy().hasHeightForWidth());
        groupBox_hollowing->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupBox_hollowing);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(groupBox_hollowing);
        label_4->setObjectName(QStringLiteral("label_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_4);

        lineEdit_hollowingOffset = new QLineEdit(groupBox_hollowing);
        lineEdit_hollowingOffset->setObjectName(QStringLiteral("lineEdit_hollowingOffset"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_hollowingOffset->sizePolicy().hasHeightForWidth());
        lineEdit_hollowingOffset->setSizePolicy(sizePolicy2);
        lineEdit_hollowingOffset->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(lineEdit_hollowingOffset);

        label_offsetUnit = new QLabel(groupBox_hollowing);
        label_offsetUnit->setObjectName(QStringLiteral("label_offsetUnit"));

        horizontalLayout_5->addWidget(label_offsetUnit);


        verticalLayout_2->addLayout(horizontalLayout_5);

        checkBox_shell = new QCheckBox(groupBox_hollowing);
        checkBox_shell->setObjectName(QStringLiteral("checkBox_shell"));

        verticalLayout_2->addWidget(checkBox_shell);

        checkBox_skipHollowing = new QCheckBox(groupBox_hollowing);
        checkBox_skipHollowing->setObjectName(QStringLiteral("checkBox_skipHollowing"));
        checkBox_skipHollowing->setChecked(true);

        verticalLayout_2->addWidget(checkBox_skipHollowing);


        verticalLayout->addWidget(groupBox_hollowing);

        groupBox_infill = new QGroupBox(centralWidget);
        groupBox_infill->setObjectName(QStringLiteral("groupBox_infill"));
        sizePolicy.setHeightForWidth(groupBox_infill->sizePolicy().hasHeightForWidth());
        groupBox_infill->setSizePolicy(sizePolicy);
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
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label);

        lineEdit_cellThickness = new QLineEdit(groupBox_infillDensity);
        lineEdit_cellThickness->setObjectName(QStringLiteral("lineEdit_cellThickness"));
        sizePolicy2.setHeightForWidth(lineEdit_cellThickness->sizePolicy().hasHeightForWidth());
        lineEdit_cellThickness->setSizePolicy(sizePolicy2);
        lineEdit_cellThickness->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(lineEdit_cellThickness);

        label_cellUnit = new QLabel(groupBox_infillDensity);
        label_cellUnit->setObjectName(QStringLiteral("label_cellUnit"));

        horizontalLayout->addWidget(label_cellUnit);


        verticalLayout_4->addLayout(horizontalLayout);

        checkBox_constantCellSize = new QCheckBox(groupBox_infillDensity);
        checkBox_constantCellSize->setObjectName(QStringLiteral("checkBox_constantCellSize"));

        verticalLayout_4->addWidget(checkBox_constantCellSize);


        verticalLayout_3->addWidget(groupBox_infillDensity);

        groupBox_infillCoordinateSystem = new QGroupBox(groupBox_infill);
        groupBox_infillCoordinateSystem->setObjectName(QStringLiteral("groupBox_infillCoordinateSystem"));
        horizontalLayout_8 = new QHBoxLayout(groupBox_infillCoordinateSystem);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        radioButton_infillCoordinateSystem_cartesian = new QRadioButton(groupBox_infillCoordinateSystem);
        radioButton_infillCoordinateSystem_cartesian->setObjectName(QStringLiteral("radioButton_infillCoordinateSystem_cartesian"));
        radioButton_infillCoordinateSystem_cartesian->setChecked(true);

        horizontalLayout_8->addWidget(radioButton_infillCoordinateSystem_cartesian);

        radioButton_infillCoordinateSystem_cylindrical = new QRadioButton(groupBox_infillCoordinateSystem);
        radioButton_infillCoordinateSystem_cylindrical->setObjectName(QStringLiteral("radioButton_infillCoordinateSystem_cylindrical"));
        radioButton_infillCoordinateSystem_cylindrical->setChecked(false);

        horizontalLayout_8->addWidget(radioButton_infillCoordinateSystem_cylindrical);

        radioButton_infillCoordinateSystem_spherical = new QRadioButton(groupBox_infillCoordinateSystem);
        radioButton_infillCoordinateSystem_spherical->setObjectName(QStringLiteral("radioButton_infillCoordinateSystem_spherical"));

        horizontalLayout_8->addWidget(radioButton_infillCoordinateSystem_spherical);


        verticalLayout_3->addWidget(groupBox_infillCoordinateSystem);

        groupBox_2 = new QGroupBox(groupBox_infill);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_7 = new QVBoxLayout(groupBox_2);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(label_2);

        doubleSpinBox_infill_originX = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_infill_originX->setObjectName(QStringLiteral("doubleSpinBox_infill_originX"));
        doubleSpinBox_infill_originX->setEnabled(true);

        horizontalLayout_10->addWidget(doubleSpinBox_infill_originX);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(label_3);

        doubleSpinBox_infill_originY = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_infill_originY->setObjectName(QStringLiteral("doubleSpinBox_infill_originY"));
        doubleSpinBox_infill_originY->setEnabled(true);

        horizontalLayout_10->addWidget(doubleSpinBox_infill_originY);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(label_5);

        doubleSpinBox_infill_originZ = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_infill_originZ->setObjectName(QStringLiteral("doubleSpinBox_infill_originZ"));
        doubleSpinBox_infill_originZ->setEnabled(true);

        horizontalLayout_10->addWidget(doubleSpinBox_infill_originZ);


        verticalLayout_7->addLayout(horizontalLayout_10);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(groupBox_infill);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_8 = new QVBoxLayout(groupBox_3);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        horizontalLayout_9->addWidget(label_6);

        lineEdit_cellSizeX = new QLineEdit(groupBox_3);
        lineEdit_cellSizeX->setObjectName(QStringLiteral("lineEdit_cellSizeX"));
        sizePolicy.setHeightForWidth(lineEdit_cellSizeX->sizePolicy().hasHeightForWidth());
        lineEdit_cellSizeX->setSizePolicy(sizePolicy);

        horizontalLayout_9->addWidget(lineEdit_cellSizeX);


        verticalLayout_8->addLayout(horizontalLayout_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(label_7);

        lineEdit_cellSizeY = new QLineEdit(groupBox_3);
        lineEdit_cellSizeY->setObjectName(QStringLiteral("lineEdit_cellSizeY"));
        sizePolicy.setHeightForWidth(lineEdit_cellSizeY->sizePolicy().hasHeightForWidth());
        lineEdit_cellSizeY->setSizePolicy(sizePolicy);

        horizontalLayout_11->addWidget(lineEdit_cellSizeY);


        verticalLayout_8->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);

        horizontalLayout_12->addWidget(label_8);

        lineEdit_cellSizeZ = new QLineEdit(groupBox_3);
        lineEdit_cellSizeZ->setObjectName(QStringLiteral("lineEdit_cellSizeZ"));
        sizePolicy.setHeightForWidth(lineEdit_cellSizeZ->sizePolicy().hasHeightForWidth());
        lineEdit_cellSizeZ->setSizePolicy(sizePolicy);

        horizontalLayout_12->addWidget(lineEdit_cellSizeZ);


        verticalLayout_8->addLayout(horizontalLayout_12);

        checkBox_variableInfill = new QCheckBox(groupBox_3);
        checkBox_variableInfill->setObjectName(QStringLiteral("checkBox_variableInfill"));
        checkBox_variableInfill->setChecked(true);

        verticalLayout_8->addWidget(checkBox_variableInfill);


        verticalLayout_3->addWidget(groupBox_3);

        checkBox_skipInfilling = new QCheckBox(groupBox_infill);
        checkBox_skipInfilling->setObjectName(QStringLiteral("checkBox_skipInfilling"));
        checkBox_skipInfilling->setChecked(false);

        verticalLayout_3->addWidget(checkBox_skipInfilling);


        verticalLayout->addWidget(groupBox_infill);

        pushButton_process = new QPushButton(centralWidget);
        pushButton_process->setObjectName(QStringLiteral("pushButton_process"));
        pushButton_process->setEnabled(false);

        verticalLayout->addWidget(pushButton_process);

        pushButton_save = new QPushButton(centralWidget);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setEnabled(false);

        verticalLayout->addWidget(pushButton_save);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_viewer = new QVBoxLayout();
        verticalLayout_viewer->setSpacing(6);
        verticalLayout_viewer->setObjectName(QStringLiteral("verticalLayout_viewer"));
        groupBox_STLInfo = new QGroupBox(centralWidget);
        groupBox_STLInfo->setObjectName(QStringLiteral("groupBox_STLInfo"));
        sizePolicy.setHeightForWidth(groupBox_STLInfo->sizePolicy().hasHeightForWidth());
        groupBox_STLInfo->setSizePolicy(sizePolicy);
        verticalLayout_6 = new QVBoxLayout(groupBox_STLInfo);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_nTriangles = new QLabel(groupBox_STLInfo);
        label_nTriangles->setObjectName(QStringLiteral("label_nTriangles"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_nTriangles->sizePolicy().hasHeightForWidth());
        label_nTriangles->setSizePolicy(sizePolicy3);

        verticalLayout_6->addWidget(label_nTriangles);

        labelWidthX = new QLabel(groupBox_STLInfo);
        labelWidthX->setObjectName(QStringLiteral("labelWidthX"));

        verticalLayout_6->addWidget(labelWidthX);

        labelWidthY = new QLabel(groupBox_STLInfo);
        labelWidthY->setObjectName(QStringLiteral("labelWidthY"));

        verticalLayout_6->addWidget(labelWidthY);

        labelHeightZ = new QLabel(groupBox_STLInfo);
        labelHeightZ->setObjectName(QStringLiteral("labelHeightZ"));

        verticalLayout_6->addWidget(labelHeightZ);

        label_baseOrigin = new QLabel(groupBox_STLInfo);
        label_baseOrigin->setObjectName(QStringLiteral("label_baseOrigin"));

        verticalLayout_6->addWidget(label_baseOrigin);

        label_baseCentroid = new QLabel(groupBox_STLInfo);
        label_baseCentroid->setObjectName(QStringLiteral("label_baseCentroid"));

        verticalLayout_6->addWidget(label_baseCentroid);

        label_baseVolume = new QLabel(groupBox_STLInfo);
        label_baseVolume->setObjectName(QStringLiteral("label_baseVolume"));

        verticalLayout_6->addWidget(label_baseVolume);


        verticalLayout_viewer->addWidget(groupBox_STLInfo);

        groupBox_viewerOptions = new QGroupBox(centralWidget);
        groupBox_viewerOptions->setObjectName(QStringLiteral("groupBox_viewerOptions"));
        sizePolicy.setHeightForWidth(groupBox_viewerOptions->sizePolicy().hasHeightForWidth());
        groupBox_viewerOptions->setSizePolicy(sizePolicy);
        verticalLayout_5 = new QVBoxLayout(groupBox_viewerOptions);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        checkBox_basePart = new QCheckBox(groupBox_viewerOptions);
        checkBox_basePart->setObjectName(QStringLiteral("checkBox_basePart"));
        checkBox_basePart->setChecked(true);

        verticalLayout_5->addWidget(checkBox_basePart);

        checkBox_wireframe = new QCheckBox(groupBox_viewerOptions);
        checkBox_wireframe->setObjectName(QStringLiteral("checkBox_wireframe"));
        checkBox_wireframe->setChecked(true);

        verticalLayout_5->addWidget(checkBox_wireframe);


        verticalLayout_viewer->addWidget(groupBox_viewerOptions);


        horizontalLayout_2->addLayout(verticalLayout_viewer);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "STL Editor", nullptr));
        pushButton_importBase->setText(QApplication::translate("MainWindow", "Import base part", nullptr));
        pushButton_view->setText(QApplication::translate("MainWindow", "View", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Pre-processing", nullptr));
        pushButton_rotateBase->setText(QApplication::translate("MainWindow", "Rotate", nullptr));
        groupBox_hollowing->setTitle(QApplication::translate("MainWindow", "Hollowing", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Offset:", nullptr));
        lineEdit_hollowingOffset->setText(QApplication::translate("MainWindow", "5.0", nullptr));
        label_offsetUnit->setText(QApplication::translate("MainWindow", "mm", nullptr));
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
        label_cellUnit->setText(QApplication::translate("MainWindow", "mm", nullptr));
        checkBox_constantCellSize->setText(QApplication::translate("MainWindow", "Constant cell size", nullptr));
        groupBox_infillCoordinateSystem->setTitle(QApplication::translate("MainWindow", "Coordinate system", nullptr));
        radioButton_infillCoordinateSystem_cartesian->setText(QApplication::translate("MainWindow", "Cartesian", nullptr));
        radioButton_infillCoordinateSystem_cylindrical->setText(QApplication::translate("MainWindow", "Cylindrical", nullptr));
        radioButton_infillCoordinateSystem_spherical->setText(QApplication::translate("MainWindow", "Spherical", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Origin", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "X:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Y:", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Z:", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Cell size", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "X =", nullptr));
        lineEdit_cellSizeX->setText(QApplication::translate("MainWindow", "1.0*x", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Y =", nullptr));
        lineEdit_cellSizeY->setText(QApplication::translate("MainWindow", "1.0*x + 1.0*y", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Z =", nullptr));
        lineEdit_cellSizeZ->setText(QApplication::translate("MainWindow", "1.0*x + 1.0*y + 1.0*z", nullptr));
        checkBox_variableInfill->setText(QApplication::translate("MainWindow", "Variable infill", nullptr));
        checkBox_skipInfilling->setText(QApplication::translate("MainWindow", "Skip infilling", nullptr));
        pushButton_process->setText(QApplication::translate("MainWindow", "Process", nullptr));
        pushButton_save->setText(QApplication::translate("MainWindow", "Save", nullptr));
        groupBox_STLInfo->setTitle(QApplication::translate("MainWindow", "STL info", nullptr));
        label_nTriangles->setText(QApplication::translate("MainWindow", "Number of triangles: 0", nullptr));
        labelWidthX->setText(QApplication::translate("MainWindow", "Width in X: -", nullptr));
        labelWidthY->setText(QApplication::translate("MainWindow", "Width in Y: -", nullptr));
        labelHeightZ->setText(QApplication::translate("MainWindow", "Height in Z: -", nullptr));
        label_baseOrigin->setText(QApplication::translate("MainWindow", "Origin: -", nullptr));
        label_baseCentroid->setText(QApplication::translate("MainWindow", "Centroid: -", nullptr));
        label_baseVolume->setText(QApplication::translate("MainWindow", "Volume: -", nullptr));
        groupBox_viewerOptions->setTitle(QApplication::translate("MainWindow", "Viewer options", nullptr));
        checkBox_basePart->setText(QApplication::translate("MainWindow", "Show base part", nullptr));
        checkBox_wireframe->setText(QApplication::translate("MainWindow", "Wireframe", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
