#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    int matrixSize = 4;
    _locks = new LocksArray(matrixSize);
    _rockers = new RockersMatrix(matrixSize);
    _btn_undo = new QPushButton(QString("<-"), this);
    _btn_undo->setMaximumWidth(32);
    _btn_undo->setEnabled(false);
    _btn_redo = new QPushButton(QString("->"), this);
    _btn_redo->setMaximumWidth(32);
    _btn_redo->setEnabled(false);
    _btn_new_game = new QPushButton(QString("*"), this);
    _btn_new_game->setMaximumWidth(32);
    _lbl_move_counter = new QLabel(QString("Moves: 0"), this);

    _rockers_logic = new RockersLogic(_rockers, this);
    _locks_logic = new LocksLogic(_locks, this);
    _win_logic = new WinLogic(this);
    _logger = new Logger(this);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(_btn_undo);
    buttonsLayout->addWidget(_btn_redo);
    buttonsLayout->addSpacerItem(new QSpacerItem(2, 0, QSizePolicy::Expanding));
    buttonsLayout->addWidget(_lbl_move_counter);
    buttonsLayout->addSpacerItem(new QSpacerItem(2, 0, QSizePolicy::Expanding));
    buttonsLayout->addWidget(_btn_new_game);

    QHBoxLayout *locksLayout = new QHBoxLayout();
    locksLayout->addSpacerItem(new QSpacerItem(12, 0, QSizePolicy::Expanding));
    locksLayout->addLayout(_locks);
    locksLayout->addSpacerItem(new QSpacerItem(12, 0, QSizePolicy::Expanding));

    QHBoxLayout *rockersLayout = new QHBoxLayout();
    rockersLayout->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Expanding));
    rockersLayout->addLayout(_rockers);
    rockersLayout->addSpacerItem(new QSpacerItem(1, 0, QSizePolicy::Expanding));

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addLayout(locksLayout);
    mainLayout->addLayout(rockersLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    // todo remove this dependency
    centralWidget->setGeometry(0, 0, (matrixSize + 1) * 48, (matrixSize + 2) * 48);
    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, Qt::white);
    centralWidget->setAutoFillBackground(true);
    centralWidget->setPalette(pal);

    setWindowTitle("Colobock demo");
    setGeometry(centralWidget->rect());

    connect(_rockers, &RockersMatrix::clickedSignal, _rockers_logic, &RockersLogic::rockerSwitchedSlot);
    connect(_rockers_logic, &RockersLogic::newRockersStateSignal, _locks_logic, &LocksLogic::newRockersStateSlot);
    connect(_rockers_logic, &RockersLogic::rockerSwitchedSignal, _logger, &Logger::newUserAction);
    connect(_locks_logic, &LocksLogic::newLocksStateSignal, _locks, &LocksArray::locksSwitchedSlot);
    connect(_locks_logic, &LocksLogic::newLocksStateSignal, _win_logic, &WinLogic::newLocksStateSlot);
    connect(_win_logic, &WinLogic::win, this, &MainWindow::winCatcher);
    connect(_btn_undo, &QPushButton::clicked, _logger, &Logger::undoLastUserAction);
    connect(_btn_redo, &QPushButton::clicked, _logger, &Logger::redoLastUserAction);
    connect(_logger, &Logger::revertAction, _rockers_logic, &RockersLogic::revertAction);
    connect(_logger, &Logger::undoAvailablityChanged, _btn_undo, &QPushButton::setEnabled);
    connect(_logger, &Logger::redoAvailablityChanged, _btn_redo, &QPushButton::setEnabled);
    connect(_logger, &Logger::moveCounterChanged, this, &MainWindow::moveCounterChanged);

    _rockers_logic->emitNewRockersStateSignal();
}

MainWindow::~MainWindow()
{

}

void MainWindow::winCatcher()
{
    qDebug() << "Game is completed now!";
}

void MainWindow::moveCounterChanged(int value)
{
    _lbl_move_counter->setText(QString("Moves: %1").arg(value));
}
