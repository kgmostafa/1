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
#include "3rd_party/tinyexpr/tinyexpr.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <iostream>
#include <QMessageBox>
#include <QInputDialog>
//#include <igl/opengl/glfw/Viewer.h>
#include <igl/copyleft/cork/from_cork_mesh.h>
#include <igl/copyleft/cork/to_cork_mesh.h>
#include <igl/copyleft/cgal/mesh_boolean.h>
#include <igl/copyleft/cork/mesh_boolean.h>
#include <Eigen/Dense>
#include <Eigen/Sparse>

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

    _exprX = NULL;
    _exprY = NULL;
    _exprZ = NULL;

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
    ui->doubleSpinBox_region_fromX->setValue(_minX);
    ui->doubleSpinBox_region_fromY->setValue(_minY);
    ui->doubleSpinBox_region_fromZ->setValue(_minZ);
    ui->doubleSpinBox_region_toX->setValue(_maxX);
    ui->doubleSpinBox_region_toY->setValue(_maxY);
    ui->doubleSpinBox_region_toZ->setValue(_maxZ);
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
//    ui->label_cellUnit->setText(unit);
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
       Utils::getTrianglesFromBox(_base, pos, size).size() > 0) {
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

void MainWindow::on_pushButton_loadCell_clicked()
{
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
    bool variableInfill = ui->checkBox_variableInfill->isChecked();
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

        Cell *cell = NULL;
        if(cellType == 1) {
            cell = new Pyramid();
        } else if(cellType == 2) {
            cell = new Cube();
        } else if(cellType == 3) {
            cell = new Icosphere();
        } else if(cellType == 4) {
            cell = _cell;
        } else {    // Default: Pyramid
            cell = new Pyramid();
        }

        glm::vec3 infillOrigin;
        if(customOrigin) {
            infillOrigin.x = ui->doubleSpinBox_infill_originX->value();
            infillOrigin.y = ui->doubleSpinBox_infill_originY->value();
            infillOrigin.z = ui->doubleSpinBox_infill_originZ->value();
        }

        // TODO: handle number of variables per axis
        te_variable vars[] = {{"x", &_varX}, {"y", &_varY}, {"z", &_varZ}};
        glm::vec3 cellSize(0.0f, 0.0f, 0.0f);
        if(variableInfill) {
            int errX;
            QByteArray xBA = ui->lineEdit_cellSizeX->text().toLatin1();
            const char *xString = xBA.data();
            _exprX = te_compile(xString, vars, 3, &errX);

            int errY;
            QByteArray yBA = ui->lineEdit_cellSizeY->text().toLatin1();
            const char *yString = yBA.data();
            _exprY = te_compile(yString, vars, 3, &errY);

            int errZ;
            QByteArray zBA = ui->lineEdit_cellSizeZ->text().toLatin1();
            const char *zString = zBA.data();
            _exprZ = te_compile(zString, vars, 3, &errZ);

            if(_exprX && _exprY && _exprZ) {
            } else {
                // TODO: stop processing here if parse fails (_expr can be NULL).
                printf("Parse error at x: %d\n", errX);
                printf("Parse error at y: %d\n", errY);
                printf("Parse error at z: %d\n", errZ);
            }
        } else {
            bool valid = false;
            cellSize.x = ui->lineEdit_cellSizeX->text().toFloat(&valid);
            if(!valid) {
                // TODO: show error dialog
                cellSize.x = 5.0f;
            }
            cellSize.y = ui->lineEdit_cellSizeY->text().toFloat(&valid);
            if(!valid) {

                cellSize.y = 5.0f;
            }
            cellSize.z = ui->lineEdit_cellSizeZ->text().toFloat(&valid);
            if(!valid) {

                cellSize.z = 5.0f;
            }

        }

        switch(coordSystem) {
            case cartesian: {
                if(variableInfill) {
                    variableCartesian(cell, infillOrigin);
                } else {
                    simpleCartesian(cell, cellSize);
                }
            } break;
            case cylindrical: {
                if(variableInfill) {
                    variableCylindrical(cell, infillOrigin);
                } else {
                    simpleCylindrical(cell, cellSize);
                }
            } break;
            case spherical: {
                if(variableInfill) {
                    std::cerr << "TODO: variable infill with spherical coordinate system\n";
                } else {
                    simpleSpherical(cell, cellSize);
                }
            } break;
        }


//            } else if(coordSystem == spherical) {
//                std::cout << "TODO\n";
//                // This should fail if the infill origin is outside the cylinder
//                float maxR = _maxXLength;
//                if(maxR < _maxYLength) {
//                    maxR = _maxYLength;
//                }
//                if(maxR < _maxZLength) {
//                    maxR = _maxZLength;
//                }
//                float r = 0;
//                while(r < maxR) {
//                    float cellSizeX = std::min(fabsf(r)/4.0f, 25.0f);
//                    cellSizeX = std::max(cellSizeX, 2.5f);
//                    float theta = 0.0;
//                    float circunferece = 2.0*M_PI*r;
//                    while(theta < 360.0) {

//                        float cellSizeY = 2.5f;//std::min(r + r*(float)cos(degreesToRadians(phi))/2.0f, 25.0f);
//                        cellSizeY = std::max(cellSizeY, 2.5f);
//                        float phi = 0.0;
//                        while(phi < 180.0) {
//                            circunferece = 2.0*M_PI*(r*sin(degreesToRadians(phi)));
//                            float cellSizeZ = std::min(fabsf(r)/4.0f, 25.0f);
//                            cellSizeZ = std::max(cellSizeZ, 2.5f);
//                            float posX = _baseCentroid.x - (cellThickness/2.0) + r*sin(degreesToRadians(phi))*cos(degreesToRadians(theta));
//                            float posY = _baseCentroid.y - (cellThickness/2.0) + r*sin(degreesToRadians(phi))*sin(degreesToRadians(theta));
//                            float posZ = _baseCentroid.z - (cellThickness/2.0) + r*cos(degreesToRadians(phi));
//                            glm::vec3 pos(posX, posY, posZ);
//                            glm::vec3 size(cellSizeX, cellSizeY, cellSizeZ);
//                            // Two approaches: cells are rotated with the cylindical orientation or cells are rotate with the cartesian orientation
//                            insertCell(pos, size, c);
//                            float phiSteps = cellSizeY/circunferece;
//                            phi += (phiSteps*180.0);
//                        }
//                        float phiSteps = cellSizeY/circunferece;
//                        phi += (phiSteps*180.0);
//                    }
//                    for(int phi = 0; phi <= phiSteps; phi++) {
//                        float phiAngle = ((float)phi/(float)phiSteps)*180.0;
//                        circunferece = 2.0*M_PI*(radius*sin(degreesToRadians(phiAngle)));
//                        int thetaSteps = (int)ceil(circunferece/cellThickness);
//                        for(int theta = 0; theta < thetaSteps; theta++) {
//                            float thetaAngle = ((float)theta/(float)thetaSteps)*360.0;

//                            glm::vec3 pos(posX, posY, posZ);
//                            glm::vec3 cellCenter = glm::vec3(posX+(cellThickness/2.0), posY+(cellThickness/2.0), posZ+(cellThickness/2.0));
//                            if(Utils::isInsideMesh(_base, cellCenter, false) ||
//                               Utils::getTrianglesFromBox(_base, pos, cellThickness).size() > 0) {
//                                c->place(posX, posY, posZ);
//                                std::vector<Triangle> t = c->getFacets();
//                                _processed.insert(_processed.end(), t.begin(), t.end());
//                            }
//                        }
//                    }
//                    while(phi < 360.0) {
//                        float cellSizeY = 2.5f;//std::min(r + r*(float)cos(degreesToRadians(phi))/2.0f, 25.0f);
//                        cellSizeY = std::max(cellSizeY, 2.5f);
//                        float posX = infillOrigin.x + r*cos(degreesToRadians(phi));
//                        float posY = infillOrigin.y + r*sin(degreesToRadians(phi));
//                        float z = infillOrigin.z;
//                        while(z < _maxZ) {
//                            float posZ = z;
//                            float cellSizeZ = std::min(r*fabsf(cos(degreesToRadians(phi)))/4.0f, 25.0f);
//                            cellSizeZ = std::max(cellSizeZ, 2.5f);
//                            glm::vec3 pos(posX, posY, posZ);
//                            glm::vec3 size(cellSizeX, cellSizeY, cellSizeZ);
////                            glm::vec3 rotation(0.0, 0.0, degreesToRadians(dPhi));
//                            // Two approaches: cells are rotated with the cylindical orientation or cells are rotate with the cartesian orientation
//                            // Approach taken: rotated with the cylindrical orientation
//                            //                            insertCell(pos, size, rotation, c);
//                            insertCell(pos, size, c);
//                            z += cellSizeZ;
//                        }
//                        z = infillOrigin.z;
//                        while(z > _minZ) {
//                            float posZ = z;
//                            float cellSizeZ = std::min(r*fabsf(cos(degreesToRadians(phi)))/4.0f, 25.0f);
//                            cellSizeZ = std::max(cellSizeZ, 2.5f);
//                            glm::vec3 pos(posX, posY, posZ-cellSizeZ);
//                            glm::vec3 size(cellSizeX, cellSizeY, cellSizeZ);
////                            glm::vec3 rotation(0.0, 0.0, degreesToRadians(dPhi));
//                            // Two approaches: cells are rotated with the cylindical orientation or cells are rotate with the cartesian orientation
//                            // Approach taken: rotated with the cylindrical orientation
////                            insertCell(pos, size, rotation, c);
//                            insertCell(pos, size, c);
//                            z -= cellSizeZ;
//                        }
//                        float radius = r;
//                        float circunferece = 2.0*M_PI*radius;
//                        float phiSteps = cellSizeY/circunferece;
//                        phi += (phiSteps*360.0);
//                    }
//                    r += cellSizeX;
//                }
//            }
//        }
        // Trimm
        Eigen::MatrixXd vOffset;
        Eigen::MatrixXi fOffset;
        Eigen::MatrixXd vProcessed;
        Eigen::MatrixXi fProcessed;

        Eigen::MatrixXd vOutput;
        Eigen::MatrixXi fOutput;
        CorkTriMesh c1 = Utils::meshToCorkTriMesh(_offset);
        CorkTriMesh c2 = Utils::meshToCorkTriMesh(_processed);

        igl::copyleft::cork::from_cork_mesh(c1, vOffset, fOffset);
        igl::copyleft::cork::from_cork_mesh(c2, vProcessed, fProcessed);
        igl::copyleft::cgal::mesh_boolean(vOffset, fOffset, vProcessed, fProcessed, igl::MESH_BOOLEAN_TYPE_INTERSECT, vOutput, fOutput);

        CorkTriMesh cOut;
        igl::copyleft::cork::to_cork_mesh(vOutput, fOutput, cOut);

        _processed = Utils::corkTriMeshToMesh(cOut);
    }

    if(skipHollow == false) {
        // TODO: if the offset is positive, we should switch the _base normals
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

void MainWindow::simpleCartesian(Cell *cell, glm::vec3 cellSize)
{
    std::cout << glm::to_string(cellSize) << std::endl;
    int zSteps = (int)ceil(_maxZLength/cellSize.z);
    glm::vec2 centroid;
    glm::vec3 pos(_minX, _minY, _minZ);
    for(int i = 0; i < zSteps; i++) {   // Step layer by layer on z axis
        pos.z = _minZ + i*cellSize.z;
        std::vector<Triangle> slice = Utils::slice(_base, pos.z, cellSize.z);

        // Get the slice contour centroid
        std::vector<std::pair<glm::vec3, glm::vec3>> intersectionSegments = Utils::getIntersectionSegments(slice, pos.z + cellSize.z/2.0);
        if(intersectionSegments.size() < 3) {
            continue;
        }
        std::vector<std::vector<glm::vec3>> contours = Utils::getContours(intersectionSegments, 0.00001f);
        std::vector<std::vector<glm::vec2>> contours2D = Utils::convertContourTo2D(contours);
        assert(Utils::getCentroid(*(contours2D.begin()), centroid) == 0);
        int xSteps = (int)ceil(_maxXLength/cellSize.x);
        int ySteps = (int)ceil(_maxYLength/cellSize.y);

        for(int j = 0; j < ySteps; j++) {
            for(int k = 0; k < xSteps; k++) {
                pos.x = _minX + k*cellSize.x;
                pos.y = _minY + j*cellSize.y;
                // Try to insert cell
                insertCell(pos, cellSize, cell);
            }
        }
    }
}

void MainWindow::simpleCylindrical(Cell *cell, glm::vec3 cellSize)
{
    int zSteps = (int)ceil(_maxZLength/cellSize.z);
    glm::vec2 centroid;
    glm::vec3 pos(_minX, _minY, _minZ);
    for(int i = 0; i < zSteps; i++) {   // Step layer by layer on z axis
        pos.z = _minZ + i*cellSize.z;
        std::vector<Triangle> slice = Utils::slice(_base, pos.z, cellSize.z);

        // Get the slice contour centroid
        std::vector<std::pair<glm::vec3, glm::vec3>> intersectionSegments = Utils::getIntersectionSegments(slice, pos.z + cellSize.z/2.0);
        if(intersectionSegments.size() < 3) {
            continue;
        }
        std::vector<std::vector<glm::vec3>> contours = Utils::getContours(intersectionSegments, 0.00001f);
        std::vector<std::vector<glm::vec2>> contours2D = Utils::convertContourTo2D(contours);
        assert(Utils::getCentroid(*(contours2D.begin()), centroid) == 0);

        // TODO: check if this is the best way to get the rSteps
        int rSteps = (int)ceil(_maxXLength/cellSize.x);
        float radiusStep = cellSize.x;
        if(rSteps < (int)ceil(_maxYLength/cellSize.y)) {
            rSteps = (int)ceil(_maxYLength/cellSize.y);
            radiusStep = cellSize.y;
        }
        for(int r = 0; r < rSteps; r++) {
            if(r == 0) {
                pos.x = centroid.x - (cellSize.x/2.0);
                pos.y = centroid.y - (cellSize.y/2.0);
                // Try to insert cell
                insertCell(pos, cellSize, cell);
            }
            float radius = r*radiusStep;
            float circunferece = 2.0*M_PI*radius;
            int phiSteps = (int)ceil(circunferece/radiusStep);
            for(int phi = 0; phi < phiSteps; phi++) {
                pos.x = centroid.x - (cellSize.x/2.0) + radius*cos(degreesToRadians(((float)phi/(float)phiSteps)*360.0));
                pos.y = centroid.y - (cellSize.y/2.0) + radius*sin(degreesToRadians(((float)phi/(float)phiSteps)*360.0));
                // Try to insert cell
                insertCell(pos, cellSize, cell);
            }
        }
    }
}

void MainWindow::simpleSpherical(Cell *cell, glm::vec3 cellSize)
{
    glm::vec3 pos = _baseCentroid - (cellSize/2.0f);
    float radiusStep = std::min(cellSize.x, cellSize.y);
    int rSteps = (int)ceil(_maxLength/radiusStep);
    for(int r = 0; r < rSteps; r++) {   // Step spherical surface on r coordinate
        if(r == 0) {
            // Try to insert cell
            insertCell(pos, cellSize, cell);
        }
        float radius = r*cellSize.z;
        float circunferecePhi = 2.0*M_PI*radius;
        // TODO: check if this is the best way to get phiSteps
        int phiSteps = (int)ceil((circunferecePhi/2.0)/cellSize.z);
        for(int phi = 0; phi <= phiSteps; phi++) {
            float phiAngle = ((float)phi/(float)phiSteps)*180.0;
            if(fabsf(sin(degreesToRadians(phiAngle))) < EPSILON) {
                pos = _baseCentroid - (cellSize/2.0f);
                pos.z += radius;
                // Try to insert cell
                insertCell(pos, cellSize, cell);
            }
            radius = r*radiusStep;
            float circunfereceTheta = 2.0*M_PI*(radius*sin(degreesToRadians(phiAngle)));
            // TODO: check if this is the best way to get thetaSteps
            int thetaSteps = (int)ceil(circunfereceTheta/radiusStep);
            for(int theta = 0; theta < thetaSteps; theta++) {
                float thetaAngle = ((float)theta/(float)thetaSteps)*360.0;
                pos.x = _baseCentroid.x - (cellSize.x/2.0) + radius*sin(degreesToRadians(phiAngle))*cos(degreesToRadians(thetaAngle));
                pos.y = _baseCentroid.y - (cellSize.y/2.0) + radius*sin(degreesToRadians(phiAngle))*sin(degreesToRadians(thetaAngle));
                pos.z = _baseCentroid.z - (cellSize.z/2.0) + radius*cos(degreesToRadians(phiAngle));
                // Try to insert cell
                insertCell(pos, cellSize, cell);
            }
        }
    }
}

void MainWindow::variableCartesian(Cell *cell, glm::vec3 infillOrigin)
{
    glm::vec3 pos(0.0f, 0.0f, 0.0f);
    pos.x = infillOrigin.x;
    while(pos.x < _maxX) {
        _varX = pos.x - infillOrigin.x;
        pos.y = infillOrigin.y;
        float cellHeightX;
        cellHeightX = std::min(te_eval(_exprX), 25.0);
        cellHeightX = std::max(cellHeightX, 2.5f);

        // Q1
        while(pos.y < _maxY) {
            _varY = pos.y - infillOrigin.y;
            pos.z = _minZ;
            float cellHeightY;
            cellHeightY = std::min(te_eval(_exprY), 25.0);
            cellHeightY = std::max(cellHeightY, 2.5f);
            while(pos.z < _maxZ) {
                _varZ = pos.z - infillOrigin.z;
                // Limit cell height
                float cellHeightZ;
                cellHeightZ = std::min(te_eval(_exprZ), 25.0);
                cellHeightZ = std::max(cellHeightZ, 2.5f);
                glm::vec3 size(cellHeightX, cellHeightY, cellHeightZ);
                insertCell(pos, size, cell);

                pos.z += cellHeightZ;
            }
            pos.y += cellHeightY;
        }
        pos.y = infillOrigin.y;
        // Q4
        while(pos.y > _minY) {
            _varY= pos.y - infillOrigin.y;
            pos.z = _minZ;
            float cellHeightY;
            cellHeightY = std::min(te_eval(_exprY), 25.0);
            cellHeightY = std::max(cellHeightY, 2.5f);
            while(pos.z < _maxZ) {
                _varZ = pos.z - infillOrigin.z;
                // Limit cell height
                float cellHeightZ;
                cellHeightZ = std::min(te_eval(_exprZ), 25.0);
                cellHeightZ = std::max(cellHeightZ, 2.5f);

                glm::vec3 posAux(pos.x, pos.y-cellHeightY, pos.z);
                glm::vec3 size(cellHeightX, cellHeightY, cellHeightZ);
                insertCell(posAux, size, cell);

                pos.z += cellHeightZ;
            }
            pos.y -= cellHeightY;
        }
        pos.x += cellHeightX;
    }
    pos.x = infillOrigin.x;
    while(pos.x > _minX) {
        _varX = pos.x - infillOrigin.x;
        pos.y = infillOrigin.y;
        float cellHeightX;
        cellHeightX = std::min(te_eval(_exprX), 25.0);
        cellHeightX = std::max(cellHeightX, 2.5f);
        // Q2
        while(pos.y < _maxY) {
            _varY = pos.y - infillOrigin.y;
            pos.z = _minZ;
            float cellHeightY;
            cellHeightY = std::min(te_eval(_exprY), 25.0);
            cellHeightY = std::max(cellHeightY, 2.5f);
            while(pos.z < _maxZ) {
                _varZ = pos.z - infillOrigin.z;
                // Limit cell height
                float cellHeightZ;
                cellHeightZ = std::min(te_eval(_exprZ), 25.0);
                cellHeightZ = std::max(cellHeightZ, 2.5f);
                glm::vec3 posAux(pos.x-cellHeightX, pos.y, pos.z);
                glm::vec3 size(cellHeightX, cellHeightY, cellHeightZ);
                insertCell(posAux, size, cell);

                pos.z += cellHeightZ;
            }
            pos.y += cellHeightY;
        }
        pos.y = infillOrigin.y;
        // Q3
        while(pos.y > _minY) {
            _varY = pos.y - infillOrigin.y;
            pos.z = _minZ;
            float cellHeightY;
            cellHeightY = std::min(te_eval(_exprY), 25.0);
            cellHeightY = std::max(cellHeightY, 2.5f);
            while(pos.z < _maxZ) {
                _varZ = pos.z - infillOrigin.z;
                // Limit cell height
                float cellHeightZ;
                cellHeightZ = std::min(te_eval(_exprZ), 25.0);
                cellHeightZ = std::max(cellHeightZ, 2.5f);

                glm::vec3 posAux(pos.x-cellHeightX, pos.y-cellHeightY, pos.z);
                glm::vec3 size(cellHeightX, cellHeightY, cellHeightZ);
                insertCell(posAux, size, cell);

                pos.z += cellHeightZ;
            }
            pos.y -= cellHeightY;
        }
        pos.x -= cellHeightX;
    }
}

void MainWindow::variableCylindrical(Cell *cell, glm::vec3 infillOrigin)
{
    // TODO: check if this is the best way to get maxR
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
                // Two approaches: cells are rotated with the cylindical orientation or cells are rotate with the cartesian orientation
                insertCell(pos, size, cell);
                z += cellSizeZ;
            }
            z = infillOrigin.z;
            while(z > _minZ) {
                float posZ = z;
                float cellSizeZ = std::min(r*fabsf(cos(degreesToRadians(phi)))/4.0f, 25.0f);
                cellSizeZ = std::max(cellSizeZ, 2.5f);
                glm::vec3 pos(posX, posY, posZ-cellSizeZ);
                glm::vec3 size(cellSizeX, cellSizeY, cellSizeZ);
                // Two approaches: cells are rotated with the cylindical orientation or cells are rotate with the cartesian orientation
                insertCell(pos, size, cell);
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

void MainWindow::on_pushButton_view_clicked()
{
//    Eigen::MatrixXd V;
//    Eigen::MatrixXi F;
//    igl::viewer::Viewer viewer;
//    viewer.data.set_mesh(V, F);
//    viewer.launch();
}
