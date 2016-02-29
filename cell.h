#ifndef CELL_H
#define CELL_H

#include <QObject>
#include "fly.h"
#include <QMap>
#include "general_includes.h"
#include "myglwidget.h"

class Fly;
class MyGLWidget;

/// класс клетки поля
class Cell : public QObject
{
    Q_OBJECT
public:
    /**
     * @param parent - указатель на родительский объект MyGLWidget
     * @param count - размер клетки в мухах (count x count)
     * @param max_count - мухоемкость клетки
     * @param cell_count - размер поля в клетках
     * @param left - смещение клетки относительно левой границы поля
     * @param top - смещение клетки относительно верхней границы поля
    */
    explicit Cell(MyGLWidget *parent, int count, int max_count, int cell_count, int left, int top);
    ~Cell();

    /** добавлениt мухи в клетку
     * @param fly - указатель на объект мухи
     * @return true - если добавление успешно, в противном случае false
    */
    bool addFly(Fly *fly);

    /** удалениt мухи из клетки
     * @param pos - позиция мухи в клетке
    */
    void removeFly(int pos);

    /** получение случайного соседа клетки
     * @return указатель на объект соседней клетки
    */
    Cell* getRandomNeibour();

    /** установка мухоемкости
     * @param cap - мухоемкость клетки
    */
    void setCapacity(int cap) {maxFlysCount = cap;}

    /** получение текущего числа мух в клетке
     * @return число мух в клетке
    */
    int getFlysCount();


private:
    MyGLWidget *widget;             /// виджет в котором происходит отрисовка
    Fly** cellFlys;                 /// мухи и их позиции в клетке
    int paintCount;                 /// число возможных отрисовочных позиций в одном ряду
    int maxFlysCount;               /// мухоемкость
    int size;                       /// размер поля в клетках
    int fromLeft;                   /// номер клетки относительно левого края
    int fromTop;                    /// номер клетки относительно верхнего края
signals:

public slots:
};

#endif // CELL_H
