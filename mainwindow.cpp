#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cube.h"
#include "icosphere.h"
#include "pyramid.h"
#include "triangle.h"
#include "stlfile.h"
#include "utils.h"
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    _nTrianglesBase = 0;
    _nTrianglesProcessed = 0;
    _maxXLength = 0.0;
    _maxYLength = 0.0;
    _maxZLength = 0.0;
    _maxLength = 0.0;
    _minZ = 0.0;
    _maxZ = 0.0;

    _wireframe = true;
    _basePart = true;
    _cellLoaded = false;

    _stlHeader = "";
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_open_clicked() {
    // Gets the file name
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open"), "", tr("STL Files (*.stl);;All files (*)"));
    if (fileName.isEmpty())
        return;

    // Decode the STL file
    STLFile stl(fileName);
    qint32 n = 0;
    _triangs = stl.decode(n);
    if(n < 0)
        return; // Return if input file is invalid

    // Load variables
    _nTrianglesBase = (quint32)n;
    _nTrianglesProcessed = 0;
    _maxXLength = stl.getMaxXLength();
    _maxYLength = stl.getMaxYLength();
    _maxZLength = stl.getMaxZLength();
    _maxLength = stl.getMaxLength();
    _minY = stl.getMinY();
    _maxY = stl.getMaxY();
    _minZ = stl.getMinZ();
    _maxZ = stl.getMaxZ();
    _stlHeader = stl.getHeader();

    // Updates the UI
    ui->labelWidthX->setText("Width in X: " + QString::number(_maxXLength) + " mm");
    ui->labelWidthY->setText("Width in Y: " + QString::number(_maxYLength) + " mm");
    ui->labelHeightZ->setText("Height in Z: " + QString::number(_maxZLength) + " mm");
    ui->pushButton_open->setEnabled(false);
}

void MainWindow::on_pushButton_loadCell_clicked() {
    // Gets the file name
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open"), "", tr("STL Files (*.stl);;All files (*)"));
    if (fileName.isEmpty())
        return;

    // Decode the STL file
    STLFile stl(fileName);
    qint32 n = 0;
    _cell = stl.decode(n);
    if(n < 0)
        return; // Return if input file is invalid

    // Load variables
    _cellMaxXLength = stl.getMaxXLength();
    _cellMaxYLength = stl.getMaxYLength();
    _cellMaxZLength = stl.getMaxZLength();
    _cellMaxLength = stl.getMaxLength();

    _cellLoaded = true;
}

void MainWindow::on_radioButton_cellType_custom_toggled(bool checked) {
    if(checked) {
        ui->pushButton_loadCell->setEnabled(true);
    } else {
        ui->pushButton_loadCell->setEnabled(false);
    }
}

void MainWindow::on_pushButton_process_clicked() {
    int cellType = 0; // None
    if(ui->radioButton_cellType_pyramid->isChecked())
        cellType = 1; // Pyramid
    else if(ui->radioButton_cellType_cube->isChecked())
        cellType = 2; // Cube
    else if(ui->radioButton_cellType_icosphere->isChecked())
        cellType = 3; // Icosphere
    else if(ui->radioButton_cellType_custom->isChecked()) {
        if(_cellLoaded == false) {
            QMessageBox::information(this, tr("Info"), "You need to load the custom cell first.");
            return;
        }
        cellType = 4; // Custom
    }

    bool valid = false;

    float layerThickness = ui->lineEdit_layerThickness->text().toFloat(&valid);
    if(!valid) {
        std::cout << "Invalid input. Using layerThickness = 1 mm\n";
        layerThickness = 1.0;
    }

    int zSteps = (int)(_maxZLength/layerThickness);
    for(int i = 0; i < zSteps; i++) {   // Step layer by layer on z axis
        float z = zSteps*layerThickness;
        std::pair<std::array<float, 2>, std::array<float, 2>> boundaries(Utils::getBoundaries(_triangs, z));

//        int ySteps = (int)((boundaries.second[1]-boundaries.first[1])/layerThickness);
//        int xSteps = (int)((boundaries.second[0]-boundaries.first[0])/layerThickness);
//        for(int j = 0; j < ySteps; j++) {
//            for(int k = 0; k < xSteps; k++) {
//                float maxLength = _maxXLength;
//                if(_maxYLength > maxLength)
//                    maxLength = _maxYLength;
//                if(_maxZLength > maxLength)
//                    maxLength = _maxZLength;
//                if(cellType == 1) {
//                    Pyramid p(maxLength);
//                    p.scale((_maxXLength/maxLength)/fillX, (_maxYLength/maxLength)/fillY, (_maxZLength/maxLength)/fillZ);
//                    p.place(k*(_maxXLength/fillX), j*(_maxYLength/fillY), i*(_maxZLength/fillZ));

//                    std::vector<Triangle> t = p.getFacets();
//                    _triangs.insert(_triangs.end(), t.begin(), t.end());
//                } else if(cellType == 2) {
//                    Cube c(maxLength);
//                    c.scale((_maxXLength/maxLength)/fillX, (_maxYLength/maxLength)/fillY, (_maxZLength/maxLength)/fillZ);
//                    c.place(k*(_maxXLength/fillX), j*(_maxYLength/fillY), i*(_maxZLength/fillZ));

//                    std::vector<Triangle> t = c.getFacets();
//                    _triangs.insert(_triangs.end(), t.begin(), t.end());
//                } else if(cellType == 3) {
//                    Icosphere s(maxLength);
//                    s.scale((_maxXLength/maxLength)/fillX, (_maxYLength/maxLength)/fillY, (_maxZLength/maxLength)/fillZ);
//                    s.place(k*(_maxXLength/fillX), j*(_maxYLength/fillY), i*(_maxZLength/fillZ));

//                    std::vector<Triangle> t = s.getFacets();
//                    _triangs.insert(_triangs.end(), t.begin(), t.end());
//                }

//            }
//        }
    }

    // Updates the UI
    ui->labelNTriangles->setText("Number of triangles: " + _nTrianglesProcessed);

    // Enable save button
    ui->pushButton_save->setEnabled(true);
}

void MainWindow::on_pushButton_save_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save"), "", tr("STL Files (*.stl);;All files (*)"));

    if (fileName.isEmpty())
        return;

    STLFile stl(fileName);
    std::vector<Triangle> vec(_triangs.begin() + _nTrianglesBase, _triangs.end());
    stl.encode(_stlHeader, vec);
}

void MainWindow::on_checkBox_basePart_stateChanged(int arg1){
    _basePart = (arg1==Qt::Unchecked)?false:true;
    update();
}

void MainWindow::on_checkBox_wireframe_stateChanged(int arg1) {
    _wireframe = (arg1==Qt::Unchecked)?false:true;
    update();
}
