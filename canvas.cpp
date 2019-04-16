#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#endif

#include "canvas.h"
CanvasImage :: CanvasImage(){
    this->_location = QPoint(0,0);
}

void CanvasImage::set_location(int x, int y){
    QPoint new_loc(x,y);
    this->_location = new_loc;
}

void CanvasImage::set_location(QPoint location){
    this->_location = location;
}

Canvas::Canvas():image_label(new QLabel),
                        scale_factor(1),
                        scroll_area(new QScrollArea){

    image_label->setBackgroundRole(QPalette::Base);
    image_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    image_label->setScaledContents(true);


    scroll_area->setBackgroundRole(QPalette::Dark);
    scroll_area->setWidget(image_label);
    scroll_area->setVisible(false);
    setCentralWidget(scroll_area);

    create_actions();

    resize(QGuiApplication::primaryScreen()->availableSize()*3/5);
    //resize(QGuiApplication::primaryScreen()->availableSize());
    //QGuiApplication::primaryScreen()->
    //resize(QGuiApplication::primaryScreen());
    //QRect rec = QApplication::desktop()->screenGeometry();
}


void Canvas::adjust_scroll_bar(QScrollBar* scroll_bar, double factor){
    scroll_bar->setValue(int(factor*scroll_bar->value() + ((factor - 1)*scroll_bar->pageStep()/2)));
}

void Canvas:: open(){

}

void Canvas::refresh(){

}

void Canvas::zoom_in(){
    scale_image(1.25);
}
void Canvas::normal_size(){
    image_label->adjustSize();
    scale_factor = 1.0;
}

void Canvas::fit_to_window(){
    bool fit_window = fit_to_window_act->isChecked();
    scroll_area->setWidgetResizable(fit_window);
    if(!fit_window)
        normal_size();
    update_actions();
}

void Canvas::zoom_out(){
    scale_image(0.75);

}

void Canvas::update_actions(){
    zoom_in_act->setEnabled(!fit_to_window_act->isChecked());
    zoom_out_act->setEnabled(!fit_to_window_act->isChecked());
    normal_size_act->setEnabled(!fit_to_window_act->isChecked());
}

void Canvas::scale_image(double factor){
    scale_factor *= factor;
    image_label->resize(scale_factor*image_label->pixmap()->size());
    adjust_scroll_bar(scroll_area->horizontalScrollBar(), factor);
    adjust_scroll_bar(scroll_area->verticalScrollBar(), factor);
    zoom_in_act->setEnabled(scale_factor < 3.0);
    zoom_out_act->setEnabled(scale_factor > 0.333);
}



void Canvas::print(){
    QPrintDialog dialog(&printer, this);
    if(dialog.exec()){
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image_label->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image_label->pixmap()->rect());
        int x_loc = 0; int y_loc = 0;
        for(int i = 0; i < _images.size(); i ++){
            QPixmap newmap;
            newmap.convertFromImage(_images.at(i));
            painter.drawPixmap(x_loc, y_loc, newmap);
            x_loc += newmap.width();
            y_loc += newmap.height();
        }
        //painter.drawPixmap(0,0, *image_label->pixmap());
    }
}

QImage Canvas::convert_file_path_to_image(QString file_path){
    QImageReader reader(file_path);
    reader.setAutoTransform(true);
    QImage image = reader.read();
    return image;
}

void Canvas::load_images() {
    QVector<QString> file_paths;
    file_paths.push_back("/home/alec/Documents/DigitalWall/image_sandbox/city_sunlight.jpg");
    file_paths.push_back("/home/alec/Documents/DigitalWall/image_sandbox/great_arch.jpg");
    file_paths.push_back("/home/alec/Documents/DigitalWall/image_sandbox/guitar.jpg");
    file_paths.push_back("/home/alec/Documents/DigitalWall/image_sandbox/skiier.jpg");

    for(int i = 0; i < file_paths.size();  i ++){
        QImageReader reader(file_paths.at(i));
        reader.setAutoTransform(true);
        const QImage new_image = reader.read();
        if(!new_image.isNull()){
            _images.push_back(new_image);
        }
    }
    set_images();
    //set_image(_images.at(0));
}

//This is from the Qt example ImageViewer -- not my code.
bool Canvas::load_file(const QString &fileName){

    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    //setImage(newImage);

    //setWindowFilePath(fileName);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
    statusBar()->showMessage(message);
    return true;

}

/*void Canvas::set_images(){
    //vector<QPixmap> maps;
    QVector<QPixmap> maps;
    int size_x = 0;
    int size_y = 0;
    QPainter painter(&printer);
    QRect rect = painter.viewport();
    QSize size = image_label->pixmap()->size();
    for(int i = 0; i < _images.size(); i ++){
        QPixmap image_map = QPixmap::fromImage(_images.at(i));
        maps.push_back(image_map);
        size_x += image_map.width();
        size_y += image_map.height();
    }
   image = _images.at(0);
   QPixmap finalMap;
   //image_label->setMinimumHeight(size_y);
   //image_label->setMinimumWidth(size_x);
   image_label->setPixmap(QPixmap::fromImage(image));
   scale_factor = 1.0;
   scroll_area->setVisible(true);
}*/
void Canvas::set_images(){
//void Canvas::set_image(const QImage &new_image){
    //vector<QPixmap> maps;
    QVector<QPixmap> maps;
    int size_x = 0;
    int size_y = 0;
    //QPixmap image_map = QPixmap::fromImage(new_image);
    QPixmap image_map(10000, 10000);
    QPainter painter(&image_map);
    //image_map.
    for(int i = 0; i < _images.size(); i ++){
        QPixmap image_map2 = QPixmap::fromImage(_images.at(i));
        QPoint image_point(size_x, size_y);
        painter.drawImage(image_point, _images.at(i));
       // maps.push_back(image_map);
        size_x += image_map2.width();
        //size_y += image_map2.height();

        //newmap.convertFromImage(_images.at(i));
        //painter.drawPixmap(x_loc, y_loc, image_map);
        //x_loc += newmap.width();
        //y_loc += newmap.height();
    }
  // QPainter painter(&printer);
  // int x_loc = 0, y_loc = 0;
  // QPixmap main_pixmap(size_x, size_y);

  // for(int i = 0; i <maps.size(); i ++){
  //     painter.drawPixmap(x_loc, y_loc, main_pixmap);
   //    x_loc += maps.at(i).width();
   //    y_loc += maps.at(i).height();
   //}

   //image = new_image;
   //image_label->setPixmap(QPixmap::fromImage(image));
   image_label->setPixmap(image_map);
   scale_factor = 1.0;
   scroll_area->setVisible(true);
   //scroll_area->setMaximumHeight(image.height());
   //scroll_area->setMaximumWidth(image.width());

}

void Canvas::show_images(){
    scroll_area->setVisible(true);
    //fit_to_window_act->setEnabled(true);
    update_actions();
    //if(!fit_to_window_act->isChecked()){
    //    image_label->adjustSize();
    //}
    QPixmap collage;
    int x = 0;
    int y = 0;
    for(int i = 0; i < _images.size(); i ++){
        x += _images.at(i).width();
        y += _images.at(i).height();
        //int x = 0;
        //int y = 0;
    //    QPointF image_point(x,y);
    //    QPainter painter(&collage);
    //    painter.drawImage(image_point, _images.at(i));

    }
    image_label->resize(image_label->pixmap()->size());
    //image_label->resize(x, y);
}

void Canvas::create_actions(){
    QMenu *file_menu = menuBar()->addMenu(tr("&File"));
    QAction *open_act = file_menu->addAction(tr("&Open..."), this, &Canvas::open);

    QMenu *view_menu = menuBar()->addMenu(tr("&View"));
    QMenu* insert_menu = menuBar()->addMenu(tr("Add Photo"));

    zoom_in_act = view_menu->addAction(tr("Zoom &In (25%)"), this, &Canvas::zoom_in);
    zoom_in_act->setShortcut(QKeySequence::ZoomIn);
    zoom_in_act->setEnabled(false);

    zoom_out_act = view_menu->addAction(tr("Zoom &Out (25%)"), this, &Canvas::zoom_out);
    zoom_out_act->setShortcut(QKeySequence::ZoomOut);
    zoom_out_act->setEnabled(false);

    normal_size_act = view_menu->addAction(tr("&Normal Size"), this, &Canvas::normal_size);
    normal_size_act->setShortcut(tr("Ctrl+S"));
    normal_size_act->setEnabled(false);

    view_menu->addSeparator();

    fit_to_window_act = view_menu->addAction(tr("&Fit to Window"), this, &Canvas::fit_to_window);
    fit_to_window_act->setEnabled(false);
    fit_to_window_act->setCheckable(true);
    fit_to_window_act->setShortcut(tr("Ctrl+F"));

    add_photo_act = insert_menu->addAction(tr("Browse For Photo"), this, &Canvas::add_photo);
    add_photo_act->setShortcut(tr("Ctrl+P"));

    //fit_to_window_act =
}

void Canvas::add_photo(){
    //QString file_name = QFileDialog::getOpenFileName(this,tr("Choose Photo To Add"), ]);
    QFileDialog photo_dialog(this, tr("Choose Photo To Add"));
    initializeImageFileDialog(photo_dialog, QFileDialog::AcceptOpen);
    QStringList file_names;
    if(photo_dialog.exec())
        file_names = photo_dialog.selectedFiles();
    QString str; QImage img;
    foreach(str, file_names){
        img = this->convert_file_path_to_image(str);
        if(!img.isNull()){
            _images.push_back(img);
        }
    }
    set_images();
    //while(photo_dialog.exec() == QDialog::Accepted){
    //photo_dialog.exec();
    //photo_dialog.
    //}

}

void Canvas::place_photo(QImage new_photo){

}

//THIS FUNCTION CAME FROM Qt ImageViewer EXAMPLE
/*https://doc.qt.io/qt-5/qtwidgets-widgets-imageviewer-imageviewer-cpp.html*/
void Canvas::initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}
