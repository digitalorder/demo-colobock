#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include "settings.h"

class ConfigDialog : public QDialog
{
    QLineEdit * _ledit_matrix_size;
    QLineEdit * _ledit_seed;
    QCheckBox * _chbox_dark_theme;
    Settings & _settings;
public:
    ConfigDialog(Settings & settings);
    ~ConfigDialog();
    Settings & settings() const { return _settings; }

private slots:
    void accepted();
};

#endif // CONFIGDIALOG_H
