#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

class ConfigDialog : public QDialog
{
    QPushButton * _btn_ok;
    QPushButton * _btn_cancel;
    QLineEdit * _ledit_matrix_size;

public:
    ConfigDialog(int matrixSize);
    int matrixSize();
};

#endif // CONFIGDIALOG_H
