#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rockersmatrix.h"
#include "rockerslogic.h"
#include "locksarray.h"
#include "lockslogic.h"
#include "winlogic.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    RockersMatrix * _rockers;
    RockersLogic * _rockers_logic;
    LocksArray * _locks;
    LocksLogic * _locks_logic;
    WinLogic * _win_logic;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void winCatcher();
};

#endif // MAINWINDOW_H
