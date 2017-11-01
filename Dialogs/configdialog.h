#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QLineEdit>

class ConfigDialog : public QDialog
{
    QLineEdit * _ledit_matrix_size;
    int _matrix_size;
public:
    ConfigDialog(int matrixSize);
    ~ConfigDialog();
    int matrixSize() { return _matrix_size; }

private slots:
    void accepted();
};

#endif // CONFIGDIALOG_H
