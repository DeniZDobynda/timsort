#include <mainwindow.h>
#include <QTime>

void delay(int n)
{
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
/*
void swap_animation_sort(int i, int j, int del = 100)
{
    delete mAnimation;

    if ( coordinates[i] > coordinates[j])
    {
        std::swap(i, j);
    }
    mAnimation = new QPropertyAnimation*[4];

    mAnimation[0] = new QPropertyAnimation(button[i], "geometry");
    mAnimation[0]->setDuration(del);
    mAnimation[0]->setStartValue(QRect(coordinates[i], 100, 20, 20));
    mAnimation[0]->setEndValue(QRect(coordinates[i] + abs((coordinates[j]-coordinates[i])/2), 120, 20, 20));

    mAnimation[1] = new QPropertyAnimation(button[j], "geometry");
    mAnimation[1]->setDuration(del);
    mAnimation[1]->setStartValue(QRect(coordinates[j], 100, 20, 20));
    mAnimation[1]->setEndValue(QRect(coordinates[j] + (-1)*abs((coordinates[i]-coordinates[j])/2), 80, 20, 20));

    mAnimation[2] = new QPropertyAnimation(button[i], "geometry");
    mAnimation[2]->setDuration(del);
    mAnimation[2]->setStartValue(QRect(coordinates[i] + abs((coordinates[j]-coordinates[i])/2), 120, 20, 20));
    mAnimation[2]->setEndValue(QRect(coordinates[j], 100, 20, 20));

    mAnimation[3] = new QPropertyAnimation(button[j], "geometry");
    mAnimation[3]->setDuration(del);
    mAnimation[3]->setStartValue(QRect(coordinates[j] + (-1)*abs((coordinates[i]-coordinates[j])/2), 80, 20, 20));
    mAnimation[3]->setEndValue(QRect(coordinates[i], 100, 20, 20));

    std::swap(coordinates[i], coordinates[j]);


    mAnimation[0]->start();
    mAnimation[1]->start();
    delay(del);
    mAnimation[2]->start();
    mAnimation[3]->start();

}
*/
