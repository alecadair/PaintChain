#include "mainwindow.h"
#include <QApplication>
#include "digitalwall.h"
//#include "paintblock.h"
#include "paintchain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //PaintBlock block();
    PaintChain paint_chain;
    PixelGrid initial_grid;
    cout << "MINING BLOCK 1" << endl;
    paint_chain.add_block(PaintBlock(1, initial_grid, "0,0"));

    cout << "MINING BLOCK 2" << endl;
    paint_chain.add_block(PaintBlock(2, initial_grid, "1,0"));

    cout << "MINING BLOCK 3" << endl;
    paint_chain.add_block(PaintBlock(3, initial_grid, "2,0"));

    return 0;
    MainWindow w;
    w.show();

    return a.exec();
}
