#ifndef ROTATEDIALOG_H
#define ROTATEDIALOG_H

#include <QDialog>

class QRadioButton;
class QLabel;
class QDoubleSpinBox;
class QPushButton;

class RotateDialog : public QDialog
{
    Q_OBJECT
public:
    RotateDialog(QWidget *parent = 0);

signals:
    void rotate(const float deg, const int axis);

private slots:
    void angleValueChanged(double d);
    void rotateClicked();

private:
    QLabel *_axisLabel;
    QRadioButton *_axisXRadioButton;
    QRadioButton *_axisYRadioButton;
    QRadioButton *_axisZRadioButton;
    QLabel *_angleLabel;
    QDoubleSpinBox *_angleSpinBox;
    QPushButton *_rotateButton;
};

#endif // ROTATEDIALOG_H
