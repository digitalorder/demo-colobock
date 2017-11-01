#include "configdialog.h"
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

const int MINIMUM_MATRIX_SIZE = 2;
const int MAXIMUM_MATRIX_SIZE = 12;

ConfigDialog::ConfigDialog(int matrixSize): _matrix_size(matrixSize)
{
    QPushButton * btnOk = new QPushButton("OK");
    QPushButton * btnCancel = new QPushButton("Cancel");
    QLabel * lblMatrixSize = new QLabel("Desired matrix size (2-12): ");
    _ledit_matrix_size = new QLineEdit(QString("%1").arg(matrixSize));

    QGroupBox * gboxSettings = new QGroupBox("Game settings", this);
    QHBoxLayout * loControls = new QHBoxLayout();
    loControls->addWidget(lblMatrixSize, 0, Qt::AlignLeft);
    loControls->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Expanding));
    loControls->addWidget(_ledit_matrix_size, 0, Qt::AlignRight);
    gboxSettings->setLayout(loControls);

    QHBoxLayout * loButtons = new QHBoxLayout();
    loButtons->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Expanding));
    loButtons->addWidget(btnOk, 0, Qt::AlignRight);
    loButtons->addWidget(btnCancel, 0, Qt::AlignRight);

    QVBoxLayout * loMain = new QVBoxLayout();
    loMain->addWidget(gboxSettings);
    loMain->addLayout(loButtons);

    QWidget * widCentral = new QWidget(this);
    widCentral->setLayout(loMain);
    widCentral->adjustSize();
    resize(widCentral->size());

    setWindowTitle("New game dialog");
    setFixedSize(QSize(size()));

    connect(btnOk, &QPushButton::clicked, this, &ConfigDialog::accepted);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

ConfigDialog::~ConfigDialog()
{
    // anything visible should not be deleted
}

void ConfigDialog::accepted()
{
    bool success = false;
    int result = _ledit_matrix_size->text().toInt(&success);
    if (!success)
    {
        return;
    }

    result = std::max(result, MINIMUM_MATRIX_SIZE);
    result = std::min(result, MAXIMUM_MATRIX_SIZE);

    _matrix_size = result;
    emit accept();
}
