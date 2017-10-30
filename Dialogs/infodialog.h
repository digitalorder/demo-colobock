#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>

class InfoDialog : public QDialog
{
    Q_OBJECT
    QPushButton * _btn_ok;
    QLabel * _lbl_info;
public:
    explicit InfoDialog();
};

#endif // INFODIALOG_H
