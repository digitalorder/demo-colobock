#include "configdialog.h"
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

const int MINIMUM_MATRIX_SIZE = 2;
const int MAXIMUM_MATRIX_SIZE = 12;
const int MINIMUM_SEED = 0;
const int MAXIMUM_SEED = INT32_MAX - 1;

ConfigDialog::ConfigDialog(int matrixSize, int seed): _matrix_size(matrixSize), _seed(seed)
{
    QPushButton * btnOk = new QPushButton("OK");
    QPushButton * btnCancel = new QPushButton("Cancel");
    _ledit_matrix_size = new QLineEdit(QString("%1").arg(matrixSize));
    _ledit_seed = new QLineEdit(QString("%1").arg(seed));

    QGroupBox * gboxSettings = new QGroupBox("Game settings", this);

    QVBoxLayout * loSettings = new QVBoxLayout();
    QHBoxLayout * loMatrixSize = new QHBoxLayout();
    loMatrixSize->addWidget(new QLabel("Desired matrix size (2-12): "), 0, Qt::AlignLeft);
    loMatrixSize->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Expanding));
    loMatrixSize->addWidget(_ledit_matrix_size, 0, Qt::AlignRight);
    loSettings->addLayout(loMatrixSize);

    QHBoxLayout * loSeed = new QHBoxLayout();
    loSeed->addWidget(new QLabel("Select game seed: "), 0, Qt::AlignLeft);
    loSeed->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Expanding));
    loSeed->addWidget(_ledit_seed, 0, Qt::AlignRight);
    loSettings->addLayout(loSeed);
    gboxSettings->setLayout(loSettings);

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
    // anything visible is deleted automatically
}

void ConfigDialog::accepted()
{
    bool success = false;
    int newMatrixSize = _ledit_matrix_size->text().toInt(&success);
    if (!success)
    {
        return;
    }

    newMatrixSize = std::max(newMatrixSize, MINIMUM_MATRIX_SIZE);
    newMatrixSize = std::min(newMatrixSize, MAXIMUM_MATRIX_SIZE);

    int newSeed = _ledit_seed->text().toInt(&success);
    if (!success)
    {
        return;
    }

    newSeed = std::max(newSeed, MINIMUM_SEED);
    newSeed = std::min(newSeed, MAXIMUM_SEED);

    _matrix_size = newMatrixSize;
    _seed = newSeed;

    emit accept();
}
