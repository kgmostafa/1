#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <iostream>
#include "importdialog.h"

const QChar lowercaseMu(0x03BC);

ImportDialog::ImportDialog(QWidget *parent)
    : QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
    _unitLabel = new QLabel(tr("STL file unit:"));
    _micrometreButton = new QRadioButton(QString(lowercaseMu) + "m");
    _millimetreButton = new QRadioButton("mm");
    _millimetreButton->setChecked(true);
    _centimetreButton = new QRadioButton("cm");
    _metreButton = new QRadioButton("m");
    _inchButton = new QRadioButton("in");
    _footButton = new QRadioButton("ft");
    _importButton = new QPushButton(tr("Import"));

    connect(_importButton, &QPushButton::clicked, this, &ImportDialog::importClicked);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(_unitLabel);
    mainLayout->addWidget(_micrometreButton);
    mainLayout->addWidget(_millimetreButton);
    mainLayout->addWidget(_centimetreButton);
    mainLayout->addWidget(_metreButton);
    mainLayout->addWidget(_inchButton);
    mainLayout->addWidget(_footButton);
    mainLayout->addWidget(_importButton);

    setLayout(mainLayout);
    setWindowTitle(tr("Import base part"));
    setFixedHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());
}

void ImportDialog::importClicked()
{
    Unit unit = millimetre;
    if(_micrometreButton->isChecked()) {
        unit = micrometre;
    } else if(_millimetreButton->isChecked()) {
        unit = millimetre;
    } else if(_centimetreButton->isChecked()) {
        unit = centimetre;
    } else if (_metreButton->isChecked()) {
        unit = metre;
    } else if (_inchButton->isChecked()) {
        unit = inch;
    } else if (_footButton->isChecked()) {
        unit = foot;
    }
    emit import(unit);

    close();
}
