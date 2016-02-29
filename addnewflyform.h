#ifndef ADDNEWFLYFORM_H
#define ADDNEWFLYFORM_H

#include <QMainWindow>
#include "myglwidget.h"

class MyGLWidget;

namespace Ui {
class AddNewFlyForm;
}
/// класс формы для добавления мух на поле
class AddNewFlyForm : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @param parent - указатель на родительский объект MyGLWidget
     * @param size - размер поля в клетках
     * @param capacity - мухоемкость одной клетки
    */
    explicit AddNewFlyForm(MyGLWidget *parent, int size, int capacity);
    ~AddNewFlyForm();

private slots:
    /// слот на нажатие кнопки "Добавить"
    void on_pb_add_clicked();

    /// слот на нажатии кнопки "Закрыть"
    void on_pb_close_clicked();

    /// слот на нажатие чекбокса "Случайная генерация"
    void on_cb_generate_clicked(bool checked);

    /// слот на изменение значения Минимальной тупости
    void on_dsb_minStupidity_valueChanged(double arg1);

    /// слот на изменение значения Максимальной тупости
    void on_dsb_maxStupidity_valueChanged(double arg1);

private:
    /// указатель на GUI компоненты
    Ui::AddNewFlyForm *ui;

    /// указатель на родительский объект MyGLWidget
    MyGLWidget *widget;

signals:
    /// сигнал на добаление новой мухи в клетку с координатами (row,col) и тупостью stupidity
    void newFlyReady(int row, int col, float stupidity);

    /// сигнал на добаление новых flysCount мух с тупостью от minStupid до  maxStupid
    void generateRandom(int flysCount, float minStupid, float maxStupid);
};

#endif // ADDNEWFLYFORM_H
