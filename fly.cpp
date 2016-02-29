#include "fly.h"
#include <QDebug>

Fly::Fly(QList<int> textures, int id, int size, QObject *parent, int status) : QThread(parent)
{
    left = 0;
    top = FLY_SIZE-1;

    ready_left = left;
    ready_top = top;

    this->textures = textures;

    this->status = status;
    id_number = id;

    currentCell = NULL;
    prevCell = NULL;

    this->size = size;
}

Fly::~Fly()
{

}

void Fly::getLeftTop()
{
    mutexLeftTop.lock();
    ready_left = left;
    ready_top = top;
    mutexLeftTop.unlock();
}

void Fly::setLeftTop(int x, int y)
{
    mutexLeftTop.lock();
    left = x;
    top = y;
    mutexLeftTop.unlock();

    //qDebug()<<"fly left"<<x<<"top"<<y;
}

void Fly::paintFly()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);

    int texture;
    int st = getStatus();

    texture = textures.at(st);
    getLeftTop();

    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();

    glTranslatef(ready_left, ready_top, 0);
    //glRotatef(a2, 0, 0, 1);

    glBegin(GL_POLYGON);

    glTexCoord2d(0, 1); glVertex3f(0, 0, 1);
    glTexCoord2d(0, 0); glVertex3f(0, -FLY_SIZE, 1);
    glTexCoord2d(1, 0); glVertex3f(FLY_SIZE, -FLY_SIZE, 1);
    glTexCoord2d(1, 1); glVertex3f(FLY_SIZE, 0, 1);

    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
}

int Fly::getStatus()
{
    int s;
    mutexStatus.lock();
    s = status;
    mutexStatus.unlock();
    return s;
}

void Fly::setStaus(int s)
{
    mutexStatus.lock();
    status = s;
    mutexStatus.unlock();
}

float Fly::getLiveTime()
{
    int msecs = start_time.msecsTo(death_time);

    return (float)msecs/1000;
}

void Fly::run()
{
    qsrand(QTime::currentTime().msec()+id_number);
    start_time = QTime::currentTime();
    while(getStatus()>1)
    {
        prevCell = currentCell;
        int pos = getCurrentPosition();
        Cell *cell = currentCell->getRandomNeibour();

        float rand = static_cast<float>(qrand()) / RAND_MAX ;

        long sleepTime = (long)(rand*getStupidity()*1000000);

        usleep(sleepTime);

        QTime curTime = QTime::currentTime();

        death_time = curTime;

        if (start_time.secsTo(curTime)>size*getStupidity())
        {
            //death_time = curTime;
            setStaus(FLY_DEAD);
            continue;
        }

        if (cell->addFly(this))
        {
            flyTimes.append(curTime);
            prevCell->removeFly(pos);
            // вычисление характеристик при движении
        }
    }
}

