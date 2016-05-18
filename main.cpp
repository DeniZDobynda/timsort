#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}





















/*
#include <QVector>
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QApplication>

class WCwindow : public QMainWindow
{
public:
    WCwindow();
private:
    QVector<QLabel*> cams;
    QLabel* cam(int r, int c) const {
        return cams[r*3 + c];
    }
};

WCwindow::WCwindow()
{
    QGridLayout *layout = new QGridLayout;

    int n = 10;
    int m =10;

    for (int i = 1; i <= n*m; ++ i) {
        QLabel * const label = new QLabel(QString("CAM %1").arg(i, 2, 10, QLatin1Char('0')));
        label->setFixedSize(200, 50);
        layout->addWidget(label, (i-1) / n, (i-1) % m);
        cams << label;
    }

    QWidget * central = new QWidget();
    setCentralWidget(central);
    centralWidget()->setLayout(layout);

    setWindowTitle("Camera Window");
    setFixedSize(1000, 800);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    WCwindow win;
    win.show();
    return app.exec();
}
*/
