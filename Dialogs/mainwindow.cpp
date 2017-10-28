#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>
#include <QMessageBox>
#include "newgamedialog.h"

static QHBoxLayout *buttonsLayout;
static QHBoxLayout *locksLayout;
static QHBoxLayout *rockersLayout;
static QVBoxLayout *mainLayout;

void MainWindow::restartLayout()
{
    this->hide();
    setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
    deleteLayout();
    constructLayout();
    setFixedSize(QSize(size()));
    this->show();
}

void MainWindow::drawWidgets()
{
    buttonsLayout->addWidget(_btn_undo);
    buttonsLayout->addWidget(_btn_redo);
    buttonsLayout->addSpacerItem(new QSpacerItem(2, 0, QSizePolicy::Expanding));
    buttonsLayout->addWidget(_lbl_move_counter);
    buttonsLayout->addSpacerItem(new QSpacerItem(2, 0, QSizePolicy::Expanding));
    buttonsLayout->addWidget(_btn_new_game);
    buttonsLayout->setMargin(0);

    locksLayout->addSpacerItem(new QSpacerItem(2, 0, QSizePolicy::Expanding));
    locksLayout->addLayout(_locks);
    locksLayout->setMargin(0);
    locksLayout->addSpacerItem(new QSpacerItem(2, 0, QSizePolicy::Expanding));

    rockersLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
    rockersLayout->addLayout(_rockers);
    rockersLayout->setMargin(0);
    rockersLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));

    mainLayout->addLayout(buttonsLayout);
    mainLayout->addLayout(locksLayout);
    mainLayout->addLayout(rockersLayout);

    _central_widget->setLayout(mainLayout);
    _central_widget->adjustSize();

    setWindowTitle("Colobock demo by Denis Vasilkovskii");
    resize(_central_widget->size());
    setFixedSize(_central_widget->size());
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _matrix_size(4)
{
    constructLayout();
}

void MainWindow::deleteLayout()
{
    delete _locks;
    delete _rockers;
    delete _btn_undo;
    delete _btn_redo;
    delete _btn_new_game;
    delete _lbl_move_counter;
    delete _central_widget;

    delete _rockers_logic;
    delete _locks_logic;
    delete _win_logic;
    delete _logger;
}

void setButtonIcon(QPushButton * button, const QString & resourcePath)
{
    QIcon ico;
    ico.addPixmap(QPixmap(resourcePath), QIcon::Normal, QIcon::On);
    button->setIcon(ico);
    button->setIconSize(QSize(32, 32));
    button->setFixedSize(QSize(32, 32));
}

void MainWindow::constructLayout()
{
    _locks = new LocksArray(_matrix_size);
    _locks_logic = new LocksLogic(_matrix_size);
    _locks_model = new LocksModel(_matrix_size);
    _rockers = new RockersMatrix(_matrix_size);
    _rockers_model = new RockersModel(_matrix_size);
    _rockers_logic = new RockersLogic(_matrix_size);
    _btn_undo = new QPushButton("", this);
    _btn_undo->setEnabled(false);
    _btn_redo = new QPushButton("", this);
    _btn_redo->setEnabled(false);
    _btn_new_game = new QPushButton("", this);
    _lbl_move_counter = new QLabel(QString("Moves: 0   "), this);
    _central_widget = new QWidget(this);

    _win_logic = new WinLogic(this);
    _logger = new Logger(this);

    buttonsLayout = new QHBoxLayout();
    locksLayout = new QHBoxLayout();
    rockersLayout = new QHBoxLayout();
    mainLayout = new QVBoxLayout();

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(185, 180, 186));
    _central_widget->setAutoFillBackground(true);
    _central_widget->setPalette(pal);

    setButtonIcon(_btn_undo, QString(":/images/resources/Undo.jpg"));
    setButtonIcon(_btn_redo, QString(":/images/resources/Redo.jpg"));
    setButtonIcon(_btn_new_game, QString(":/images/resources/Config.jpg"));

    drawWidgets();

    connect(_rockers, &RockersMatrix::rockerToggled, _rockers_logic, &RockersLogic::rockerSwitchedSlot);
    connect(_rockers_logic, &RockersLogic::blockControllers, _rockers, &RockersMatrix::block);
    connect(_rockers_logic, &RockersLogic::blockControllers, _rockers_model, &RockersModel::block);
    connect(_rockers_logic, &RockersLogic::blockControllers, _logger, &Logger::block);
    connect(_rockers_logic, &RockersLogic::unblockControllers, _rockers, &RockersMatrix::unblock);
    connect(_rockers_logic, &RockersLogic::unblockControllers, _rockers_model, &RockersModel::unblock);
    connect(_rockers_logic, &RockersLogic::unblockControllers, _logger, &Logger::unblock);
    connect(_rockers_logic, &RockersLogic::rockerSwitchedSignal, _rockers_model, &RockersModel::rockerToggled);
    connect(_rockers_model, &RockersModel::toggleRockerWithoutLogic, _rockers, &RockersMatrix::toggleRocker);
    connect(_rockers_model, &RockersModel::toggleRockerWithLogic, _rockers_logic, &RockersLogic::toggleRocker);
    connect(_rockers_model, &RockersModel::modelStateUpdated, _locks_logic, &LocksLogic::newRockersStateSlot);
    connect(_rockers, &RockersMatrix::rockerToggled, _logger, &Logger::newUserAction);
    connect(_locks_logic, &LocksLogic::blockControllers, _locks_model, &LocksModel::block);
    connect(_locks_logic, &LocksLogic::unblockControllers, _locks_model, &LocksModel::unblock);
    connect(_locks_logic, &LocksLogic::lockStateChangedSignal, _locks_model, &LocksModel::lockStateChangedSlot);
    connect(_locks_model, &LocksModel::locksStateChangedSignal, _locks, &LocksArray::updateLocksStates);
    connect(_locks_model, &LocksModel::locksStateChangedSignal, _win_logic, &WinLogic::newLocksStateSlot);
    connect(_win_logic, &WinLogic::win, this, &MainWindow::winCatcher);
    connect(_btn_undo, &QPushButton::clicked, _logger, &Logger::undoLastUserAction);
    connect(_btn_redo, &QPushButton::clicked, _logger, &Logger::redoLastUserAction);
    connect(_logger, &Logger::revertAction, _rockers_model, &RockersModel::rockerToggled);
    connect(_logger, &Logger::undoAvailablityChanged, _btn_undo, &QPushButton::setEnabled);
    connect(_logger, &Logger::redoAvailablityChanged, _btn_redo, &QPushButton::setEnabled);
    connect(_logger, &Logger::moveCounterChanged, this, &MainWindow::moveCounterChanged);
    connect(_btn_new_game, &QPushButton::clicked, this, &MainWindow::newGameRequested);
}

MainWindow::~MainWindow()
{

}

void MainWindow::showEvent(QShowEvent *)
{
    qDebug() << "Window has been loaded";
    _win_logic->block();
    _rockers_model->shuffle();
    _win_logic->unblock();
}

void MainWindow::winCatcher()
{
    QMessageBox msgBox;
    msgBox.setText("Cool! You was able to solve this puzzle. Would you like to try again?");
    QAbstractButton *btnYes = msgBox.addButton("I wanna more!", QMessageBox::YesRole);
    msgBox.addButton("That's enough!", QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton()==btnYes)
    {
        restartLayout();
    }
    else
    {
        close();
    }
}

void MainWindow::moveCounterChanged(int value)
{
    _lbl_move_counter->setText(QString("Moves: %1").arg(value));
}

void MainWindow::newGameRequested()
{
    NewGameDialog dialog(_matrix_size);
    dialog.setModal(true);
    int dialogResult = dialog.exec();
    if (dialogResult == QDialog::Accepted)
    {
        _matrix_size = dialog.matrixSize();
        restartLayout();
    }
}