#ifndef ROCKER_H
#define ROCKER_H

#include <QPushButton>

class Rocker : public QPushButton
{
    Q_OBJECT
    enum State {
        VERTICAL,
        HORIZONTAL
    };

    State state;

    QString stateToText();
public:
    explicit Rocker(QWidget *parent = 0);

signals:

public slots:
};

#endif // ROCKER_H
