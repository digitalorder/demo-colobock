#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    int matrixSize = 2;
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    _locks = new LocksArray(matrixSize);
    _rockers = new RockersMatrix(matrixSize);
    mainLayout->addLayout(_locks);
    mainLayout->addLayout(_rockers);
    centralWidget->setLayout(mainLayout);
    // todo remove this dependency
    centralWidget->setMinimumHeight((matrixSize + 1) * 48);
    centralWidget->setMaximumHeight((matrixSize + 1) * 48);
    centralWidget->setMinimumWidth(matrixSize * 48);
    centralWidget->setMaximumWidth(matrixSize * 48);

    _rockers_logic = new RockersLogic(_rockers, this);
    _locks_logic = new LocksLogic(_locks, this);
    _win_logic = new WinLogic(this);

    setWindowTitle("Colobock demo");

    connect(_rockers, &RockersMatrix::clickedSignal, _rockers_logic, &RockersLogic::rockerSwitched);
    connect(_rockers_logic, &RockersLogic::newRockersStateSignal, _locks_logic, &LocksLogic::newRockersStateSlot);
    connect(_locks_logic, &LocksLogic::newLocksStateSignal, _locks, &LocksArray::locksSwitchedSlot);
    connect(_locks_logic, &LocksLogic::newLocksStateSignal, _win_logic, &WinLogic::newLocksStateSlot);
    connect(_win_logic, &WinLogic::win, this, &MainWindow::winCatcher);
}

MainWindow::~MainWindow()
{

}

void MainWindow::winCatcher()
{
    qDebug() << "Game is completed now!";
}
