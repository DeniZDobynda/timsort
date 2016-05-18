#include <merge.cpp>
#include <partition.h>

void check ( int*& mass, Partition& partition, int n)
{
    if ( partition.count >= 2)
    {
        item *X = partition.pop();
        item *Y = partition.pop();

        if ( X->lenght > Y->lenght || X->lenght + Y->lenght == n)
        {
            merge(mass, Y->start, Y->lenght, X->start, X->lenght);
            partition.push(Y->start, Y->lenght + X->lenght);
            check(mass, partition, n);
        }else{
            partition.push(Y->start, Y->lenght);
            partition.push(X->start, X->lenght);
        }
    }
    return ;
}
