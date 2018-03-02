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
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <iostream>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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
    _baseImported = false;
    _baseProcessed = false;
    _customCell = false;

    _baseVolume = 0.0;
    _baseCentroid = glm::vec3(0.0, 0.0, 0.0);

    _stlHeader = "";
    _stlUnit = millimetre;

    _importDialog = new ImportDialog(this);
    connect(_importDialog, &ImportDialog::import, this, &MainWindow::importBasePart);
    _rotateDialog = new RotateDialog(this);
    connect(_rotateDialog, &RotateDialog::rotate, this, &MainWindow::rotateBasePart);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::importBasePart(Unit unit)
{
    _stlUnit = unit;

    // Updates the UI
    updateUI();
}

void MainWindow::on_pushButton_importBase_clicked()
{
    // Gets the file name
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Import"), "", tr("STL Files (*.stl);;All files (*)"));
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
    Utils::getCentroid(_base, _baseCentroid, _baseVolume);
    _baseImported = true;

    // Show import dialog (STL file unit selection)
    _importDialog->show();

    // Updates the UI
    ui->doubleSpinBox_infill_originX->setValue(_baseCentroid.x);
    ui->doubleSpinBox_infill_originY->setValue(_baseCentroid.y);
    ui->doubleSpinBox_infill_originZ->setValue(_baseCentroid.z);
    updateUI();
}

void MainWindow::updateUI()
{
    const QChar lowercaseMu(0x03BC);
    QString unit;
    switch(_stlUnit) {
        case micrometre: {
            unit = QString(lowercaseMu) + "m";
        } break;
        case millimetre: {
            unit = "mm";
        } break;
        case centimetre: {
            unit = "cm";
        } break;
        case metre: {
            unit = "m";
        } break;
        case inch: {
            unit = "in";
        } break;
        case foot: {
            unit = "ft";
        } break;
        default: {
            unit = "mm";
        } break;
    }

    ui->label_offsetUnit->setText(unit);
    ui->label_cellUnit->setText(unit);
    ui->labelWidthX->setText("Width in X: " + QString::number(_maxXLength) + " " + unit);
    ui->labelWidthY->setText("Width in Y: " + QString::number(_maxYLength) + " " + unit);
    ui->labelHeightZ->setText("Height in Z: " + QString::number(_maxZLength) + " " + unit);
    ui->label_nTriangles->setText("Number of triangles: " + QString::number(_nTrianglesProcessed));
    ui->label_baseOrigin->setText("Origin: (" + QString::number(_minX) + ", " + QString::number(_minY) + ", " + QString::number(_minZ) + ")");
    ui->label_baseCentroid->setText("Centroid: (" + QString::number(_baseCentroid.x) + ", " + QString::number(_baseCentroid.y) + ", " + QString::number(_baseCentroid.z) + ")");
    ui->label_baseVolume->setText("Volume: " + QString::number(_baseVolume) + " " + unit + "³");
    ui->pushButton_importBase->setEnabled(!_baseImported);
    ui->pushButton_rotateBase->setEnabled(_baseImported && !_baseProcessed);
    ui->pushButton_loadCell->setEnabled(_customCell);
    ui->pushButton_process->setEnabled(_baseImported && !_baseProcessed);
    ui->pushButton_save->setEnabled(_baseProcessed);
}

void MainWindow::insertCell(glm::vec3 pos, glm::vec3 size, Cell *c)
{
    insertCell(pos, size, glm::vec3(0.0f, 0.0f, 0.0f), c);
}

void MainWindow::insertCell(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation, Cell *c)
{
    glm::vec3 cellCenter = pos + (size/2.0);

    // Check if is inside the mesh or if is overlaping the surfaces
    if(Utils::isInsideMesh(_base, cellCenter, false) ||
       Utils::getTrianglesFromBox(_base, pos, std::max(std::max(size.x, size.y), size.z)).size() > 0) {
        c->rotateX(rotation.x);
        c->rotateY(rotation.y);
        c->rotateZ(rotation.z);
        c->resize(size);
        c->place(pos);
        std::vector<Triangle> t = c->getFacets();
        _processed.insert(_processed.end(), t.begin(), t.end());
    }
}

void MainWindow::rotateBasePart(float angle, int axis)
{
    angle = degreesToRadians(angle);
    if(axis == 0) {
        Utils::rotateX(_base, angle);
    } else if(axis == 1) {
        Utils::rotateY(_base, angle);
    } else if(axis == 2) {
        Utils::rotateZ(_base, angle);
    }
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

void MainWindow::on_radioButton_cellType_custom_toggled(bool checked)
{
    _customCell = checked;

    // Updates the UI
    updateUI();
}

void MainWindow::on_pushButton_process_clicked()
{
    // TODO: change infill custom origin min/max values (QDoubleSpinBox)
    bool customOrigin = true;
    bool constantCell = ui->checkBox_constantCellSize->isChecked();
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

//        _processed.insert(_processed.end(), _base.begin(), _base.end());
        v_aux = Utils::getVertexList(_base, f_aux);
        Utils::offsetVertices(v_aux, f_aux, offset);
        t_aux = Utils::getTriangleList(v_aux, f_aux);
        _offset = t_aux;
//        Utils::switchNormal(t_aux);
//        _processed.insert(_processed.end(), t_aux.begin(), t_aux.end());

//        std::vector<std::pair<glm::vec3, glm::vec3>> intseg = Utils::getIntersectionSegments(_processed, 36.0);
////        std::cout << "intersect segments size: " << intseg.size() << std::endl;
////        for(int i = 0; i < intseg.size(); i++) {
////            std::cout << intseg[i].first.x << ", " << intseg[i].first.y << ", " << intseg[i].second.x << ", " << intseg[i].second.y << std::endl;
////        }
//        std::vector<std::vector<glm::vec3>> cont = Utils::getContours(intseg, 0.00001f);

//        std::vector<std::vector<glm::vec2>> cont2D = Utils::convertContourTo2D(cont);
//        std::vector<std::vector<glm::vec2>> contours = Utils::splitLoopsFromContours2D(cont2D);
//        std::cout << "contours size: " << contours.size() << std::endl;

//        std::vector<std::vector<glm::vec2>> contoursBase;
//        contoursBase.push_back(contours[0]);
//        std::vector<std::vector<glm::vec2>> contoursOffset;
//        contoursOffset.insert(contoursOffset.begin(), contours.begin()+1, contours.end());
//        Utils::removeLoops2D(_processed, 36.0, contoursBase, contoursOffset, offset/2.0, 0.0001f);

//        bool loops = Utils::checkLoops(cont);
//        if(loops) {
//            std::cout << "Loops detected!\n";
//        } else {
//            std::cout << "Loops not detected\n";
//        }

//        return;

        //        for(int i = 0; i < conn.size(); i++) {
        //            std::cout << "conn[" << i << "] size: " << conn[i].size() << std::endl;
        //            for(int j = 0; j < conn[i].size(); j++) {
        //                std::cout << "conn[" << i << "][" << j << "]: " << glm::to_string(conn[i].at(j)) << std::endl;
        //            }
        //        }
    } else {
        _offset = _base;
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

        float cellThickness;
        bool valid = false;
        cellThickness = ui->lineEdit_cellThickness->text().toFloat(&valid);
        if(!valid) {
            std::cout << "Invalid input. Using layerThickness = 1 mm\n";
            cellThickness = 1.0;
        }

        CoordinateSystem coordSystem;
        if(ui->radioButton_infillCoordinateSystem_cartesian->isChecked()) {
            coordSystem = cartesian;    // Cartesian coordinate system
        } else if(ui->radioButton_infillCoordinateSystem_cylindrical->isChecked()) {
            coordSystem = cylindrical;  // Cylindrical coordinate system
        } else if(ui->radioButton_infillCoordinateSystem_spherical->isChecked()) {
            coordSystem = spherical;    // Spherical coordinate system
        } else {
            coordSystem = cartesian;    // Default: Cartesian coordinate system
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

        glm::vec3 infillOrigin;
        if(customOrigin) {
            infillOrigin.x = ui->doubleSpinBox_infill_originX->value();
            infillOrigin.y = ui->doubleSpinBox_infill_originY->value();
            infillOrigin.z = ui->doubleSpinBox_infill_originZ->value();
        }

        if(constantCell) {
            if(coordSystem == spherical) {
                std::cout << "centroid: " << glm::to_string(_baseCentroid) << std::endl;
                int rSteps = (int)ceil(_maxLength/cellThickness);
                for(int r = 0; r < rSteps; r++) {   // Step spherical surface on r coordinate
                    if(r == 0) {
                        float posX = _baseCentroid.x - (cellThickness/2.0);
                        float posY = _baseCentroid.y - (cellThickness/2.0);
                        float posZ = _baseCentroid.z - (cellThickness/2.0);
                        glm::vec3 pos(posX, posY, posZ);
                        glm::vec3 cellCenter = glm::vec3(posX+(cellThickness/2.0), posY+(cellThickness/2.0), posZ+(cellThickness/2.0));
                        if(Utils::isInsideMesh(_base, cellCenter, true) ||
                           Utils::getTrianglesFromBox(_base, pos, cellThickness).size() > 0) {
                            c->place(posX, posY, posZ);
                            std::vector<Triangle> t = c->getFacets();
                            _processed.insert(_processed.end(), t.begin(), t.end());
                        }
                    }
                    float radius = r*cellThickness;
                    float circunferece = 2.0*M_PI*radius;
                    int phiSteps = (int)ceil((circunferece/2.0)/cellThickness);
                    for(int phi = 0; phi <= phiSteps; phi++) {
                        float phiAngle = ((float)phi/(float)phiSteps)*180.0;
                        if(fabsf(sin(degreesToRadians(phiAngle))) < EPSILON) {
                            float posX = _baseCentroid.x - (cellThickness/2.0);
                            float posY = _baseCentroid.y - (cellThickness/2.0);
                            float posZ = _baseCentroid.z - (cellThickness/2.0) + radius;
                            glm::vec3 pos(posX, posY, posZ);
                            glm::vec3 cellCenter = glm::vec3(posX+(cellThickness/2.0), posY+(cellThickness/2.0), posZ+(cellThickness/2.0));
                            if(Utils::isInsideMesh(_base, cellCenter, true) ||
                               Utils::getTrianglesFromBox(_base, pos, cellThickness).size() > 0) {
                                c->place(posX, posY, posZ);
                                std::vector<Triangle> t = c->getFacets();
                                _processed.insert(_processed.end(), t.begin(), t.end());
                            }
                        }
                        circunferece = 2.0*M_PI*(radius*sin(degreesToRadians(phiAngle)));
                        int thetaSteps = (int)ceil(circunferece/cellThickness);
                        for(int theta = 0; theta < thetaSteps; theta++) {
                            float thetaAngle = ((float)theta/(float)thetaSteps)*360.0;
                            float posX = _baseCentroid.x - (cellThickness/2.0) + radius*sin(degreesToRadians(phiAngle))*cos(degreesToRadians(thetaAngle));
                            float posY = _baseCentroid.y - (cellThickness/2.0) + radius*sin(degreesToRadians(phiAngle))*sin(degreesToRadians(thetaAngle));
                            float posZ = _baseCentroid.z - (cellThickness/2.0) + radius*cos(degreesToRadians(phiAngle));
                            glm::vec3 pos(posX, posY, posZ);
                            glm::vec3 cellCenter = glm::vec3(posX+(cellThickness/2.0), posY+(cellThickness/2.0), posZ+(cellThickness/2.0));
                            if(Utils::isInsideMesh(_base, cellCenter, false) ||
                               Utils::getTrianglesFromBox(_base, pos, cellThickness).size() > 0) {
                                c->place(posX, posY, posZ);
                                std::vector<Triangle> t = c->getFacets();
                                _processed.insert(_processed.end(), t.begin(), t.end());
                            }
                        }
                    }
                }
            } else {
                int zSteps = (int)ceil(_maxZLength/cellThickness);
                glm::vec2 centroid;
                for(int i = 0; i < zSteps; i++) {   // Step layer by layer on z axis
                    float z = _minZ + i*cellThickness;
                    std::vector<Triangle> slice = Utils::slice(_base, z, cellThickness);

                    // Get the slice contour centroid
                    std::vector<std::pair<glm::vec3, glm::vec3>> intersectionSegments = Utils::getIntersectionSegments(slice, z + cellThickness/2.0);
                    if(intersectionSegments.size() < 3) {
                        continue;
                    }
                    std::vector<std::vector<glm::vec3>> contours = Utils::getContours(intersectionSegments, 0.00001f);
                    std::vector<std::vector<glm::vec2>> contours2D = Utils::convertContourTo2D(contours);
                    assert(Utils::getCentroid(*(contours2D.begin()), centroid) == 0);

                    if(coordSystem == cartesian) {
                        int xSteps = (int)ceil(_maxXLength/cellThickness);
                        int ySteps = (int)ceil(_maxYLength/cellThickness);
                        // TODO: optimize by using boundaries
                        for(int j = 0; j < ySteps; j++) {
                            for(int k = 0; k < xSteps; k++) {
                                // TODO (OPTIONAL CONFIG): start from the middle and cut the cell on the boundaries
                                float posX = _minX + k*cellThickness;
                                float posY = _minY + j*cellThickness;
                                glm::vec3 pos(posX, posY, z);
                                // Check if is inside the mesh or if is overlaping the surfaces
                                glm::vec3 cellCenter = glm::vec3(posX+(cellThickness/2.0), posY+(cellThickness/2.0), z+(cellThickness/2.0));
                                if(Utils::isInsideMesh(slice, cellCenter, true) ||
                                   Utils::getTrianglesFromBox(slice, pos, cellThickness).size() > 0) {
                                    c->place(posX, posY, z);
                                    std::vector<Triangle> t = c->getFacets();
                                    _processed.insert(_processed.end(), t.begin(), t.end());
                                }
                            }
                        }
                    } else if(coordSystem == cylindrical) {
                        int rSteps = (int)ceil(_maxXLength/cellThickness);
                        if(rSteps < (int)ceil(_maxYLength/cellThickness)) {
                            rSteps = (int)ceil(_maxYLength/cellThickness);
                        }
                        for(int r = 0; r < rSteps; r++) {
                            if(r == 0) {
                                float posX = centroid.x - (cellThickness/2.0);
                                float posY = centroid.y - (cellThickness/2.0);
                                glm::vec3 pos(posX, posY, z);
                                glm::vec3 cellCenter = glm::vec3(posX+(cellThickness/2.0), posY+(cellThickness/2.0), z+(cellThickness/2.0));
                                if(Utils::isInsideMesh(slice, cellCenter, true) ||
                                   Utils::getTrianglesFromBox(slice, pos, cellThickness).size() > 0) {
                                    c->place(posX, posY, z);
                                    std::vector<Triangle> t = c->getFacets();
                                    _processed.insert(_processed.end(), t.begin(), t.end());
                                }
                            }
                            float radius = r*cellThickness;
                            float circunferece = 2.0*M_PI*radius;
                            int phiSteps = (int)ceil(circunferece/cellThickness);
                            for(int phi = 0; phi < phiSteps; phi++) {
                                float posX = centroid.x - (cellThickness/2.0) + radius*cos(degreesToRadians(((float)phi/(float)phiSteps)*360.0));
                                float posY = centroid.y - (cellThickness/2.0) + radius*sin(degreesToRadians(((float)phi/(float)phiSteps)*360.0));
                                glm::vec3 pos(posX, posY, z);
                                glm::vec3 cellCenter = glm::vec3(posX+(cellThickness/2.0), posY+(cellThickness/2.0), z+(cellThickness/2.0));
                                if(Utils::isInsideMesh(slice, cellCenter, true) ||
                                   Utils::getTrianglesFromBox(slice, pos, cellThickness).size() > 0) {
                                    c->place(posX, posY, z);
                                    std::vector<Triangle> t = c->getFacets();
                                    _processed.insert(_processed.end(), t.begin(), t.end());
                                }
                            }
                        }
                    }
                }
            }
        } else {
            // Approach 1
            if(coordSystem == cartesian) {
                float posX = infillOrigin.x;
                while(posX < _maxX) {
                    float x = posX - infillOrigin.x;
                    float posY = infillOrigin.y;
                    float cellHeightX = std::min((fabsf(x))/2.0f, 25.0f);
                    cellHeightX = std::max(cellHeightX, 2.5f);
                    // Q1
                    while(posY < _maxY) {
                        float y = posY - infillOrigin.y;
                        float posZ = _minZ;
                        float cellHeightY = std::min((fabsf(x) + fabsf(y))/5.0f, 25.0f);
                        cellHeightY = std::max(cellHeightY, 2.5f);
                        while(posZ < _maxZ) {
                            float z = posZ - infillOrigin.z;
                            // Limit cell height
                            float cellHeightZ = std::min((fabsf(x) + fabsf(y) + fabsf(z))/10.0f, 25.0f);
                            cellHeightZ = std::max(cellHeightZ, 2.5f);

                            glm::vec3 pos(posX, posY, posZ);
                            glm::vec3 size(cellHeightX, cellHeightY, cellHeightZ);
                            insertCell(pos, size, c);

                            posZ += cellHeightZ;
                        }
                        posY += cellHeightY;
                    }
                    posY = infillOrigin.y;
                    // Q4
                    while(posY > _minY) {
                        float y = posY - infillOrigin.y;
                        float posZ = _minZ;
                        float cellHeightY = std::min((fabsf(x) + fabsf(y))/5.0f, 25.0f);
                        cellHeightY = std::max(cellHeightY, 2.5f);
                        while(posZ < _maxZ) {
                            float z = posZ - infillOrigin.z;
                            // Limit cell height
                            float cellHeightZ = std::min((fabsf(x) + fabsf(y) + fabsf(z))/10.0f, 25.0f);
                            cellHeightZ = std::max(cellHeightZ, 2.5f);

                            glm::vec3 pos(posX, posY-cellHeightY, posZ);
                            glm::vec3 size(cellHeightX, cellHeightY, cellHeightZ);
                            insertCell(pos, size, c);

                            posZ += cellHeightZ;
                        }
                        posY -= cellHeightY;
                    }
                    posX += cellHeightX;
                }
                posX = infillOrigin.x;
                while(posX > _minX) {
                    float x = posX - infillOrigin.x;
                    float posY = infillOrigin.y;
                    float cellHeightX = std::min((fabsf(x))/2.0f, 25.0f);
                    cellHeightX = std::max(cellHeightX, 2.5f);
                    // Q2
                    while(posY < _maxY) {
                        float y = posY - infillOrigin.y;
                        float posZ = _minZ;
                        float cellHeightY = std::min((fabsf(x) + fabsf(y))/5.0f, 25.0f);
                        cellHeightY = std::max(cellHeightY, 2.5f);
                        while(posZ < _maxZ) {
                            float z = posZ - infillOrigin.z;
                            // Limit cell height
                            float cellHeightZ = std::min((fabsf(x) + fabsf(y) + fabsf(z))/10.0f, 25.0f);
                            cellHeightZ = std::max(cellHeightZ, 2.5f);

                            glm::vec3 pos(posX-cellHeightX, posY, posZ);
                            glm::vec3 size(cellHeightX, cellHeightY, cellHeightZ);
                            insertCell(pos, size, c);

                            posZ += cellHeightZ;
                        }
                        posY += cellHeightY;
                    }
                    posY = infillOrigin.y;
                    // Q3
                    while(posY > _minY) {
                        float y = posY - infillOrigin.y;
                        float posZ = _minZ;
                        float cellHeightY = std::min((fabsf(x) + fabsf(y))/5.0f, 25.0f);
                        cellHeightY = std::max(cellHeightY, 2.5f);
                        while(posZ < _maxZ) {
                            float z = posZ - infillOrigin.z;
                            // Limit cell height
                            float cellHeightZ = std::min((fabsf(x) + fabsf(y) + fabsf(z))/10.0f, 25.0f);
                            cellHeightZ = std::max(cellHeightZ, 2.5f);

                            glm::vec3 pos(posX-cellHeightX, posY-cellHeightY, posZ);
                            glm::vec3 size(cellHeightX, cellHeightY, cellHeightZ);
                            insertCell(pos, size, c);

                            posZ += cellHeightZ;
                        }
                        posY -= cellHeightY;
                    }
                    posX -= cellHeightX;
                }
            } else if(coordSystem == cylindrical) {
                // This should fail if the infill origin is outside the cylinder
                float maxR = _maxXLength;
                if(maxR < _maxYLength) {
                    maxR = _maxYLength;
                }
                float r = 0;
                while(r < maxR) {
                    float cellSizeX = std::min(fabsf(r)/4.0f, 25.0f);
                    cellSizeX = std::max(cellSizeX, 2.5f);
                    float phi = 0.0;
                    while(phi < 360.0) {
                        float cellSizeY = 2.5f;//std::min(r + r*(float)cos(degreesToRadians(phi))/2.0f, 25.0f);
                        cellSizeY = std::max(cellSizeY, 2.5f);
                        float posX = infillOrigin.x + r*cos(degreesToRadians(phi));
                        float posY = infillOrigin.y + r*sin(degreesToRadians(phi));
                        float z = infillOrigin.z;
                        while(z < _maxZ) {
                            float posZ = z;
                            float cellSizeZ = std::min(r*fabsf(cos(degreesToRadians(phi)))/4.0f, 25.0f);
                            cellSizeZ = std::max(cellSizeZ, 2.5f);
                            glm::vec3 pos(posX, posY, posZ);
                            glm::vec3 size(cellSizeX, cellSizeY, cellSizeZ);
//                            glm::vec3 rotation(0.0, 0.0, degreesToRadians(dPhi));
                            // Two approaches: cells are rotated with the cylindical orientation or cells are rotate with the cartesian orientation
                            // Approach taken: rotated with the cylindrical orientation
                            //                            insertCell(pos, size, rotation, c);
                            insertCell(pos, size, c);
                            z += cellSizeZ;
                        }
                        z = infillOrigin.z;
                        while(z > _minZ) {
                            float posZ = z;
                            float cellSizeZ = std::min(r*fabsf(cos(degreesToRadians(phi)))/4.0f, 25.0f);
                            cellSizeZ = std::max(cellSizeZ, 2.5f);
                            glm::vec3 pos(posX, posY, posZ-cellSizeZ);
                            glm::vec3 size(cellSizeX, cellSizeY, cellSizeZ);
//                            glm::vec3 rotation(0.0, 0.0, degreesToRadians(dPhi));
                            // Two approaches: cells are rotated with the cylindical orientation or cells are rotate with the cartesian orientation
                            // Approach taken: rotated with the cylindrical orientation
//                            insertCell(pos, size, rotation, c);
                            insertCell(pos, size, c);
                            z -= cellSizeZ;
                        }
                        float radius = r;
                        float circunferece = 2.0*M_PI*radius;
                        float phiSteps = cellSizeY/circunferece;
                        phi += (phiSteps*360.0);
                    }
                    r += cellSizeX;
                }
            }
        }
        // Trimm
        CorkTriMesh c1 = Utils::meshToCorkTriMesh(_offset);
        CorkTriMesh c2 = Utils::meshToCorkTriMesh(_processed);
        CorkTriMesh *cork = new CorkTriMesh;
        computeIntersection(c1, c2, cork);
        _processed = Utils::corkTriMeshToMesh(*cork);
    }

    if(skipHollow == false) {
        Utils::switchNormal(_offset);
        if(skipInfill == false) {
            _base.insert(_base.begin(), _offset.begin(), _offset.end());

            // Trimm
//            CorkTriMesh c1 = Utils::meshToCorkTriMesh(_base);
//            CorkTriMesh c2 = Utils::meshToCorkTriMesh(_processed);
//            CorkTriMesh *cork = new CorkTriMesh;
//            computeIntersection(c1, c2, cork);
//            _processed = Utils::corkTriMeshToMesh(*cork);
            _processed.insert(_processed.begin(), _base.begin(), _base.end());
        } else {
            _processed.insert(_processed.begin(), _base.begin(), _base.end());
            _processed.insert(_processed.begin(), _offset.begin(), _offset.end());
        }
    }

    _baseProcessed = true;

    // Updates the UI
    updateUI();
}

void MainWindow::on_pushButton_save_clicked()
{
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

void MainWindow::on_pushButton_rotateBase_clicked()
{
    _rotateDialog->show();
}
