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
#include <QSize>

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
    void set_image();
    void set_image(const QImage &new_image);
    void show_images();
    void load_images();
    void update_actions();


private slots:
    void open();
    void refresh();
    void print();
    void fit_to_window();
    void zoom_in();
    void zoom_out();
    void normal_size();
    void scale_image(double factor);

private:
    void create_actions();
    void adjust_scroll_bar(QScrollBar* scroll_bar, double factor);

    QVector<QImage> _images;
    QImage image;
    QLabel* image_label;
    QScrollArea* scroll_area;
    QPrinter printer;
    QSize image_size;
    double scale_factor;

    QAction* zoom_in_act;
    QAction* zoom_out_act;
    QAction* normal_size_act;
    QAction* fit_to_window_act;



};

#endif // CANVAS_H
