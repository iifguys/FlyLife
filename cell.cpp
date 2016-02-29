#include "cell.h"
#include <QDebug>

Cell::Cell(MyGLWidget *parent, int count, int max_count, int cell_count, int left, int top) : QObject(parent)
{
    widget = parent;
    paintCount = count;
    maxFlysCount = max_count;

    size = cell_count;
    fromLeft = left;
    fromTop = top;

    cellFlys = new Fly*[maxFlysCount];

    for (int i=0; i<maxFlysCount; i++)
    {
        cellFlys[i] = NULL;
    }

}

Cell::~Cell()
{

}

bool Cell::addFly(Fly *fly)
{
    if (getFlysCount() == maxFlysCount)
        return false;

    int size_in_pixels = FLY_SIZE*size*widget->getCountInOneCell() + size-1;

    for (int i=0; i<maxFlysCount; i++)
    {
        int left_in_cell = i%paintCount;
        int top_in_cell = i/paintCount;
        int pos = i;

        //qDebug()<<"getFlysCount"<<getFlysCount();
        //qDebug()<<this<<this->fromLeft<<this->fromTop;

        //qDebug()<<"left_in_cell"<<left_in_cell<<"top_in_cell"<<top_in_cell<<"paintCount"<<paintCount;

        if (cellFlys[pos] == NULL)
        {
            cellFlys[pos] =  fly;
            fly->setCurrentCell(this);
            fly->setCurrentPosition(pos);
            int left = fromLeft*(FLY_SIZE*widget->getCountInOneCell()+1) + left_in_cell*FLY_SIZE;
            int top = size_in_pixels - (fromTop*(FLY_SIZE*widget->getCountInOneCell()+1) + top_in_cell*FLY_SIZE);
            fly->setLeftTop(left, top);
            break;
        }
    }
    return true;
}

void Cell::removeFly(int pos)
{
    cellFlys[pos] = NULL;
}

Cell *Cell::getRandomNeibour()
{
    return widget->getRandomNeibour(fromLeft, fromTop);
}

int Cell::getFlysCount()
{
    int count = 0;
    for (int i=0; i<maxFlysCount; i++)
        if (cellFlys[i]!=NULL)
            count++;
    return count;
}

