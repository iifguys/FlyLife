#ifndef STATISTICSFORM_H
#define STATISTICSFORM_H

#include <QMainWindow>
#include "fly.h"
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QCloseEvent>

class Fly;

namespace Ui {
class StatisticsForm;
}

/// класс формы вывода статистики полетов
class StatisticsForm : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @param parent - указатель на родительский объект QWidget
     * @param list - список указателей на объекты мух
    */
    explicit StatisticsForm(QWidget *parent, QList<Fly*> list);
    ~StatisticsForm();

    /// переопределение closeEvent от QMainWindow
    void closeEvent(QCloseEvent *event);

private slots:
    /// слот на изменение текущего выбранного элемента в tableView на форме
    void currentChanged(QModelIndex curr, QModelIndex prev);

private:
    Ui::StatisticsForm *ui;         /// указатель для работы с GUI

    QList<Fly*> flysList;           /// список указателей на объекты мух

    QStandardItemModel *model;      /// модель для заполнения статистики

    QItemSelectionModel *selModel;  /// модель для отслеживания выделений

    /// формирование статистики по мухам
    void createStatistics();
signals:
    /// сигнал о обновлении статусов мух
    void statusesUpdated();
};

#endif // STATISTICSFORM_H
