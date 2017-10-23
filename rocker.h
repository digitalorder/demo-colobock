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
    const int x;
    const int y;

    QString stateToText();
private slots:
    void clickedEventCatcher(bool);

public:
    explicit Rocker(int x, int y, QWidget *parent = 0);

signals:
    void clickedOverride(int x, int y);

public slots:
};

#endif // ROCKER_H
