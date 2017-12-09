#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>
#include <QMessageBox>
#include <QTime>
#include "configdialog.h"
#include "infodialog.h"

void MainWindow::restartLayout()
{
    this->hide();
    setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
    // this is a workaround because IDK how to delete all those empty widgets in
    // grid layout when it is reduced from say 5x5 to 4x4
    deleteLayout();
    constructLayout();
    setFixedSize(QSize(size()));
    this->show();
}

void MainWindow::drawWidgets()
{
    QHBoxLayout * loButtons = new QHBoxLayout();
//    loButtons->addWidget(_btn_full_undo);
    loButtons->addWidget(_btn_undo);
    loButtons->addWidget(_btn_redo);
    loButtons->addSpacerItem(new QSpacerItem(2, 0, QSizePolicy::Expanding));
    loButtons->addWidget(_lbl_move_counter);

    QFont font = _lbl_move_counter->font();
    font.setBold(true);
    _lbl_move_counter->setFont(font);

    loButtons->addSpacerItem(new QSpacerItem(2, 0, QSizePolicy::Expanding));
    loButtons->addWidget(_btn_config);
//    loButtons->addWidget(_btn_highest_score);
    loButtons->addWidget(_btn_info);
    loButtons->setMargin(0);

    QHBoxLayout * loLocks = new QHBoxLayout();
    loLocks->addSpacerItem(new QSpacerItem(2, 0, QSizePolicy::Expanding));
    loLocks->addLayout(_locks);
    loLocks->setMargin(0);
    loLocks->addSpacerItem(new QSpacerItem(2, 0, QSizePolicy::Expanding));

    QHBoxLayout * loRockers = new QHBoxLayout();
    loRockers->addSpacerItem(new QSpacerItem(2, 0, QSizePolicy::Expanding));
    loRockers->addLayout(_rockers);
    loRockers->addSpacerItem(new QSpacerItem(2, 0, QSizePolicy::Expanding));
    _rockers->setSizeConstraint(QLayout::SetFixedSize);

    QVBoxLayout * loMain = new QVBoxLayout();
    loMain->addLayout(loButtons);
    loMain->addLayout( loLocks);
    loMain->addLayout(loRockers);

    QPalette pal = palette();
    if (_settings.darkTheme())
    {
        pal.setColor(QPalette::Background, QColor(79, 76, 75));
        QPalette pal1 = _lbl_move_counter->palette();
        pal1.setColor(_lbl_move_counter->foregroundRole(), QColor(169, 161, 158));
        _lbl_move_counter->setPalette(pal1);
    }
    else
    {
        pal.setColor(QPalette::Background, QColor(169, 161, 158));
        QPalette pal1 = _lbl_move_counter->palette();
        pal1.setColor(_lbl_move_counter->foregroundRole(), QColor(79, 76, 75));
        _lbl_move_counter->setPalette(pal1);
    }
    _central_widget->setAutoFillBackground(true);
    _central_widget->setPalette(pal);

//    setButtonIcon(_btn_full_undo, QString(resourceFolder + "Full_Undo_Active.png"), QString(resourceFolder + "Full_Undo_Inactive.png"));
    setButtonIcon(_btn_undo, _settings.resourceFolder() + "Undo_Active.png", _settings.resourceFolder() + "Undo_Inactive.png");
    setButtonIcon(_btn_redo, _settings.resourceFolder() + "Redo_Active.png", _settings.resourceFolder() + "Redo_Inactive.png");
//    setButtonIcon(_btn_highest_score, QString(resourceFolder + "Top.png"));
    setButtonIcon(_btn_config, _settings.resourceFolder() + "Config.png");
    setButtonIcon(_btn_info, _settings.resourceFolder() + "Info.png");

    _central_widget->setLayout(loMain);
    _central_widget->adjustSize();

    resize(_central_widget->size());
    setFixedSize(_central_widget->size());
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _settings(Settings())
{
    constructLayout();
}

void MainWindow::deleteLayout()
{
    delete _central_widget;
}

void MainWindow::setButtonIcon(QPushButton * button, const QString & resourcePath, const QString & inactiveResourcePath)
{
    QIcon ico;
    ico.addPixmap(QPixmap(resourcePath), QIcon::Normal, QIcon::On);
    if (inactiveResourcePath != nullptr)
    {
        ico.addPixmap(QPixmap(inactiveResourcePath), QIcon::Disabled, QIcon::On);
    }
    button->setIcon(ico);
    button->setIconSize(QSize(32, 32));
    button->setFixedSize(QSize(32, 32));
}

void MainWindow::constructLayout()
{
    _locks_model = new LocksModel(_settings, this);
    _locks = new LocksArray(_settings);
    _locks_logic = new LocksLogic(_settings, this);
    _rockers_model = new RockersModel(_settings, this);
    _rockers = new RockersMatrix(*_rockers_model, _settings);
    _rockers_logic = new RockersLogic(_settings, this);

    _btn_full_undo = new QPushButton("", this);
    _btn_undo = new QPushButton("", this);
    _btn_redo = new QPushButton("", this);
    _btn_config = new QPushButton("", this);
    _btn_highest_score = new QPushButton("", this);
    _btn_info = new QPushButton("", this);
    _lbl_move_counter = new QLabel(QString("Moves: 0   "), this);
    _central_widget = new QWidget(this);

    _win_logic = new WinLogic(this);
    _logger = new Logger(this);

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
    connect(_logger, &Logger::undoAvailablityChanged, _btn_full_undo, &QPushButton::setEnabled);
    connect(_logger, &Logger::redoAvailablityChanged, _btn_redo, &QPushButton::setEnabled);
    connect(_logger, &Logger::moveCounterChanged, this, &MainWindow::moveCounterChanged);
    connect(_btn_config, &QPushButton::clicked, this, &MainWindow::configBtnClicked);
    connect(_btn_info, &QPushButton::clicked, this, &MainWindow::infoBtnClicked);
}

void MainWindow::showEvent(QShowEvent *)
{
    _win_logic->block();
    if (_settings.seed() == Settings::SEED_IS_NOT_SET) {
        qsrand(static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay()));
        _settings.setSeed(qrand());
    }
    _minimum_moves = _rockers_model->shuffle(_settings.seed());
    _win_logic->unblock();
    qDebug() << "This puzzle might be solved in" << _minimum_moves << "moves";
    setWindowTitle(QString("Colobock (seed#%1)").arg(_settings.seed()));
}

void MainWindow::winCatcher()
{
    QMessageBox msgBox;
    QAbstractButton *btnYes = msgBox.addButton("I wanna more!", QMessageBox::YesRole);
    msgBox.setText("Cool! You was able to solve this puzzle. Would you like to try again?");
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

void MainWindow::configBtnClicked()
{
    ConfigDialog dialog(_settings);
    dialog.setModal(true);
    int dialogResult = dialog.exec();
    if (dialogResult == QDialog::Accepted)
    {
        _settings = dialog.settings();
        restartLayout();
    }
}

void MainWindow::infoBtnClicked()
{
    InfoDialog dialog;
    dialog.setModal(true);
    dialog.exec();
}
