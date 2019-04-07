#include "mainwindow.h"
#include <QApplication>
#include "digitalwall.h"
#include "paintblock.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaintBlock block();
    printf("hello world\n");
    return 0;
    MainWindow w;
    w.show();

    return a.exec();
}
