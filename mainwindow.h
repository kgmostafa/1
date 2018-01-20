#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QFileDialog>
#include "triangle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    std::vector<Triangle> _triangs;

    quint32 _nTriangles;
    quint32 _nProcessed;

    float _maxXLength;
    float _maxYLength;
    float _maxZLength;

    bool _wireframe;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_Process_clicked();

    void on_checkBoxWireFrame_stateChanged(int arg1);

    void on_pushButtonSave_clicked();

    void on_pushButton_test_clicked();

private:
    Ui::MainWindow *ui;

    void processOld();
    void processNew();

    bool insideTriangle(glm::vec3 p, Triangle t);

    float _minZ;
    float _maxZ;

    float _minY;
    float _maxY;

    QString _stlHeader;
};

#endif // MAINWINDOW_H
