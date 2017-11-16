#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QLineEdit>

class ConfigDialog : public QDialog
{
    QLineEdit * _ledit_matrix_size;
    QLineEdit * _ledit_seed;
    int _matrix_size;
    int _seed;
public:
    ConfigDialog(int matrixSize, int seed);
    ~ConfigDialog();
    int matrixSize() { return _matrix_size; }
    int seed() { return _seed; }

private slots:
    void accepted();
};

#endif // CONFIGDIALOG_H
