#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QString>

class InfoDialog : public QDialog
{
    Q_OBJECT
    QPushButton * _btn_ok;
    QLabel * _lbl_info;
    QString readInfoFromFile(const QString &f);
public:
    explicit InfoDialog();
};

#endif // INFODIALOG_H
