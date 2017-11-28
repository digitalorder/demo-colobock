#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>

class ConfigDialog : public QDialog
{
    QLineEdit * _ledit_matrix_size;
    QLineEdit * _ledit_seed;
    QCheckBox * _chbox_dark_theme;
    int _matrix_size;
    int _seed;
    bool _dark_theme;
public:
    ConfigDialog(int matrixSize, int seed, bool darkTheme);
    ~ConfigDialog();
    int matrixSize() { return _matrix_size; }
    int seed() { return _seed; }
    bool darkTheme() { return _dark_theme; }

private slots:
    void accepted();
};

#endif // CONFIGDIALOG_H
