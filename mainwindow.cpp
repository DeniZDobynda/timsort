#include "mainwindow.h"
#include <QTime>
#include <timsort.h>
#include <time.h>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mAnimation(0)
{
    ui->setupUi(this);
    //QPrope
    count = 0;
}

void delay(int n)
{
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mAnimation;
}

void MainWindow::on_pushButton_clicked()
{
    if ( count != 0 )
    {
        for ( int i = 0; i < count; ++i)
        {
            button[i]->hide();
            delete button[i];
        }
        delete button;
    }

    bool ok;
    int n = ui->lineEdit->text().toInt(&ok, 10);
    if ( !ok ) return ;

    //ui->centralWidget->setGeometry(0, 0, 845, 100 + 40*(n/20 + 1));

    QDesktopWidget recDesc;

    QRect rec = recDesc.geometry();

    int h = 50 + 40*int(n/20);

    if ( n % 20 ) h += 40;

    if ( h > rec.height()-70 )
    {
        ui->lineEdit->setText("ERR");
        return ;
    }

    //h = 1000 * (h / 1000);

    int w = 430;

    if ( n >= 64 ) w = 870;

    this->setFixedSize(w, h);

    ui->line->setFixedHeight(h);

    button = new QPushButton*[n];

    qsrand((uint)QTime(0,0,0).msecsTo(QTime::currentTime()));

    masss = new int[n];

    for ( int i = 0; i < n; ++i)
    {
        masss[i] = qrand()%100;
        button[i] = new QPushButton(QString::number(masss[i]), this);
        button[i]->show();
    }

    entry_animation(n);

}

void MainWindow::swap_animation(int i, int j)
{
    delete mAnimation;

    if ( coordinates[i] > coordinates[j])
    {
        std::swap(i, j);
    }

    int k = 0;//(i/20)*400;
    int l = 0;//(j/20)*400;

    mAnimation = new QPropertyAnimation*[4];

    mAnimation[0] = new QPropertyAnimation(button[i], "geometry");
    mAnimation[0]->setDuration(del);
    mAnimation[0]->setStartValue(QRect(coordinates[i]-k, Y[i], 20, 20));
    mAnimation[0]->setEndValue(QRect(coordinates[i]-k + abs((coordinates[j]-coordinates[i])/2), Y[i] + 20, 20, 20));

    mAnimation[1] = new QPropertyAnimation(button[j], "geometry");
    mAnimation[1]->setDuration(del);
    mAnimation[1]->setStartValue(QRect(coordinates[j]-l, Y[j], 20, 20));
    mAnimation[1]->setEndValue(QRect(coordinates[j]-l + (-1)*abs((coordinates[i]-coordinates[j])/2), Y[j] - 20, 20, 20));

    mAnimation[2] = new QPropertyAnimation(button[i], "geometry");
    mAnimation[2]->setDuration(del);
    mAnimation[2]->setStartValue(QRect(coordinates[i]-k + abs((coordinates[j]-coordinates[i])/2), Y[i] + 20, 20, 20));
    mAnimation[2]->setEndValue(QRect(coordinates[j]-l, Y[j], 20, 20));

    mAnimation[3] = new QPropertyAnimation(button[j], "geometry");
    mAnimation[3]->setDuration(del);
    mAnimation[3]->setStartValue(QRect(coordinates[j]-l + (-1)*abs((coordinates[i]-coordinates[j])/2), Y[j] - 20, 20, 20));
    mAnimation[3]->setEndValue(QRect(coordinates[i]-k, Y[i], 20, 20));

    //std::swap(coordinates[i], coordinates[j]);
    std::swap(button[i], button[j]);

    mAnimation[0]->start();
    mAnimation[1]->start();
    delay(del);
    mAnimation[2]->start();
    mAnimation[3]->start();

}

void MainWindow::merge_area_intro(int first, int last)
{
    if ( first > last )
    {
        std::swap(first, last);
    }

    delete mAnimation;

    mAnimation = new QPropertyAnimation*[last - first + 1];
    delete merge_button;
    merge_button = new QPushButton*[last - first + 1];

    for ( int i = first; i < last; ++i)
    {
        merge_button[i - first] = new QPushButton(button[i]->text(), this );


        mAnimation[i - first] = new QPropertyAnimation(merge_button[i - first], "geometry");
        mAnimation[i - first]->setDuration(del);
        mAnimation[i - first]->setStartValue(QRect(coordinates[i], Y[i], 20, 20));
        mAnimation[i - first]->setEndValue(QRect(coordinates[i] + 450, Y[i], 20, 20));
    }

    for ( int i = first; i < last; ++i)
    {
        merge_button[i - first]->show();
        mAnimation[i - first]->start();
        button[i]->hide();
        delay(del);
    }

    return ;
}

void MainWindow::entry_animation( int n)
{
    mAnimation = new QPropertyAnimation*[n];

    coordinates = new int[n];

    Y = new int[n];

    count = n;

    int y = 10;

    int j = -400;

    for ( int i = 0; i < n; ++i)
    {

        if ( i % 20 == 0)
        {
            y += 40;
            j += 400;
        }
        mAnimation[i] = new QPropertyAnimation(button[i], "geometry");

        mAnimation[i]->setDuration(2000);
        mAnimation[i]->setStartValue(QRect(0, 0, 20, 20));
        mAnimation[i]->setEndValue(QRect(10 + i*20 - j, y, 20, 20));

        coordinates[i] = 10 + i*20 - j;
        Y[i] = y;
    }
    for ( int i = 0; i < n; ++i) mAnimation[i]->start();

}

void MainWindow::insert_sort( int*& mass, int first, int last)
{
    if ( first < 0 || last > count ) return ;

    int i = first + 1;

    while ( i <= last)
    {
        int j = i - 1;

        while ( j > first && mass[j] < mass[j - 1])
        {
            std::swap(mass[j - 1], mass[j]);
            swap_animation(j - 1, j);
            delay(del);
            --j;
        }
        ++i;
    }
}

void MainWindow::merge( int*& mass, int first, int lenght1, int second, int lenght2)
{

    if ( first > second )
    {
        std::swap(first, second);
        std::swap(lenght1, lenght2);
    }

    int copymass[lenght1];

    merge_area_intro(first, second);

    for ( int i = 0; i < lenght1; ++i)
    {
        copymass[i] = mass[i + first];
    }

    int i = first;
    int j = second;

    int k = first;

    while ( i < first + lenght1 && j < second + lenght2)
    {
        if ( mass[j] < copymass[i - first])
        {
            mass[k++] = mass[j++];

            delete mAnimation;
            mAnimation = new QPropertyAnimation*[2];
            mAnimation[0] = new QPropertyAnimation(button[j - 1], "geometry");
//            mAnimation[0]->setStartValue(QRect(coordinates[j - 1], Y[j - 1], 20, 20));
            mAnimation[0]->setEndValue(QRect(coordinates[k - 1], Y[k - 1], 20, 20));
            std::swap(button[j - 1], button[k - 1]);
            mAnimation[0]->setDuration(del);
            mAnimation[0]->start();
            delay(del);


        }else{
            mass[k++] = copymass[i - first];
            ++i;

            delete mAnimation;
            mAnimation = new QPropertyAnimation*[2];
            mAnimation[0] = new QPropertyAnimation(merge_button[i - 1 - first], "geometry");
            mAnimation[0]->setStartValue(QRect(coordinates[i - 1] + 500, Y[i - 1], 20, 20));
            mAnimation[0]->setEndValue(QRect(coordinates[k - 1], Y[k - 1], 20, 20));
            //button[k - 1] = merge_button[i - 1 - first];
           std::swap(merge_button[i - 1 - first], button[k - 1]);
            button[k - 1]->show();
            mAnimation[0]->setDuration(del);
            mAnimation[0]->start();
            delay(del);

        }
    }

    while ( i < first + lenght1 )
    {
        mass[k++] = copymass[i - first];
        ++i;

        delete mAnimation;
        mAnimation = new QPropertyAnimation*[2];
        mAnimation[0] = new QPropertyAnimation(merge_button[i - 1 - first], "geometry");
            mAnimation[0]->setStartValue(QRect(coordinates[i - 1] + 500, Y[i - 1], 20, 20));
        mAnimation[0]->setEndValue(QRect(coordinates[k - 1], Y[k - 1], 20, 20));
        std::swap(merge_button[i - 1 - first], button[k - 1]);
        button[k - 1]->show();
        mAnimation[0]->setDuration(del);
        mAnimation[0]->start();
        delay(del);
    }

    return ;
}

int getMinrun(int n)
{
    int r = 0;

    while ( n >= 64 )
    {
        r |= n & 1;
        n >>= 1;
    }

    return n+r;
}

void MainWindow::check ( int*& mass, Partition& partition, int n)
{

    if ( partition.count == 1) return ;
    else
    {
        if ( partition.count == 2)
        {
            item *X = partition.pop();
            item *Y = partition.pop();

            if ( X->lenght == Y->lenght || Y->lenght/2 < X->lenght || X->lenght + Y->lenght == n)
            {
                merge(mass, Y->start, Y->lenght, X->start, X->lenght);
                partition.push(Y->start, Y->lenght + X->lenght);
                check(mass, partition, n);
            }else{
                partition.push(Y->start, Y->lenght);
                partition.push(X->start, X->lenght);
            }
        }
        else
        {
            item * X = partition.pop();
            item * Y = partition.pop();
            item * Z = partition.pop();

            if ( X->lenght > Y->lenght + Z->lenght and Y->lenght > Z->lenght )
            {
                merge(mass, Y->start, Y->lenght, X->start, X->lenght);
                partition.push(Z->start, Z->lenght);
                partition.push(Y->start, X->lenght + Y->lenght);
                check(mass, partition, n);
            }
            else
            {
                if ( X->lenght < Z->lenght)
                {
                    merge(mass, Y->start, Y->lenght, X->start, X->lenght);
                    partition.push(Z->start, Z->lenght);
                    partition.push(Y->start, X->lenght + Y->lenght);
                    check(mass, partition, n);
                }
                else
                {
                    merge(mass, Z->start, Z->lenght, Y->start, Y->lenght);
                    partition.push(Z->start, Z->lenght + Y->lenght);
                    partition.push(X->start, X->lenght);
                    check(mass, partition, n);
                }
            }
        }
    }

    /*
    if ( partition.count >= 2)
    {
        item *X = partition.pop();
        item *Y = partition.pop();

        if ( X->lenght == Y->lenght || X->lenght <= Y->lenght / 2 - 1 || X->lenght + Y->lenght == n)
        {
            merge(mass, Y->start, Y->lenght, X->start, X->lenght);
            partition.push(Y->start, Y->lenght + X->lenght);
            check(mass, partition, n);
        }else{
            partition.push(Y->start, Y->lenght);
            partition.push(X->start, X->lenght);
        }
    }

    */
    return ;
}

void MainWindow::divide_and_sort(int*& mass, int n)
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
            if ( i > n - 1)
            {
                i = n - 1;
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

float MainWindow::rand_sort(int countt, int how_much = 1, int degree = 1)
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
        divide_and_sort(mass, countt);
        timer += clock();
        time_aver += timer;
    }
    time_aver /= how_much;
    time_aver *= degree;
    time_aver /= CLOCKS_PER_SEC;

    return time_aver;
}

float MainWindow::timsort(int*& mas, int countt, int how_much = 1, int degree = 1)
{
    float time_aver = 0;

    for ( int n = 0; n < how_much; ++n)
    {

        float timer = -clock();
        divide_and_sort(mas, countt);
        timer += clock();
        time_aver += timer;
    }
    time_aver /= how_much;
    time_aver *= degree;
    time_aver /= CLOCKS_PER_SEC;

    return time_aver;
}

void MainWindow::on_pushButton_2_clicked()
{
    float timer = 0;

    if ( count > 1 && count < 1000 ) timer = timsort(masss, count);

    QString t = "time = ";
    t.append(QString::number(timer));
    t.append(" seconds");
    ui->time->setText(t);
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    del = ui->horizontalSlider->value();
}

void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

void MainWindow::on_horizontalSlider_sliderMoved()
{
    del = ui->horizontalSlider->value();
}
