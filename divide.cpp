#include <insertion_sort.cpp>
#include <minrun.cpp>
#include <partition.h>
#include <online.cpp>

void MainWindow::didivide_and_sort(int*& mass, int n)
{
    int minrunn = getMinrun(n);
    int i = 0;
    int j = 0;

    Partition partition;

    while ( i < n - 1)
    {
        if ( mass[i + 1] - mass[i] > 0)
        {
            while (i < n - 1 && mass[i + 1] - mass[i] > 0)
            {
                ++i;
            }
        }else{

            while ( i < n - 1 && mass[i + 1] - mass[i] <= 0)
            {
                ++i;
            }
            //this reversed, must rev_swap

            for ( int k = 0; k < (i-j)/2 - 1; ++k)
            {
                std::swap(mass[j + k], mass[i - k]);
            }

        }

        if ( i - j < minrunn )
        {
            i = j + minrunn;
            if ( i > n - 2)
            {
                i = n - 2;
            }
            insert_sort(mass, j, i + 1);
            partition.push(j, i - j + 1);
        }else{
            partition.push(j, i - j + 1);
        }

        i += 1;
        j = i;

        check(mass, partition, n);
    }
    check(mass, partition, n);

    return ;
}
