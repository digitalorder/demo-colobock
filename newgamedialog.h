#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

class NewGameDialog : public QDialog
{
    QPushButton * _btn_ok;
    QPushButton * _btn_cancel;
    QLineEdit * _ledit_matrix_size;

public:
    NewGameDialog(int matrixSize);
    int matrixSize();
};

#endif // NEWGAMEDIALOG_H
