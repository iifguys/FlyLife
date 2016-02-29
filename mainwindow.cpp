#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QRect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    size = ui->sb_size->value();
    capacity = ui->sb_capacity->value();

    widget = ui->widget;

    connect(widget, SIGNAL(stateChanged(State)), this, SLOT(setState(State)));

    addFlyForm = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize(QRect rect)
{
    //showFullScreen();


    resize(rect.width(), rect.height());

    cur_width = widget->width();
    cur_height = widget->height();
    setState(INITIALIZE);
}

void MainWindow::updateGLWidget()
{    
    widget->setFixedSize(cur_width, cur_height);

    widget->setCapacity(capacity);
    widget->setSizeOfField(size);
    widget->updateWidget();
}

void MainWindow::updateState()
{
    switch (currentState) {
    case INITIALIZE:
        ui->action->setEnabled(false);
        ui->action_2->setEnabled(false);
        ui->action_3->setEnabled(false);
        ui->action_4->setEnabled(false);
        ui->action_6->setEnabled(true);

        ui->groupBox->setEnabled(true);
        ui->pb_setParamms->setEnabled(true);
        break;
    case ADD_FLYS:
        ui->action->setEnabled(true);
        ui->action_2->setEnabled(false);
        ui->action_3->setEnabled(true);
        ui->action_4->setEnabled(true);
        ui->action_6->setEnabled(true);

        ui->groupBox->setEnabled(false);
        ui->pb_setParamms->setEnabled(false);
        break;
    case PLAYING:
        ui->action->setEnabled(false);
        ui->action_2->setEnabled(true);
        ui->action_3->setEnabled(false);
        ui->action_4->setEnabled(false);
        ui->action_6->setEnabled(false);

        ui->groupBox->setEnabled(false);
        ui->pb_setParamms->setEnabled(false);
        break;
    case STOPED:
        ui->action->setEnabled(false);
        ui->action_2->setEnabled(false);
        ui->action_3->setEnabled(false);
        ui->action_4->setEnabled(true);
        ui->action_6->setEnabled(true);

        ui->groupBox->setEnabled(false);
        ui->pb_setParamms->setEnabled(false);
        break;
    }
}

void MainWindow::on_sb_size_valueChanged(int arg1)
{
    size = arg1;
}

void MainWindow::on_sb_capacity_valueChanged(int arg1)
{
    capacity = arg1;
}
// новая муха
void MainWindow::on_action_3_triggered()
{
    if (addFlyForm!=NULL)
        delete addFlyForm;

    addFlyForm = new AddNewFlyForm(widget, size, capacity);
    connect(addFlyForm, SIGNAL(newFlyReady(int,int,float)), widget, SLOT(addNewFly(int,int,float)));
    connect(addFlyForm, SIGNAL(generateRandom(int,float,float)), widget, SLOT(generateRandom(int,float,float)));

    addFlyForm->show();
}

void MainWindow::on_pb_setParamms_clicked()
{
    setState(ADD_FLYS);
    updateGLWidget();
}
// выход
void MainWindow::on_action_6_triggered()
{
    close();
}
// пуск
void MainWindow::on_action_triggered()
{
    setState(PLAYING);
    widget->startFlys();
}
// стоп
void MainWindow::on_action_2_triggered()
{
    setState(STOPED);
    widget->stopFlys();
}
// очистить
void MainWindow::on_action_4_triggered()
{
    setState(INITIALIZE);
    widget->clearAll();
}

void MainWindow::setState(State state)
{
    currentState = state;
    updateState();
}
