
#include "mainwindow.cpp"



void insert_sort( int*& mass, int first, int last)
{
    if ( first < 0 || last > (int)sizeof(mass)) return ;

    int i = first + 1;

    while ( i < last )
    {
        int key = mass[i];

        int j = i-1;

        while ( j >= first && mass[j] > key )
        {
            mass[j+1] = mass[j];
            swap_animation(j+1+1, j+1, 100);
            delay(100);
            --j;
        }

        mass[j+1] = key;

        ++i;
    }
    return ;
}
////think
