#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cube.h"
#include "icosphere.h"
#include "pyramid.h"
#include "customcell.h"
#include "triangle.h"
#include "stlfile.h"
#include "utils.h"
#include "glm/ext.hpp"
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
    _minX = 0.0;
    _maxX = 0.0;
    _minY = 0.0;
    _maxY = 0.0;
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
    _base = stl.decode(n);
    if(n < 0)
        return; // Return if input file is invalid

    // Load variables
    _nTrianglesBase = (quint32)n;
    _nTrianglesProcessed = 0;
    _maxXLength = stl.getMaxXLength();
    _maxYLength = stl.getMaxYLength();
    _maxZLength = stl.getMaxZLength();
    _maxLength = stl.getMaxLength();
    _minX = stl.getMinX();
    _maxX = stl.getMaxX();
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

    // Create to CustomCell object
    _cell = new CustomCell(fileName);
    _cellLoaded = _cell->isInitialized();
}

void MainWindow::on_radioButton_cellType_custom_toggled(bool checked) {
    if(checked) {
        ui->pushButton_loadCell->setEnabled(true);
    } else {
        ui->pushButton_loadCell->setEnabled(false);
    }
}

void MainWindow::on_pushButton_process_clicked() {
    bool skipHollow = ui->checkBox_skipHollowing->isChecked();
    bool skipInfill = ui->checkBox_skipInfilling->isChecked();

    if(skipHollow == false) {
        std::vector<Vertex> v_aux;
        std::vector<Facet> f_aux;
        std::vector<Triangle> t_aux;

        bool valid = false;
        float offset = ui->lineEdit_hollowingOffset->text().toFloat(&valid);
        if(!valid) {
            std::cout << "Invalid input. Using default offset = 5 mm\n";
            offset = 5.0;
        }
        if(ui->checkBox_shell->isChecked() == false) {
            offset *= -1.0;
        }

        _processed.insert(_processed.end(), _base.begin(), _base.end());
        v_aux = Utils::getVertexList(_base, f_aux);
        Utils::offsetVertices(v_aux, f_aux, offset);
        t_aux = Utils::getTriangleList(v_aux, f_aux);
        _base = t_aux;
        Utils::switchNormal(t_aux);
        _processed.insert(_processed.end(), t_aux.begin(), t_aux.end());
        std::vector<std::pair<glm::vec3, glm::vec3>> cont = Utils::getContours(_processed, 10.0);
        std::vector<std::vector<glm::vec3>> conn = Utils::connect(cont);
        std::cout << "conn size: " << conn.size() << std::endl;
//        for(int i = 0; i < conn.size(); i++) {
//            std::cout << "conn[" << i << "] size: " << conn[i].size() << std::endl;
//            for(int j = 0; j < conn[i].size(); j++) {
//                std::cout << "conn[" << i << "][" << j << "]: " << glm::to_string(conn[i].at(j)) << std::endl;
//            }
//        }
//        bool loops = Utils::checkLoops(cont);
//        if(loops) {
//            std::cout << "Loops detected!\n";
//        } else {
//            std::cout << "Loops not detected\n";
//        }
        return;
    }



    if(skipInfill == false) {
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
        float cellThickness = ui->lineEdit_cellThickness->text().toFloat(&valid);
        if(!valid) {
            std::cout << "Invalid input. Using layerThickness = 1 mm\n";
            cellThickness = 1.0;
        }

        Cell *c = NULL;
        if(cellType == 1) {
            c = new Pyramid(cellThickness);
        } else if(cellType == 2) {
            c = new Cube(cellThickness);
        } else if(cellType == 3) {
            c = new Icosphere(cellThickness);
        } else if(cellType == 4) {
            c = _cell;
        } else {    // Default: Pyramid
            c = new Pyramid(cellThickness);
        }

        int zSteps = (int)ceil(_maxZLength/cellThickness);
        for(int i = 0; i < zSteps; i++) {   // Step layer by layer on z axis
            float z = _minZ + i*cellThickness;
            std::vector<Triangle> slice = Utils::slice(_base, z, cellThickness);

    //        std::pair<std::array<float, 2>, std::array<float, 2>> boundaries(Utils::getBoundaries(_base, z, layerThickness));
    //        float xLength = boundaries.second[0]-boundaries.first[0];
    //        float yLength = boundaries.second[1]-boundaries.first[1];

            int xSteps = (int)ceil(_maxXLength/cellThickness);
            int ySteps = (int)ceil(_maxYLength/cellThickness);

            // TODO: optimize by using boundaries
            for(int j = 0; j < ySteps; j++) {
                bool inside = false;
                for(int k = 0; k < xSteps; k++) {
                    bool sw = false;
                    // TODO (OPTIONAL CONFIG): start from the middle and cut the cell on the boundaries
                    float posX = _minX + k*cellThickness;
                    float posY = _minY + j*cellThickness;
                    std::vector<Triangle> aux = Utils::getTrianglesFromBox(slice, posX, posY, z, cellThickness);
                    for(std::vector<Triangle>::iterator it = aux.begin() ; it != aux.end(); ++it) {
                        inside = true;
                        if(it->getNormal().x > 0) {
                            sw = true;
                        }
                    }
                    if(inside) {
                        c->place(posX, posY, z);
                        std::vector<Triangle> t = c->getFacets();
                        _processed.insert(_processed.end(), t.begin(), t.end());
                    }
                    if(sw) {
                        inside = false;
                    }
                }
            }
        }
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
    stl.encode(_stlHeader, _processed);
}

void MainWindow::on_checkBox_basePart_stateChanged(int arg1){
    _basePart = (arg1==Qt::Unchecked)?false:true;
    update();
}

void MainWindow::on_checkBox_wireframe_stateChanged(int arg1) {
    _wireframe = (arg1==Qt::Unchecked)?false:true;
    update();
}
