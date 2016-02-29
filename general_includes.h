#ifndef GENERAL_INCLUDES
#define GENERAL_INCLUDES

/// интервал отрисовки в миллисекундах
#define PAINT_TIME_INTERVAL 1000/50

/// размер иконки мухи в пикселях
#define FLY_SIZE 16

/// статусы мухи в ходе работы программы
#define FLY_DEAD 0
#define FLY_DEAD_SELECTED 1
#define FLY_ALIVE 2
#define FLY_ALIVE_SELECTED 3

/// возможные состояния программы
enum State{INITIALIZE, ADD_FLYS, PLAYING, STOPED};

#endif // GENERAL_INCLUDES

