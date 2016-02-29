#include "myglwidget.h"
#include <QDebug>
#include <QTime>
#include <QMessageBox>

MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent)
{

    started = false;
    size = 10;
    capacity = 5;
    width_my = width();
    height_my = height();
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));

    cellsMap = NULL;

    qsrand(QTime::currentTime().msec());

    statisticsForm = NULL;

    flyStarted = false;

    sound = new QSound(":/snd/sounds/F-kin_Fly.wav", this);
    sound->setLoops(QSound::Infinite);
}

MyGLWidget::~MyGLWidget()
{
    delete sound;
}

void MyGLWidget::setSizeOfField(int size)
{
    this->size = size;
}

void MyGLWidget::setCapacity(int capacity)
{
    this->capacity = capacity;
}

void MyGLWidget::updateWidget()
{
    //qDebug()<<"width_my"<<width_my;
    int count_h_16_all = (width_my - size + 1)/FLY_SIZE;                // число мух по горизонтали
    int count_in_one_h = count_h_16_all/size;                           // число мух на одну клетку по горизонтали
    int count_h_16_optimal = count_in_one_h*FLY_SIZE*size + size - 1;   // оптимальная ширина виджета

    int count_v_16_all = (height_my - size + 1)/FLY_SIZE;               // аналогично по вертикали
    int count_in_one_v = count_v_16_all/size;
    int count_v_16_optimal = count_in_one_v*FLY_SIZE*size + size - 1;

    // вычисление оптимального размера виджета и числа мух на одну клетку (в одном направлении)
    int count_optimal =count_v_16_optimal;
    count_in_one_optimal = count_in_one_v;
    if (count_h_16_optimal<count_optimal)
    {
        count_optimal = count_h_16_optimal;
        count_in_one_optimal = count_in_one_h;
    }

    setFixedSize(count_optimal, count_optimal);

    //qDebug()<<"capacity"<<capacity<<"count_in_one_optimal"<<count_in_one_optimal;

    if (capacity>count_in_one_optimal*count_in_one_optimal)
    {
        QMessageBox::information(this,
                                 "Невозможно создать поле",
                                 QString("Создаваемое поле позволяет вместить %1 мух на одну клетку при мухоемкости %2."
                                 "Пожалуйста, измените параметры поля или снизьте мухоемкость.")
                                 .arg(count_in_one_optimal*count_in_one_optimal).arg(capacity),
                                 QMessageBox::Ok);

        clearAll();
        emit stateChanged(INITIALIZE);
        return;
    }


    cellsMap = new Cell*[size*size];

    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size; j++)
        {
            Cell *cell = new Cell(this, count_in_one_optimal, capacity, size, i, j);
            int pos = i*size +j;
            cellsMap[pos] = cell;
        }
    }


    started = true;

    updateGL();
}

Cell *MyGLWidget::getRandomNeibour(int fromLeft, int fromTop)
{
    bool ok = false;
    int pos;
    int curPos = fromLeft*size + fromTop;
    while (!ok)
    {
        int random_left = 0;
        int random_top = 0;

        if (fromLeft == 0)
            random_left = qrand()%2;
        else if (fromLeft == size-1)
            random_left = fromLeft - qrand()%2;
        else
        {
            int r =  qrand()%3;
            if (r==0)
                random_left = fromLeft;
            else if (r==1)
                random_left = fromLeft+1;
            else
                random_left = fromLeft-1;
        }

        if (fromTop == 0)
            random_top = qrand()%2;
        else if (fromTop == size-1)
            random_top = fromTop - qrand()%2;
        else
        {
            int r =  qrand()%3;
            if (r==0)
                random_top = fromTop;
            else if (r==1)
                random_top = fromTop+1;
            else
                random_top = fromTop-1;
        }

        pos = random_left*size +random_top;

        if (pos != curPos)
            ok = true;
    }

    return cellsMap[pos];
}

int MyGLWidget::loadTexture(QString name)
{
    QImage img(name);

    int tex = bindTexture(img);


    return tex;
}

bool MyGLWidget::isFullCell(int row, int col)
{
    int pos = (col-1)*size +(row-1);
    if (cellsMap[pos]->getFlysCount()==capacity)
        return true;
    return false;
}

bool MyGLWidget::isFullCell(Cell *cell)
{
    if (cell->getFlysCount()==capacity)
        return true;
    return false;
}

void MyGLWidget::startFlys()
{
    flyStarted = true;
    for (int i=0; i<flysList.size(); i++)
        flysList.at(i)->start();

    timer.start(PAINT_TIME_INTERVAL);
    sound->play();
}

void MyGLWidget::stopFlys()
{
    sound->stop();
    flyStarted = false;
    for (int i=0; i<flysList.size(); i++)
        flysList.at(i)->terminate();
    timer.stop();

    statisticsForm = new StatisticsForm(this, flysList);
    connect(statisticsForm, SIGNAL(statusesUpdated()), this, SLOT(updateGL()));
    statisticsForm->show();

    emit stateChanged(STOPED);
}

void MyGLWidget::clearAll()
{
    if (started)
    {
        for (int i=0; i<size*size; i++)
            delete cellsMap[i];
        delete [] cellsMap;
    }

    for (int i=0; i<flysList.size(); i++)
    {
        delete flysList.at(i);
    }
    flysList.clear();

    size = 0;

    updateGL();
    started = false;
}

void MyGLWidget::initializeGL()
{
    if (textures.size()==0)
    {
        textures.append(loadTexture(":/images/deadFly.png"));
        textures.append(loadTexture(":/images/deadFlySelected.png"));
        textures.append(loadTexture(":/images/fly.png"));
        textures.append(loadTexture(":/images/flySelected.png"));
    }
}

void MyGLWidget::resizeGL(int w, int h)
{
    //qDebug()<<"width"<<w<<"height"<<h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -10, 1);
    glViewport(0, 0, w, h);
    width_my = w;
    height_my = h;
}

void MyGLWidget::paintGL()
{
    glClearColor(50.0, 50.0, 50.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!started)
        return;


    for (int i=1; i<size; i++)
    {
        int x = i*FLY_SIZE*count_in_one_optimal + i;
        glLineWidth(1);
        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex3f(x, 0, 1);
        glVertex3f(x, height_my, 1);
        glEnd();
    }

    for (int i=1; i<size; i++)
    {
        int y = i*FLY_SIZE*count_in_one_optimal + i;
        glLineWidth(1);
        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex3f(0, y, 1);
        glVertex3f(width_my, y, 1);
        glEnd();
    }


    bool stop = true;
    for (int i=0; i<flysList.size(); i++)
    {
        flysList.at(i)->paintFly();
        if (flysList.at(i)->getStatus()>1)
            stop = false;
    }

    if (stop && flyStarted)
    {
        stopFlys();
    }
}

void MyGLWidget::addNewFly(int row, int col, float stupidity)
{
    Fly *fly = new Fly(textures, flysList.size()+1, size, this, FLY_ALIVE);
    fly->setStupidity(stupidity);
    flysList.append(fly);

    int pos = (col-1)*size +(row-1);

    cellsMap[pos]->addFly(fly);

    updateGL();
}

void MyGLWidget::addNewFly(Cell *cell, float stupidity)
{
    Fly *fly = new Fly(textures, flysList.size()+1, size, this, FLY_ALIVE);
    fly->setStupidity(stupidity);
    flysList.append(fly);

    cell->addFly(fly);

    updateGL();
}

void MyGLWidget::generateRandom(int flysCount, float minStupid, float maxStupid)
{
    int freeSlots = size*size*capacity - flysList.size();
    if (flysCount > freeSlots)
    {
        QMessageBox::information(this, "Не выполнено",
                                 QString("Невозможно добавить %1 мух. Осталось %2 пустых позиций на поле.")
                                 .arg(flysCount).arg(freeSlots),
                                 QMessageBox::Ok);
        return;
    }

    qsrand(QTime::currentTime().msec());

    int i=0;
    while (i<flysCount)
    {
        int rand = qrand() % (size*size);

        Cell *cell = cellsMap[rand];
        if (isFullCell(cell))
            continue;

        float stupidity = (static_cast<float>(qrand()) / RAND_MAX)*(maxStupid-minStupid) + minStupid;
        addNewFly(cell, stupidity);
        i++;
    }
}

