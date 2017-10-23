#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setMinimumHeight(2 * 48);
    centralWidget->setMaximumHeight(2 * 48);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    rockers = new RockerMatrix(2);
    mainLayout->addLayout(rockers);
    centralWidget->setLayout(mainLayout);
    setWindowTitle("Colobock demo");

    connect(rockers, &RockerMatrix::clickedSignal, this, &MainWindow::clicked);
}

void MainWindow::clicked(int x, int y)
{
    qDebug() << "Button (" << x << ", " << y << ") clicked";
}

MainWindow::~MainWindow()
{

}
