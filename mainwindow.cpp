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
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _nTriangles = 0;
    _nProcessed = 0;
    _maxXLength = 0.0;
    _maxYLength = 0.0;
    _maxZLength = 0.0;
    _maxLength = 0.0;
    _minZ = 0.0;
    _maxZ = 0.0;

    _wireframe = true;
    _baseCube = true;

    _stlHeader = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qint32 n = 0;
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open"), "", tr("STL Files (*.stl);;All files (*)"));

    if (fileName.isEmpty())
        return;

    STLFile stl(fileName);
    _triangs = stl.decode(n);
    if(n < 0)
        return;
    _nTriangles = (quint32)n;
    _nProcessed = _nTriangles;

    // Updates the UI texts
    _maxXLength = stl.getMaxXLength();
    _maxYLength = stl.getMaxYLength();
    _maxZLength = stl.getMaxZLength();
    _maxLength = _maxXLength;
    if(_maxYLength > _maxLength)
        _maxLength = _maxYLength;
    if(_maxZLength > _maxLength)
        _maxLength = _maxZLength;
    ui->labelNTriangles->setText("Number of triangles: " + QString::number(_nProcessed));
    ui->labelWidthX->setText("Width in X: " + QString::number(_maxXLength) + " mm");
    ui->labelWidthY->setText("Width in Y: " + QString::number(_maxYLength) + " mm");
    ui->labelHeightZ->setText("Height in Z: " + QString::number(_maxZLength) + " mm");
    _minY = stl.getMinY();
    _maxY = stl.getMaxY();
    _minZ = stl.getMinZ();
    _maxZ = stl.getMaxZ();
    _stlHeader = stl.getHeader();
}

//void MainWindow::on_pushButton_Process_clicked() {
//    processNew();

//    // Enable save button
//    ui->pushButtonSave->setEnabled(true);
//}

void MainWindow::processOld() {
    bool valid = false;
    float size = ui->lineEdit_size->text().toFloat(&valid);
    if(!valid) {
        std::cout << "Invalid input. Using size = 10mm\n";
        size = 10.0;
    }

    float widthX = 0.0;
    float widthY = 0.0;
    float heightZ = 0.0;

    int counter = _nTriangles;

    std::vector<Triangle> processed;

    for (std::vector<Triangle>::iterator it = _triangs.begin() ; it != _triangs.end(); ++it) {
        Triangle t = *it;
        std::cout << "Processing...\n";

        float minX = t.getMinX();
        float maxX = t.getMaxX();
        float minY = t.getMinY();
        float maxY = t.getMaxY();
        float minZ = t.getMinZ();
        float maxZ = t.getMaxZ();

        if(maxX - minX > widthX)
            widthX = maxX - minX;
        if(maxY - minY > widthY)
            widthY = maxY - minY;
        if(maxZ - minZ > heightZ)
            heightZ = maxZ - minZ;


        // Get the number of steps
        int nx = (int)((maxX-minX)/size); // default size: 10mm
        int ny = (int)((maxY-minY)/size); // default size: 10mm

        for(int i = 0; i < ny; i++) { // Y-axis
            for(int j = 0; j < nx; j += 2) { // X-axis
                // Adds a square

                Vertex v1(minX+(j+(i%2))*size, minY+i*size, minZ);
                Vertex v2(minX+(j+1+(i%2))*size, minY+i*size, minZ);
                Vertex v3(minX+(j+(i%2))*size, minY+(i+1)*size, minZ);
                // Square 1st triangle
                Triangle tnew(v1, v2, v3);
                processed.push_back(tnew);
                counter++;

                Vertex v1b(minX+(j+1+(i%2))*size, minY+(i)*size, minZ);
                Vertex v2b(minX+(j+1+(i%2))*size, minY+(i+1)*size, minZ);
                Vertex v3b(minX+(j+(i%2))*size, minY+(i+1)*size, minZ);

                // Square 2nd triangle
                Triangle tnewb(v1b, v2b, v3b);
                processed.push_back(tnewb);
                counter++;
            }
        }
        std::cout << counter << std::endl;
    }

    _nProcessed = counter;
    _triangs.insert(_triangs.end(), processed.begin(), processed.end());

    // Updates the UI texts
    ui->labelNTriangles->setText("Number of triangles: " + QString::number(_nProcessed));
}

void MainWindow::processNew() {
    bool valid = false;
    float thickness = ui->lineEdit_size->text().toFloat(&valid);
    if(!valid) {
        std::cout << "Invalid input. Using size = 10mm\n";
        thickness = 10.0;
    }

    int n = (_maxZ - _minZ) / thickness + 1;
    std::cout << "n slices: " << n << std::endl;

    std::vector<Triangle> processed;
    for(int i = 0; i < n; i++) {
        float z = _minZ + (i * thickness);
        std::cout << "z = " << z << std::endl;


        for (std::vector<Triangle>::iterator it = _triangs.begin() ; it != _triangs.end(); ++it) {
            Triangle t = *it;
            // TEST:
//            Vertex p1a(0.0, 50.0, 40.0);
//            Vertex p2a(0.0, 60.0, 40.0);
//            Vertex p3a(0.0, 50.0, 50.0);
//            Vertex p4a(0.0, 60.0, 50.0);
//            if(insideTriangle(p1a, t) && insideTriangle(p2a, t) && insideTriangle(p3a, t) && insideTriangle(p4a, t))
//                std::cout << "ERROR: SHOULD NOT BE INSIDE TRIANGLE\n";

            if(t.getMinZ() <= z && t.getMaxZ() > z) {   // Tiangle's intersect the slice plan
                int ny = (_maxY - _minY) / thickness + 1;
                float x = 0.0;
                for(int j = 0; j < ny; j++) {
                    if((i+j)%2 == 0)
                        continue;
                    float y = _minY + (j *thickness);
                    glm::vec3 p1(x, y, z);
                    glm::vec3 p2(x, y+thickness, z);
                    glm::vec3 p3(x, y, z+thickness);
                    glm::vec3 p4(x, y+thickness, z+thickness);
                    if(insideTriangle(p1, t) && insideTriangle(p2, t) && insideTriangle(p3, t) && insideTriangle(p4, t)) {
                        // T1
                        Vertex v1a(x, y, z);
                        Vertex v2a(x, y, z+thickness);
                        Vertex v3a(x, y+thickness, z);

                        Triangle tnewa(v1a, v2a, v3a);
                        processed.push_back(tnewa);

                        // T2
                        Vertex v1b(x, y, z+thickness);
                        Vertex v2b(x, y+thickness, z+thickness);
                        Vertex v3b(x, y+thickness, z);

                        Triangle tnewb(v1b, v2b, v3b);
                        processed.push_back(tnewb);

                        // CONNECT 1
                        Vertex v1c(x, y, z);
                        Vertex v2c(x+50.0, y, z);
                        Vertex v3c(x+50.0, y, z+thickness);

                        Triangle tnewc(v1c, v2c, v3c);
                        processed.push_back(tnewc);

                        // CONNECT 2
                        Vertex v1d(x, y, z);
                        Vertex v2d(x+50.0, y, z+thickness);
                        Vertex v3d(x, y, z+thickness);

                        Triangle tnewd(v1d, v2d, v3d);
                        processed.push_back(tnewd);

                        // CONNECT 3
                        Vertex v1e(x, y, z+thickness);
                        Vertex v2e(x+50.0, y, z+thickness);
                        Vertex v3e(x+50.0, y+thickness, z+thickness);

                        Triangle tnewe(v1e, v2e, v3e);
                        processed.push_back(tnewe);

                        // CONNECT 4
                        Vertex v1f(x, y, z+thickness);
                        Vertex v2f(x+50.0, y+thickness, z+thickness);
                        Vertex v3f(x, y+thickness, z+thickness);

                        Triangle tnewf(v1f, v2f, v3f);
                        processed.push_back(tnewf);
//                        std::cout << "insideTriangle! - " << t.toString().toStdString() << "x: 0.0, y: " << y << ", z: " << z << std::endl;
                    }
                }
                x += 50.0;
                for(int j = 0; j < ny; j++) {
                    if((i+j)%2 == 0)
                        continue;
                    float y = _minY + (j *thickness);
                    glm::vec3 p1(x, y, z);
                    glm::vec3 p2(x, y+thickness, z);
                    glm::vec3 p3(x, y, z+thickness);
                    glm::vec3 p4(x, y+thickness, z+thickness);
                    if(insideTriangle(p1, t) && insideTriangle(p2, t) && insideTriangle(p3, t) && insideTriangle(p4, t)) {
                        // T1
                        Vertex v1a(x, y, z);
                        Vertex v2a(x, y, z+thickness);
                        Vertex v3a(x, y+thickness, z);

                        Triangle tnewa(v1a, v2a, v3a);
                        processed.push_back(tnewa);

                        // T2
                        Vertex v1b(x, y, z+thickness);
                        Vertex v2b(x, y+thickness, z+thickness);
                        Vertex v3b(x, y+thickness, z);

                        Triangle tnewb(v1b, v2b, v3b);
                        processed.push_back(tnewb);

                        // CONNECT 1
                        Vertex v1c(x, y, z);
                        Vertex v2c(x-50.0, y, z);
                        Vertex v3c(x-50.0, y+thickness, z);

                        Triangle tnewc(v1c, v2c, v3c);
                        processed.push_back(tnewc);

                        // CONNECT 2
                        Vertex v1d(x, y, z);
                        Vertex v2d(x-50.0, y+thickness, z);
                        Vertex v3d(x, y+thickness, z);

                        Triangle tnewd(v1d, v2d, v3d);
                        processed.push_back(tnewd);

                        // CONNECT 3
                        Vertex v1e(x, y+thickness, z);
                        Vertex v2e(x-50.0, y+thickness, z);
                        Vertex v3e(x-50.0, y+thickness, z+thickness);

                        Triangle tnewe(v1e, v2e, v3e);
                        processed.push_back(tnewe);

                        // CONNECT 4
                        Vertex v1f(x, y+thickness, z);
                        Vertex v2f(x-50.0, y+thickness, z+thickness);
                        Vertex v3f(x, y+thickness, z+thickness);

                        Triangle tnewf(v1f, v2f, v3f);
                        processed.push_back(tnewf);
//                        std::cout << "insideTriangle! - " << t.toString().toStdString() << "x: 0.0, y: " << y << ", z: " << z << std::endl;
                    }
                }
            }
        }
    }
    _triangs.insert(_triangs.end(), processed.begin(), processed.end());
    // Updates the UI texts
    ui->labelNTriangles->setText("Number of triangles: " + QString::number(_triangs.size()));
}

// TODO: add reference to website that gives this pseudocode
bool MainWindow::insideTriangle(glm::vec3 p, Triangle t) {
    glm::vec3 A = t.getV1();
    glm::vec3 B = t.getV2();
    glm::vec3 C = t.getV3();

    // Compute vectors
    glm::vec3 v0 = C - A;
    glm::vec3 v1 = B - A;
    glm::vec3 v2 = p - A;

    // Compute dot products

    float dot00 = glm::dot(v0, v0);
    float dot01 = glm::dot(v0, v1);
    float dot02 = glm::dot(v0, v2);
    float dot11 = glm::dot(v1, v1);
    float dot12 = glm::dot(v1, v2);

    // Compute barycentric coordinates
    float invDenom = 1.0 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    // Check if point is in triangle
    return (u >= 0) && (v >= 0) && (u + v < 1);
}

void MainWindow::on_checkBoxWireFrame_stateChanged(int arg1) {
    _wireframe = (arg1==Qt::Unchecked)?false:true;
    update();
}

void MainWindow::on_pushButtonSave_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save"), "", tr("STL Files (*.stl);;All files (*)"));

    if (fileName.isEmpty())
        return;

    STLFile stl(fileName);
    std::vector<Triangle> vec(_triangs.begin() + _nTriangles, _triangs.end());
    stl.encode(_stlHeader, vec);
}

void MainWindow::on_pushButton_test_clicked() {
    Cube c(50.0);
    float scaleX = 1.0;
    float scaleY = 1.0;
    float scaleZ = 1.0;
    c.scale(scaleX, scaleY, scaleZ);
//    // Rotation order(Z -> X -> Y)
//    c.rotateZ(15.0);
//    c.rotateX(45.0);
//    c.rotateY(60.0);
//    c.translate(25.0, 0.0, 0.0);
    _triangs = c.getFacets();
    _nTriangles = _triangs.size();
    _nProcessed = _triangs.size();
    _maxXLength = scaleX*50.0;
    _maxYLength = scaleY*50.0;
    _maxZLength = scaleZ*50.0;
    _maxLength = _maxXLength;
    if(_maxYLength > _maxLength)
        _maxLength = _maxYLength;
    if(_maxZLength > _maxLength)
        _maxLength = _maxZLength;

    ui->labelNTriangles->setText("Number of triangles: " + QString::number(_nTriangles));
    ui->labelWidthX->setText("Width in X: " + QString::number(_maxXLength) + " mm");
    ui->labelWidthY->setText("Width in Y: " + QString::number(_maxYLength) + " mm");
    ui->labelHeightZ->setText("Height in Z: " + QString::number(_maxZLength) + " mm");
}

void MainWindow::on_pushButton_Place_clicked() {
    bool valid = false;

    float fillX = ui->lineEdit_posX->text().toFloat(&valid);
    if(!valid) {
        std::cout << "Invalid input. Using fillX = 1 cell\n";
        fillX = 1.0;
    }

    float fillY = ui->lineEdit_posY->text().toFloat(&valid);
    if(!valid) {
        std::cout << "Invalid input. Using fillY = 1 cell\n";
        fillY = 1.0;
    }

    float fillZ = ui->lineEdit_posZ->text().toFloat(&valid);
    if(!valid) {
        std::cout << "Invalid input. Using fillZ = 1 cell\n";
        fillZ = 1.0;
    }

    int cellType = 0; // None
    if(ui->radioButton_cellType_pyramid->isChecked())
        cellType = 1; // Pyramid
    else if(ui->radioButton_cellType_cube->isChecked())
        cellType = 2; // Cube
    else if(ui->radioButton_cellType_icosphere->isChecked())
        cellType = 3; // Icosphere

    for(int i = 0; i < fillZ; i++) {
        for(int j = 0; j < fillY; j++) {
            for(int k = 0; k < fillX; k++) {
//                if((k+j)%2 == 1)
//                    continue;
                float maxLength = _maxXLength;
                if(_maxYLength > maxLength)
                    maxLength = _maxYLength;
                if(_maxZLength > maxLength)
                    maxLength = _maxZLength;
                if(cellType == 1) {
                    Pyramid p(maxLength);
                    p.scale((_maxXLength/maxLength)/fillX, (_maxYLength/maxLength)/fillY, (_maxZLength/maxLength)/fillZ);
                    p.place(k*(_maxXLength/fillX), j*(_maxYLength/fillY), i*(_maxZLength/fillZ));

                    std::vector<Triangle> t = p.getFacets();
                    _triangs.insert(_triangs.end(), t.begin(), t.end());
                } else if(cellType == 2) {
                    Cube c(maxLength);
                    c.scale((_maxXLength/maxLength)/fillX, (_maxYLength/maxLength)/fillY, (_maxZLength/maxLength)/fillZ);
                    c.place(k*(_maxXLength/fillX), j*(_maxYLength/fillY), i*(_maxZLength/fillZ));

                    std::vector<Triangle> t = c.getFacets();
                    _triangs.insert(_triangs.end(), t.begin(), t.end());
                } else if(cellType == 3) {
                    Icosphere s(maxLength);
                    s.scale((_maxXLength/maxLength)/fillX, (_maxYLength/maxLength)/fillY, (_maxZLength/maxLength)/fillZ);
                    s.place(k*(_maxXLength/fillX), j*(_maxYLength/fillY), i*(_maxZLength/fillZ));

                    std::vector<Triangle> t = s.getFacets();
                    _triangs.insert(_triangs.end(), t.begin(), t.end());
                }

            }
        }
    }

    // Updates the UI texts
    ui->labelNTriangles->setText("Number of triangles: " + QString::number(_triangs.size()));

    // Enable save button
    ui->pushButtonSave->setEnabled(true);
}

void MainWindow::on_checkBox_baseCube_stateChanged(int arg1) {
    _baseCube = (arg1==Qt::Unchecked)?false:true;
    update();
}
