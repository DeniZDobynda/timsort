#include <iostream>
void merge ( int*& mass, int first, int lenght1, int second, int lenght2)
{
    if ( first > second )
    {
        std::swap(first, second);
        std::swap(lenght1, lenght2);
    }

    int copymass[lenght1];

    for ( int i = 0; i < lenght1; ++i)
    {
        copymass[i] = mass[i + first];
    }

    int i = 0;
    int j = second;

    int k = first;

    while ( i < lenght1 && j < second + lenght2)
    {
        if ( mass[j] < copymass[i])
        {
            mass[k++] = mass[j++];
        }else{
            mass[k++] = copymass[i++];
        }
    }

    while ( i < lenght1 )
    {
        mass[k++] = copymass[i++];
    }

    return ;
}
