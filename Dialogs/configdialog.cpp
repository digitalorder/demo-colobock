#include "configdialog.h"
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

const int MINIMUM_MATRIX_SIZE = 2;
const int MAXIMUM_MATRIX_SIZE = 12;
const int DEFAULT_MATRIX_SIZE = 4;

ConfigDialog::ConfigDialog(int matrixSize)
{
    _btn_ok = new QPushButton("OK");
    _btn_cancel = new QPushButton("Cancel");
    QLabel * lblMatrixSize = new QLabel("Desired matrix size (2-12): ");
    _ledit_matrix_size = new QLineEdit(QString("%1").arg(matrixSize));

    QGroupBox *groupBox = new QGroupBox("Game settings", this);
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(lblMatrixSize, 0, Qt::AlignLeft);
    controlsLayout->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Expanding));
    controlsLayout->addWidget(_ledit_matrix_size, 0, Qt::AlignRight);
    groupBox->setLayout(controlsLayout);

    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    buttonsLayout->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Expanding));
    buttonsLayout->addWidget(_btn_ok, 0, Qt::AlignRight);
    buttonsLayout->addWidget(_btn_cancel, 0, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(groupBox);
    mainLayout->addLayout(buttonsLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    centralWidget->adjustSize();
    resize(centralWidget->size());

    setWindowTitle("New game dialog");
    setFixedSize(QSize(size()));

    connect(_btn_ok, &QPushButton::clicked, this, &QDialog::accept);
    connect(_btn_cancel, &QPushButton::clicked, this, &QDialog::reject);
}

int ConfigDialog::matrixSize()
{
    bool success = false;
    int result = _ledit_matrix_size->text().toInt(&success);
    if (!success)
    {
        return DEFAULT_MATRIX_SIZE;
    }

    result = std::max(result, MINIMUM_MATRIX_SIZE);
    result = std::min(result, MAXIMUM_MATRIX_SIZE);

    return result;
}
