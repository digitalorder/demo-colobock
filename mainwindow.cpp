#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    int matrixSize = 3;
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    _locks = new LocksArray(matrixSize);
    _rockers = new RockerMatrix(matrixSize);
    mainLayout->addLayout(_locks);
    mainLayout->addLayout(_rockers);
    centralWidget->setLayout(mainLayout);
    // todo remove this dependency
    centralWidget->setMinimumHeight((matrixSize + 1) * 48);
    centralWidget->setMaximumHeight((matrixSize + 1) * 48);
    centralWidget->setMinimumWidth(matrixSize * 48);
    centralWidget->setMaximumWidth(matrixSize * 48);

    _switch_logic = new SwitchLogic(_rockers, this);
    _win_logic = new WinLogic(matrixSize, this);

    setWindowTitle("Colobock demo");

    connect(_rockers, &RockerMatrix::clickedSignal, _switch_logic, &SwitchLogic::rockerSwitched);
    connect(_switch_logic, &SwitchLogic::newSwitchesState, _win_logic, &WinLogic::newSwitchesState);
    connect(_win_logic, &WinLogic::newLocksState, _locks, &LocksArray::locksSwitched);
    connect(_win_logic, &WinLogic::win, this, &MainWindow::winCatcher);
}

MainWindow::~MainWindow()
{

}

void MainWindow::winCatcher()
{
    qDebug() << "Game is completed now!";
}
