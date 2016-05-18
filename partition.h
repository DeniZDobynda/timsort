#ifndef PARTITION_H
#define PARTITION_H

struct item
{
    int start;
    int lenght;
    item * next;
};


class Partition
{
    item * head;


public:
    Partition();

    item* pop();

    void push(int , int);

    int count = 0;
};

#endif // PARTITION_H
