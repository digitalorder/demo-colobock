#include "infodialog.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QResource>
#include <QFile>
#include <QDebug>
#include <QTextStream>

InfoDialog::InfoDialog()
{
    _btn_ok = new QPushButton("Oh, I see!");
    _lbl_info = new QLabel(readInfoFromFile(":/images/resources/info.txt"));
    _lbl_info->setWordWrap(true);
    _lbl_info->setFixedWidth(370);

    QHBoxLayout *textLayout = new QHBoxLayout();
    textLayout->addWidget(_lbl_info, 0, Qt::AlignLeft);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Expanding));
    buttonsLayout->addWidget(_btn_ok, 0, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(textLayout);
    mainLayout->addLayout(buttonsLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    centralWidget->setMaximumWidth(400);
    centralWidget->adjustSize();
    resize(centralWidget->size());

    setWindowTitle("How to play");
    setFixedSize(QSize(size()));

    connect(_btn_ok, &QPushButton::clicked, this, &QDialog::accept);
}

QString InfoDialog::readInfoFromFile(const QString &f)
{
    QResource infoText(f);

    QFile infoFile(infoText.absoluteFilePath());

    if (!infoFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return QString("Error loading info: " + infoFile.errorString());
    }

    QTextStream in(&infoFile);

    // QString is moveable so this is both efficient and readable
    return in.readAll();
}
