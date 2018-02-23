#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include "utils.h"

class QRadioButton;
class QLabel;
class QPushButton;

class ImportDialog : public QDialog
{
    Q_OBJECT
public:
    ImportDialog(QWidget *parent = 0);

signals:
    void import(const Unit unit);

private slots:
    void importClicked();

private:
    QLabel *_unitLabel;
    QRadioButton *_micrometreButton;
    QRadioButton *_millimetreButton;
    QRadioButton *_centimetreButton;
    QRadioButton *_metreButton;
    QRadioButton *_inchButton;
    QRadioButton *_footButton;
    QPushButton *_importButton;
};

#endif // IMPORTDIALOG_H
