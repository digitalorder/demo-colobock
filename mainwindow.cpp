#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QGridLayout *grid = new QGridLayout();
    rocker = new Rocker(this);
    grid->addWidget(rocker);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(grid);
    setLayout(mainLayout);
    setWindowTitle("Colobock demo");

    connect(rocker, &Rocker::clicked, this, &MainWindow::clicked);
}

void MainWindow::clicked()
{
    qDebug() << "Button clicked";
}

MainWindow::~MainWindow()
{

}
