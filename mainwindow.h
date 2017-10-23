#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rocker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Rocker * rocker;

private slots:
    void clicked();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
