#include "mainwindow.h"
#include "rotatedialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    RotateDialog *dialog = new RotateDialog;
//    dialog->show();
    MainWindow *w = new MainWindow();
    w->show();

    return a.exec();
}
