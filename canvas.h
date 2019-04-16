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
#include <QFileDialog>

class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;

class CanvasImage : public QObject, public QImage{
    Q_OBJECT
    QPoint _location;
public:

    CanvasImage();
    void set_location(int x, int y);
    void set_location(QPoint location);
    QPoint get_location();
};

class Canvas : public QMainWindow{
    Q_OBJECT

public:
    Canvas();
    bool load_file(const QString &);
    void set_images(const QImage images);
    void set_images();
    void set_image(const QImage &new_image);
    void show_images();
    void load_images();
    void update_actions();
    void place_photo(QImage new_photo);
    QImage convert_file_path_to_image(QString file_path);

private slots:
    void open();
    void refresh();
    void print();
    void fit_to_window();
    void zoom_in();
    void zoom_out();
    void normal_size();
    void scale_image(double factor);
    void add_photo();


private:
    void create_actions();
    void adjust_scroll_bar(QScrollBar* scroll_bar, double factor);
    static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode);

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
    QAction* add_photo_act;



};

#endif // CANVAS_H
