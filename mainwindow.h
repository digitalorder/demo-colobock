#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rockermatrix.h"
#include "locksarray.h"
#include "switchlogic.h"
#include "winlogic.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    RockerMatrix * _rockers;
    LocksArray * _locks;
    SwitchLogic * _switch_logic;
    WinLogic * _win_logic;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void winCatcher();
};

#endif // MAINWINDOW_H
