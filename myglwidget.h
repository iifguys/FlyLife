#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QProgressBar>
#include "general_includes.h"
#include "cell.h"
#include "fly.h"
#include "statisticsform.h"
#include <QtMultimedia/QSound>


class Cell;
class Fly;
class StatisticsForm;

/// класс виджета отрисовки поля с помощью OpenGL
class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    /// Стандартный конструктор QGLWidget
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();

    /// сеттер для размера поля в клетках
    void setSizeOfField(int size);

    /// сеттер для установки мухоемкости
    void setCapacity(int capacity);

    /// обновление параметров виджета и создание клеток
    void updateWidget();

    /** получение случайного соседа клетки
     * @param fromLeft - смещение исходной клетки относительно левого края поля
     * @param fromTop - смещение исходной клетки относительно верхнего края поля
     * @return указатель на объект соседней клетки
    */
    Cell* getRandomNeibour(int fromLeft, int fromTop);

    /// геттер для размера клетки в мухах
    int getCountInOneCell(){return count_in_one_optimal;}

    /** загрузка текстуры
     * @param name - путь к файлу текстуры
     * @return идентификатор текстуры
    */
    int loadTexture(QString name);

    /** проверка на заполненность клетки
     * @param row - ряд клетки (начиная с 1)
     * @param col - столбец клетки (начиная с 1)
     * @return true - если заполнена, false - если нет
    */
    bool isFullCell(int row, int col);

    /** проверка на заполненность клетки
     * @param cell - указатель на объект клетки
     * @return true - если заполнена, false - если нет
    */
    bool isFullCell(Cell *cell);

    /// запуск моделирования
    void startFlys();

    /// остановка моделирования
    void stopFlys();

    /// очистка контейнеров и поля
    void clearAll();
private:

    QList<int> textures;            /// Список загруженных текстур

    bool started;                   /// флаг запуска отрисовки
    bool flyStarted;                /// флаг запуска моделирования

    QTimer timer;                   /// таймер отрисовки поля

    int width_my;                   /// ширина виджета в пикселях
    int height_my;                  /// высота виджета в пикселях

    int size;                       /// размер поля в клетках
    int capacity;                   /// мухоемкость

    int count_in_one_optimal;       /// размер клетки в мухах

    Cell** cellsMap;                /// массив указателей на объекты клеток

    QList<Fly*> flysList;           /// список указателей на объекты мух

    StatisticsForm *statisticsForm; /// указатель на форму статистики StatisticsForm

    QSound *sound;                  /// вж-вж-вж

signals:
    /// сигнал на изменение текущего состояния работы программы
    void stateChanged(State state);

protected:
    /// переопределение initializeGL из класса QGLWidget
    void initializeGL();

    /// переопределение resizeGL из класса QGLWidget
    void resizeGL(int w, int h);

    /// переопределение paintGL из класса QGLWidget
    void paintGL();

public slots:
    /// слот на добавление новой мухи в клетку
    /// клетка задается координатами
    void addNewFly(int row, int col, float stupidity);

    /// слот на добавление новой мухи в клетку
    /// клетка задается указателем
    void addNewFly(Cell *cell, float stupidity);

    /** слот на случайную генерацию мух на поле
    * @param flysCount - число создаваемых мух
    * @param minStupid - минимальная тупость мухи
    * @param maxStupid - максимальная тупость мухи
    */
    void generateRandom(int flysCount, float minStupid, float maxStupid);

};

#endif // MYGLWIDGET_H
