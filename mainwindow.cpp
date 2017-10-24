#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    int matrixSize = 4;
    _locks = new LocksArray(matrixSize);
    _rockers = new RockersMatrix(matrixSize);
    _btn_undo = new QPushButton(QString("<-"), this);
    _btn_undo->setMaximumWidth(32);
    _btn_redo = new QPushButton(QString("->"), this);
    _btn_redo->setMaximumWidth(32);
    _btn_new_game = new QPushButton(QString("*"), this);
    _btn_new_game->setMaximumWidth(32);

    _rockers_logic = new RockersLogic(_rockers, this);
    _locks_logic = new LocksLogic(_locks, this);
    _win_logic = new WinLogic(this);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(_btn_undo);
    buttonsLayout->addWidget(_btn_redo);
    QSpacerItem * btnSpacer = new QSpacerItem(24, 0, QSizePolicy::Expanding);
    buttonsLayout->addSpacerItem(btnSpacer);
    buttonsLayout->addWidget(_btn_new_game);
    buttonsLayout->setAlignment(_btn_undo, Qt::AlignLeft);
    buttonsLayout->setAlignment(_btn_redo, Qt::AlignLeft);
//    buttonsLayout->setAlignment(btnSpacer, Qt::AlignHCenter);
    buttonsLayout->setAlignment(_btn_new_game, Qt::AlignRight);
//    QRect r1(0, 0, matrixSize * 48, 32);
//    buttonsLayout->setGeometry(r1);

    QHBoxLayout *locksLayout = new QHBoxLayout();
    locksLayout->addSpacerItem(new QSpacerItem(12, 0, QSizePolicy::Expanding));
    locksLayout->addLayout(_locks);
    locksLayout->addSpacerItem(new QSpacerItem(12, 0, QSizePolicy::Expanding));

    QHBoxLayout *rockersLayout = new QHBoxLayout();
    rockersLayout->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Expanding));
    rockersLayout->addLayout(_rockers);
    rockersLayout->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Expanding));

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addLayout(locksLayout);
    mainLayout->addLayout(rockersLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
//    QRect r(0, 0, matrixSize * 32, (matrixSize + 0) * 32);
//    _rockers->setGeometry(r);
    // todo remove this dependency
    centralWidget->setGeometry(0, 0, (matrixSize + 1) * 48, (matrixSize + 2) * 48);
    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, Qt::white);
    centralWidget->setAutoFillBackground(true);
    centralWidget->setPalette(pal);

    setWindowTitle("Colobock demo");
    setGeometry(centralWidget->rect());

    connect(_rockers, &RockersMatrix::clickedSignal, _rockers_logic, &RockersLogic::rockerSwitched);
    connect(_rockers_logic, &RockersLogic::newRockersStateSignal, _locks_logic, &LocksLogic::newRockersStateSlot);
    connect(_locks_logic, &LocksLogic::newLocksStateSignal, _locks, &LocksArray::locksSwitchedSlot);
    connect(_locks_logic, &LocksLogic::newLocksStateSignal, _win_logic, &WinLogic::newLocksStateSlot);
    connect(_win_logic, &WinLogic::win, this, &MainWindow::winCatcher);

    _rockers_logic->emitNewRockersStateSignal();
}

MainWindow::~MainWindow()
{

}

void MainWindow::winCatcher()
{
    qDebug() << "Game is completed now!";
}
