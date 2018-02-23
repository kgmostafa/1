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
#include <iostream>
#include <QMessageBox>
#include <QInputDialog>

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

    _rotateDialog = new RotateDialog(this);
    connect(_rotateDialog, &RotateDialog::rotate, this, &MainWindow::rotateBasePart);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::rotateBasePart(float angle, int axis)
{
    angle = degreesToRadians(angle);
    if(axis == 0) {
        Utils::rotateX(_base1, angle);
    } else if(axis == 1) {
        Utils::rotateY(_base1, angle);
    } else if(axis == 2) {
        Utils::rotateZ(_base1, angle);
    }
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
    if(_base1.size() > 0) {
        _base2 = stl.decode(n);
    } else {
        _base1 = stl.decode(n);
    }
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
//    ui->pushButton_open->setEnabled(false);
    ui->pushButton_rotate->setEnabled(true);
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

        _processed.insert(_processed.end(), _base1.begin(), _base1.end());
        v_aux = Utils::getVertexList(_base1, f_aux);
        Utils::offsetVertices(v_aux, f_aux, offset);
        t_aux = Utils::getTriangleList(v_aux, f_aux);
        _base1 = t_aux;
        Utils::switchNormal(t_aux);
        _processed.insert(_processed.end(), t_aux.begin(), t_aux.end());

        std::vector<std::pair<glm::vec3, glm::vec3>> intseg = Utils::getIntersectionSegments(_processed, 36.0);
//        std::cout << "intersect segments size: " << intseg.size() << std::endl;
//        for(int i = 0; i < intseg.size(); i++) {
//            std::cout << intseg[i].first.x << ", " << intseg[i].first.y << ", " << intseg[i].second.x << ", " << intseg[i].second.y << std::endl;
//        }
        std::vector<std::vector<glm::vec3>> cont = Utils::getContours(intseg, 0.00001f);

        std::vector<std::vector<glm::vec2>> cont2D = Utils::convertContourTo2D(cont);
        std::vector<std::vector<glm::vec2>> contours = Utils::splitLoopsFromContours2D(cont2D);
        std::cout << "contours size: " << contours.size() << std::endl;

        std::vector<std::vector<glm::vec2>> contoursBase;
        contoursBase.push_back(contours[0]);
        std::vector<std::vector<glm::vec2>> contoursOffset;
        contoursOffset.insert(contoursOffset.begin(), contours.begin()+1, contours.end());
        Utils::removeLoops2D(_processed, 36.0, contoursBase, contoursOffset, offset/2.0, 0.0001f);

//        bool loops = Utils::checkLoops(cont);
//        if(loops) {
//            std::cout << "Loops detected!\n";
//        } else {
//            std::cout << "Loops not detected\n";
//        }

        return;

        //        for(int i = 0; i < conn.size(); i++) {
        //            std::cout << "conn[" << i << "] size: " << conn[i].size() << std::endl;
        //            for(int j = 0; j < conn[i].size(); j++) {
        //                std::cout << "conn[" << i << "][" << j << "]: " << glm::to_string(conn[i].at(j)) << std::endl;
        //            }
        //        }
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

        if(coordSystem == spherical) {
            glm::vec3 centroid;
            Utils::getCentroid(_base1, centroid);
            std::cout << "centroid: " << glm::to_string(centroid) << std::endl;
            int rSteps = (int)ceil(_maxLength/cellThickness);
            for(int r = 0; r < rSteps; r++) {   // Step spherical surface on r coordinate
                if(r == 0) {
                    float posX = centroid.x - (cellThickness/2.0);
                    float posY = centroid.y - (cellThickness/2.0);
                    float posZ = centroid.z - (cellThickness/2.0);
                    glm::vec3 cellCenter = glm::vec3(posX+(cellThickness/2.0), posY+(cellThickness/2.0), posZ+(cellThickness/2.0));
                    if(Utils::isInsideMesh(_base1, cellCenter, true) ||
                       Utils::getTrianglesFromBox(_base1, posX, posY, posZ, cellThickness).size() > 0) {
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
                        float posX = centroid.x - (cellThickness/2.0);
                        float posY = centroid.y - (cellThickness/2.0);
                        float posZ = centroid.z - (cellThickness/2.0) + radius;
                        glm::vec3 cellCenter = glm::vec3(posX+(cellThickness/2.0), posY+(cellThickness/2.0), posZ+(cellThickness/2.0));
                        if(Utils::isInsideMesh(_base1, cellCenter, true) ||
                           Utils::getTrianglesFromBox(_base1, posX, posY, posZ, cellThickness).size() > 0) {
                            c->place(posX, posY, posZ);
                            std::vector<Triangle> t = c->getFacets();
                            _processed.insert(_processed.end(), t.begin(), t.end());
                        }
                    }
                    circunferece = 2.0*M_PI*(radius*sin(degreesToRadians(phiAngle)));
                    int thetaSteps = (int)ceil(circunferece/cellThickness);
                    for(int theta = 0; theta < thetaSteps; theta++) {
                        float thetaAngle = ((float)theta/(float)thetaSteps)*360.0;
                        float posX = centroid.x - (cellThickness/2.0) + radius*sin(degreesToRadians(phiAngle))*cos(degreesToRadians(thetaAngle));
                        float posY = centroid.y - (cellThickness/2.0) + radius*sin(degreesToRadians(phiAngle))*sin(degreesToRadians(thetaAngle));
                        float posZ = centroid.z - (cellThickness/2.0) + radius*cos(degreesToRadians(phiAngle));
                        glm::vec3 cellCenter = glm::vec3(posX+(cellThickness/2.0), posY+(cellThickness/2.0), posZ+(cellThickness/2.0));
                        if(Utils::isInsideMesh(_base1, cellCenter, false) ||
                           Utils::getTrianglesFromBox(_base1, posX, posY, posZ, cellThickness).size() > 0) {
                            c->place(posX, posY, posZ);
                            std::vector<Triangle> t = c->getFacets();
                            _processed.insert(_processed.end(), t.begin(), t.end());
                        }
                    }
                }
            }
        }

        int zSteps = (int)ceil(_maxZLength/cellThickness);
        glm::vec2 centroid;

        for(int i = 0; i < zSteps; i++) {   // Step layer by layer on z axis
            float z = _minZ + i*cellThickness;
            std::vector<Triangle> slice = Utils::slice(_base1, z, cellThickness);

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
                        // Check if is inside the mesh or if is overlaping the surfaces
                        glm::vec3 cellCenter = glm::vec3(posX+(cellThickness/2.0), posY+(cellThickness/2.0), z+(cellThickness/2.0));
                        if(Utils::isInsideMesh(slice, cellCenter, true) ||
                           Utils::getTrianglesFromBox(slice, posX, posY, z, cellThickness).size() > 0) {
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
                        glm::vec3 cellCenter = glm::vec3(posX+(cellThickness/2.0), posY+(cellThickness/2.0), z+(cellThickness/2.0));
                        if(Utils::isInsideMesh(slice, cellCenter, true) ||
                           Utils::getTrianglesFromBox(slice, posX, posY, z, cellThickness).size() > 0) {
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
                        glm::vec3 cellCenter = glm::vec3(posX+(cellThickness/2.0), posY+(cellThickness/2.0), z+(cellThickness/2.0));
                        if(Utils::isInsideMesh(slice, cellCenter, true) ||
                           Utils::getTrianglesFromBox(slice, posX, posY, z, cellThickness).size() > 0) {
                            c->place(posX, posY, z);
                            std::vector<Triangle> t = c->getFacets();
                            _processed.insert(_processed.end(), t.begin(), t.end());
                        }
                    }
                }
            }
        }
    }

    // Trimm
    CorkTriMesh c1 = Utils::meshToCorkTriMesh(_base1);
    CorkTriMesh c2 = Utils::meshToCorkTriMesh(_processed);
    CorkTriMesh *c = new CorkTriMesh;
    computeIntersection(c1, c2, c);
    _processed = Utils::corkTriMeshToMesh(*c);

    // Updates the UI
    ui->labelNTriangles->setText("Number of triangles: " + _nTrianglesProcessed);

    // Enable save button
    ui->pushButton_save->setEnabled(true);
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

void MainWindow::on_pushButton_rotate_clicked() {
    _rotateDialog->show();
//    bool valid;
//    double d = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
//                                   tr("Amount:"), 37.56, -10000, 10000, 2, &valid);
//    if (valid)
//        std::cout << d << std::endl;
}
