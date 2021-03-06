#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QFileDialog>
#include "triangle.h"
#include "cell.h"
#include "utils.h"
#include "importdialog.h"
#include "rotatedialog.h"
#include "3rd_party/tinyexpr/tinyexpr.h"

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
    std::vector<Triangle> _shell;
    Cell *_tool;
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
    void importBasePart(Unit unit);

    void rotateBasePart(float angle, int axis);

    void on_pushButton_process_clicked();

    void on_radioButton_cellType_custom_toggled(bool checked);

    void on_checkBox_basePart_stateChanged(int arg1);

    void on_checkBox_wireframe_stateChanged(int arg1);

    void on_pushButton_loadCell_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_importBase_clicked();

    void on_pushButton_rotateBase_clicked();

    void on_pushButton_view_clicked();

    void on_pushButton_infill_add_clicked();

    void on_comboBox_infill_currentIndexChanged(int index);

    void on_pushButton_surfaceProjection_loadTool_clicked();

private:
    void updateUI();

    void insertCell(glm::vec3 pos, glm::vec3 size, Cell *c);
    void insertCell(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation, Cell *c);

    void saveCurrentInfill();

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
    Unit _stlUnit;

    float _baseVolume;
    glm::vec3 _baseCentroid;

    bool _baseImported;
    bool _baseProcessed;
    bool _customCell;
    bool _toolLoaded;

    ImportDialog *_importDialog;
    RotateDialog *_rotateDialog;
    void simpleCartesian(Cell *cell, Infill infill);
    void simpleCylindrical(Cell *cell, Infill infill);
    void simpleSpherical(Cell *cell, Infill infill);

    void variableCartesian(Cell *cell, Infill infill);
    void variableCylindrical(Cell *cell, Infill infill);
    void variableSpherical(Cell *cell, Infill infill);

    int _infillIndex;
    int _infillCount;
    std::vector<Infill> _infills;

    // Variable infill equations and variables
    te_expr *_exprX;
    te_expr *_exprY;
    te_expr *_exprZ;
    double _varX;
    double _varY;
    double _varZ;

    // Surface projection position equations and variables
    te_expr *_surfProjPosX;
    te_expr *_surfProjPosY;
    te_expr *_surfProjPosZ;
    double _surfProjVarX;
    double _surfProjVarY;
    double _surfProjVarZ;

    int _iteration;
};

#endif // MAINWINDOW_H
