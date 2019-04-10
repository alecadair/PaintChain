#ifndef CANVAS_H
#define CANVAS_H

#include <QMainWindow>
#include <QImage>
#ifndef QT_NO_PRINTER
    #include <QPrinter>
#endif
#include <QLabel>
#include <QScrollArea>
#include <QGuiApplication>
#include <QApplication>
#include <QScreen>
#include <QVector>
#include <QString>
#include <QImageReader>
#include <QAction>
#include <QPrinter>

class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;

class Canvas : public QMainWindow
{
    Q_OBJECT

public:
    Canvas();
    bool load_file(const QString &);
    void set_images(const QImage images);
    void show_images();
    void load_images();
    void update_actions();


private slots:
    void open();
    void refresh();
    void print();

private:
    void create_actions();
    QVector<QImage> _images;
    QImage image;
    QLabel* image_label;
    double scale_factor;
    QScrollArea* scroll_area;
    QAction* fit_to_window_act;


};

#endif // CANVAS_H
