#include "configdialog.h"
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

ConfigDialog::ConfigDialog(Settings &settings): _settings(settings)
{
    QPushButton * btnOk = new QPushButton("OK");
    QPushButton * btnCancel = new QPushButton("Cancel");
    _ledit_matrix_size = new QLineEdit(QString("%1").arg(settings.matrixSize()));
    _ledit_seed = new QLineEdit(QString("%1").arg(settings.seed()));
    _chbox_dark_theme = new QCheckBox();
    _chbox_dark_theme->setChecked(settings.darkTheme());

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

    QHBoxLayout * loDarkTheme = new QHBoxLayout();
    loDarkTheme->addWidget(new QLabel("Dark theme mode"));
    loDarkTheme->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Expanding));
    loDarkTheme->addWidget(_chbox_dark_theme, 0, Qt::AlignRight);
    loSettings->addLayout(loDarkTheme);
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
    _settings.setMatrixSize(_ledit_matrix_size->text().toInt());
    _settings.setSeed(_ledit_seed->text().toInt());
    _settings.setDarkTheme(_chbox_dark_theme->isChecked());

    emit accept();
}
