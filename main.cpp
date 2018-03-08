#include "mainwindow.h"
#include "rotatedialog.h"
#include <QApplication>
#include <igl/cotmatrix.h>
#include <Eigen/Dense>
#include <Eigen/Sparse>

int main(int argc, char *argv[])
{
    Eigen::MatrixXd V(4,2);
     V<<0,0,
        1,0,
        1,1,
        0,1;
     Eigen::MatrixXi F(2,3);
     F<<0,1,2,
        0,2,3;
     Eigen::SparseMatrix<double> L;
     igl::cotmatrix(V,F,L);
     std::cout<<"Hello, mesh: "<<std::endl<<L*V<<std::endl;

    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    w->show();

    return a.exec();
}
