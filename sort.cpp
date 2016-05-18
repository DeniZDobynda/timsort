#include <divide.cpp>
#include <time.h>
#include <QTime>

float rand_sort(int count, int how_much = 1, int degree = 1)
{
    float time_aver = 0;

    for ( int n = 0; n < how_much; ++n)
    {
        int* mass = new int[n];
        qsrand((uint)QTime(0,0,0).msecsTo(QTime::currentTime()));
        for ( int i = 0; i < count; ++i)
        {
            mass[i] = qrand()%1000000;
        }
        float timer = -clock();
        divide_and_sort(mass, count);
        timer += clock();
        time_aver += timer;
    }
    time_aver /= how_much;
    time_aver *= degree;
    time_aver /= CLOCKS_PER_SEC;

    return time_aver;
}
