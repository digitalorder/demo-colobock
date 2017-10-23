#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rockermatrix.h"
#include "switchlogic.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    RockerMatrix * _rockers;
    SwitchLogic * _logic;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
