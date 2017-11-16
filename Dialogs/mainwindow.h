#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "rockersmatrix.h"
#include "rockerslogic.h"
#include "rockersmodel.h"
#include "locksarray.h"
#include "lockslogic.h"
#include "locksmodel.h"
#include "winlogic.h"
#include "logger.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    RockersModel * _rockers_model;
    RockersMatrix * _rockers;
    RockersLogic * _rockers_logic;
    LocksModel * _locks_model;
    LocksArray * _locks;
    LocksLogic * _locks_logic;
    WinLogic * _win_logic;
    Logger * _logger;
    QPushButton * _btn_undo;
    QPushButton * _btn_redo;
    QPushButton * _btn_config;
    QPushButton * _btn_info;
    QLabel * _lbl_move_counter;
    QWidget * _central_widget;
    int _matrix_size;
    const int SEED_IS_NOT_SET = INT32_MAX;
    int _seed;
    void restartLayout();
    void drawWidgets();
    void deleteLayout();
    void constructLayout();
    void showEvent(QShowEvent *);
    void setButtonIcon(QPushButton *button, const QString &resourcePath);
    void deleteParentless();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void winCatcher();
    void moveCounterChanged(int value);
    void configBtnClicked();
    void infoBtnClicked();
};

#endif // MAINWINDOW_H
