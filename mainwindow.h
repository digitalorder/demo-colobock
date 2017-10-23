#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rockermatrix.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    RockerMatrix * rockers;

private slots:
    void clicked(int x, int y);

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
