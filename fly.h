#ifndef FLY_H
#define FLY_H

#include <QObject>
#include "cell.h"
#include "general_includes.h"
#include <QMutex>
#include <QThread>
#include <QTime>

class Cell;

/// класс мухи, наследуемый от QThread для реализации собственного потока
class Fly : public QThread
{
    Q_OBJECT
public:
    /**
     * @param textures - список текстур для статусов мухи
     * @param id - идентификатор мухи
     * @param size - размер поля в клетках
     * @param parent - указатель на родительский объект QObject
     * @param status - статус мухи (от 0 до 3)
    */
    explicit Fly( QList<int> textures, int id, int size,  QObject *parent = 0, int status = 0);
    ~Fly();

    int ready_left;     /// смещение в пикселях от левого края поля (после вызова getLeftTop)
    int ready_top;      /// смещение в пикселях от верхнего края поля (после вызова getLeftTop)

    /// геттер и сеттер для текущей клетки
    Cell *getCurrentCell(){return currentCell;}
    void setCurrentCell(Cell *cell){currentCell = cell;}

    /// геттер и сеттер для тупости
    float getStupidity(){return stupidity;}
    void setStupidity(float stupid){ stupidity = stupid;}

    /// геттер и сеттер для текущей позиции в клетке
    int getCurrentPosition(){return currentPosition;}
    void setCurrentPosition(int pos){ currentPosition = pos;}

    /// геттер и сеттер для текущих смещений относительно левого и верхнего краев поля
    void getLeftTop();
    void setLeftTop(int x, int y);

    /// отрисовка мухи на поле
    void paintFly();

    /// геттер и сеттер для статуса мухи
    int getStatus();
    void setStaus(int s);

    /// геттер для списка времен полетов
    QList<QTime> getFlyTimes () {return flyTimes;}

    /// геттер для времени жизни в секундах
    float getLiveTime();

    /// геттер для времени старта
    QTime getStartTime() {return start_time;}

private:
    float stupidity;        /// тупость
    Cell *currentCell;      /// текущая клетка
    Cell *prevCell;         /// предыдущая клетка
    int currentPosition;    /// текущая позиция в клетке

    int left;               /// координата x для левой границы отрисовки
    int top;                /// координата y для верхней границы отрисовки

    QMutex mutexLeftTop;    /// Мьютекс для доступа к координатам отрисовки
    QMutex mutexStatus;     /// Мбютекс для доступа к статусу

    QList<int> textures;
    int status;             /// 0 - мертвая, 1 - мертвая выделенная, 2 - живая, 3 - живая выделенная

    int id_number;          /// номер мухи

    int size;               /// размер поля

    QTime start_time;       /// начало жизни (время старта)
    QTime death_time;       /// время смерти

    QList<QTime> flyTimes;  /// времена полетов

protected:
    /// переопределение метода run из QThread
    void run();

signals:

public slots:
};

#endif // FLY_H
