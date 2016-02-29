#include "statisticsform.h"
#include "ui_statisticsform.h"
#include <QDebug>


StatisticsForm::StatisticsForm(QWidget *parent, QList<Fly*> list) :
    QMainWindow(parent),
    ui(new Ui::StatisticsForm)
{
    ui->setupUi(this);

    flysList = list;
    createStatistics();
}

StatisticsForm::~StatisticsForm()
{
    delete selModel;
    delete model;
    delete ui;
}

void StatisticsForm::createStatistics()
{
    model = new QStandardItemModel(flysList.count(), 6, this);
    model->setHeaderData(0, Qt::Horizontal, "Муха");
    model->setHeaderData(1, Qt::Horizontal, "Состояние");
    model->setHeaderData(2, Qt::Horizontal, "Тупость\n(секунды)");
    model->setHeaderData(3, Qt::Horizontal, "Возраст\n(секунды)");
    model->setHeaderData(4, Qt::Horizontal, "Пробег\n(число клеток)");
    model->setHeaderData(5, Qt::Horizontal, "Скорость\n(клеток в секунду)");

    for (int i=0; i<flysList.count(); i++)
    {
        Fly *fly = flysList.at(i);
        int id = i+1;

        QString status = "Жива";
        if (fly->getStatus()<2)
            status = "Мертва";
        QList<QTime> flyTimes = fly->getFlyTimes();
        int path = flyTimes.count();

        float age = fly->getLiveTime();
        float stupidity = fly->getStupidity();

        float sumTime = 0;

        for (int j=flyTimes.size()-1; j>=1; j--)
            sumTime += flyTimes.at(j-1).msecsTo(flyTimes.at(j));
        if (flyTimes.size()!=0)
            sumTime += fly->getStartTime().msecsTo(flyTimes.at(0));

        float speed = 0;
        if (sumTime !=0)
            speed = (float) path/sumTime * 1000;

        model->setData(model->index(i,0), id);
        model->setData(model->index(i,1), status);
        model->setData(model->index(i,2), stupidity);
        model->setData(model->index(i,3), age);
        model->setData(model->index(i,4), path);
        model->setData(model->index(i,5), speed);
    }

    ui->tableView->setModel(model);


    selModel = new QItemSelectionModel(model);

    ui->tableView->setSelectionModel(selModel);

    connect(ui->tableView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(currentChanged(QModelIndex,QModelIndex)));

    ui->tableView->resizeColumnsToContents();
}

void StatisticsForm::closeEvent(QCloseEvent *event)
{
    for (int i=0; i<flysList.size(); i++)
    {
        Fly *fly = flysList.at(i);
        int status = fly->getStatus();
        if (status == FLY_DEAD_SELECTED || status == FLY_ALIVE_SELECTED)
        {
                fly->setStaus(status-1);
                break;
        }
    }
    emit statusesUpdated();
    event->accept();
}

void StatisticsForm::currentChanged(QModelIndex curr, QModelIndex prev)
{
    int row = curr.row();

    Fly *fly = flysList.at(row);
    int status = fly->getStatus();
    if (status == FLY_DEAD_SELECTED || status == FLY_ALIVE_SELECTED)
        return;
    else
        fly->setStaus(status+1);

    for (int i=0; i<flysList.size(); i++)
    {
        Fly *fly = flysList.at(i);
        int status = fly->getStatus();
        if (i!=row)
        {
            if (status == FLY_DEAD_SELECTED || status == FLY_ALIVE_SELECTED)
                fly->setStaus(status-1);
        }
    }

    emit statusesUpdated();
}
