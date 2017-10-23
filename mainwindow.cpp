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
    _rockers = new RockerMatrix(matrixSize);
    mainLayout->addLayout(_rockers);
    centralWidget->setLayout(mainLayout);
    // todo remove this dependency
    centralWidget->setMinimumHeight(matrixSize * 48);
    centralWidget->setMaximumHeight(matrixSize * 48);
    centralWidget->setMinimumWidth(matrixSize * 48);
    centralWidget->setMaximumWidth(matrixSize * 48);

    _logic = new SwitchLogic(_rockers, this);

    setWindowTitle("Colobock demo");

    connect(_rockers, &RockerMatrix::clickedSignal, _logic, &SwitchLogic::rockerSwitched);
}

MainWindow::~MainWindow()
{

}
