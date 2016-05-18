#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpropertyanimation>
#include <partition.h>


#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void entry_animation(int n);

    void swap_animation(int i, int j);

    void divide_and_sort(int*& mass, int n);

    void insert_sort( int*& mass, int first, int last);

    void merge ( int*& mass, int first, int lenght1, int second, int lenght2);

    void check ( int*& mass, Partition& partition, int n);

    float rand_sort(int countt, int how_much, int degree);

    float timsort(int*& mas, int countt, int how_much, int degree);

    void merge_area_intro(int first, int last);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_sliderReleased();

    void on_lineEdit_returnPressed();

    void on_horizontalSlider_sliderMoved();

private:
    Ui::MainWindow *ui;
    QPropertyAnimation **mAnimation;
    QPushButton ** button;
    QPushButton ** merge_button;

    int * coordinates;
    int * Y;
    int count;

    int * masss;

    int del = 100;
};

#endif // MAINWINDOW_H
