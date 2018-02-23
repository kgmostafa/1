#include <QLabel>
#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <iostream>
#include "rotatedialog.h"

RotateDialog::RotateDialog(QWidget *parent)
    : QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
    _axisLabel = new QLabel(tr("Axis:"));
    _axisXRadioButton = new QRadioButton("x");
    _axisXRadioButton->setChecked(true);
    _axisYRadioButton = new QRadioButton("y");
    _axisZRadioButton = new QRadioButton("z");
    _angleLabel = new QLabel(tr("Angle:"));
    _angleSpinBox = new QDoubleSpinBox();
    _angleSpinBox->setRange(-360.0, 360.0);
    _angleSpinBox->setSingleStep(0.1);
    _angleSpinBox->setSuffix(tr(" degree"));
    _rotateButton = new QPushButton(tr("Rotate"));

    connect(_angleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &RotateDialog::angleValueChanged);
    connect(_rotateButton, &QPushButton::clicked, this, &RotateDialog::rotateClicked);

    QHBoxLayout *axisLayout = new QHBoxLayout;
    axisLayout->addWidget(_axisLabel);
    axisLayout->addWidget(_axisXRadioButton);
    axisLayout->addWidget(_axisYRadioButton);
    axisLayout->addWidget(_axisZRadioButton);

    QHBoxLayout *angleLayout = new QHBoxLayout;
    angleLayout->addWidget(_angleLabel);
    angleLayout->addWidget(_angleSpinBox);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(axisLayout);
    mainLayout->addLayout(angleLayout);
    mainLayout->addWidget(_rotateButton);

    setLayout(mainLayout);
    setWindowTitle(tr("Rotate base part"));
    setFixedHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());
}

void RotateDialog::rotateClicked()
{
    int axis = -1;
    if(_axisXRadioButton->isChecked()) {
        axis = 0;
    } else if(_axisYRadioButton->isChecked()) {
        axis = 1;
    } else if (_axisZRadioButton->isChecked()) {
        axis = 2;
    }
    emit rotate(_angleSpinBox->value(), axis);

    close();
}

void RotateDialog::angleValueChanged(double d)
{
    if(d > 1.0 || d < -1.0) {
        _angleSpinBox->setSuffix(tr(" degrees"));
    } else {
        _angleSpinBox->setSuffix(tr(" degree"));
    }
}
