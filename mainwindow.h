#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "rockersmatrix.h"
#include "rockerslogic.h"
#include "rockersmodel.h"
#include "locksarray.h"
#include "lockslogic.h"
#include "winlogic.h"
#include "logger.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    RockersModel * _rockers_model;
    RockersMatrix * _rockers;
    RockersLogic * _rockers_logic;
    LocksArray * _locks;
    LocksLogic * _locks_logic;
    WinLogic * _win_logic;
    Logger * _logger;
    QPushButton * _btn_undo;
    QPushButton * _btn_redo;
    QPushButton * _btn_new_game;
    QLabel * _lbl_move_counter;
    QWidget * _central_widget;
    int _matrix_size;
    void restartLayout();
    void drawWidgets();
    void deleteLayout();
    void constructLayout();
    void showEvent(QShowEvent *);

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void winCatcher();
    void moveCounterChanged(int value);
    void newGameRequested();
};

#endif // MAINWINDOW_H
