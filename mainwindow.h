#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myglwidget.h"
#include "addnewflyform.h"
#include "general_includes.h"

namespace Ui {
class MainWindow;
}

/// класс главного окна программы
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// стандартный конструктор QMainWindow
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /// функция инициализации стартовых параметров окна
    /// необходим вызов сразу после конструктора
    void initialize(QRect rect);

private:

    MyGLWidget *widget;         /// указатель на объект MyGLWidget с формы

    AddNewFlyForm *addFlyForm;  /// указатель на объект AddNewFlyForm

    int capacity;               /// мухоемкость
    int size;                   /// размерм поля в клетках

    int cur_width;              /// стартовая шириная widget
    int cur_height;             /// стартовая высота widget

    State currentState;         /// текущее состояние работы программы

    /// обновление параметров widget
    void updateGLWidget();

    /// обновление внешнего вида окна
    void updateState();

private slots:
    /// слот на изменение размера поля
    void on_sb_size_valueChanged(int arg1);

    /// слот на изменение мухоемкости
    void on_sb_capacity_valueChanged(int arg1);

    /// слот на Действие "Новая муха"
    void on_action_3_triggered();

    /// слот на нажатие кнопки "Применить"
    void on_pb_setParamms_clicked();

    /// слот на Действие "Выход"
    void on_action_6_triggered();

    /// слот на Действие "Пуск"
    void on_action_triggered();

    /// слот на Действие "Стоп"
    void on_action_2_triggered();

    /// слот на Действие "Очистить"
    void on_action_4_triggered();

    /// слот для установки текущего состояния работы программы
    void setState(State state);
private:
    /// указатель для работы с GUI
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
