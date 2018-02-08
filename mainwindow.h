#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QFileDialog>
#include "triangle.h"
#include "cell.h"
#include "utils.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    std::vector<Triangle> _base;
    std::vector<Triangle> _offset;
    std::vector<Triangle> _processed;
    Cell *_cell;

    quint32 _nTrianglesBase;
    quint32 _nTrianglesProcessed;

    float _maxXLength;
    float _maxYLength;
    float _maxZLength;
    float _maxLength;

    float _cellMaxXLength;
    float _cellMaxYLength;
    float _cellMaxZLength;
    float _cellMaxLength;

    bool _wireframe;
    bool _basePart;

    bool _cellLoaded;


private slots:
    void on_pushButton_process_clicked();

    void on_radioButton_cellType_custom_toggled(bool checked);

    void on_pushButton_open_clicked();

    void on_checkBox_basePart_stateChanged(int arg1);

    void on_checkBox_wireframe_stateChanged(int arg1);

    void on_pushButton_loadCell_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_rotate_clicked();

private:
    Ui::MainWindow *ui;

    float _minX;
    float _maxX;
    float _minY;
    float _maxY;
    float _minZ;
    float _maxZ;

    std::vector<Vertex> _vertex;
    std::vector<Facet> _facets;

    QString _stlHeader;
};

#endif // MAINWINDOW_H
