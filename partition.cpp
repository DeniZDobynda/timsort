#include "partition.h"
#include <QMainWindow>

Partition::Partition()
{
    head = NULL;

    count = 0;
}

void Partition::push(int st, int len)
{
    if ( head )
    {
        item * nevv = new item;

        nevv->lenght = len;
        nevv->start = st;

        nevv->next = head;

        head = nevv;

    }else{
        head = new item;

        head->lenght = len;

        head->start = st;

        head->next = NULL;
    }
    ++count;
}

item* Partition::pop()
{
    if (!head) return NULL;

    item *temp = head;

    head = head->next;

    temp->next = NULL;

    --count;

    return temp;
}
