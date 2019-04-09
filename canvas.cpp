#include "canvas.h"

Canvas::Canvas():image_label(new QLabel), scale_factor(1){
    image_label->setBackgroundRole(QPalette::Base);
    image_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    image_label->setScaledContents(true);

    scroll_area->setBackgroundRole(QPalette::Dark);
    scroll_area->setWidget(image_label);
    scroll_area->setVisible(false);

    setCentralWidget(scroll_area);

    resize(QGuiApplication::primaryScreen()->availableSize());
    //resize(QGuiApplication::primaryScreen()->availableSize());
    //QGuiApplication::primaryScreen()->
    //resize(QGuiApplication::primaryScreen());
    //QRect rec = QApplication::desktop()->screenGeometry();
}

void Canvas:: open(){

}

void Canvas::refresh(){

}

void Canvas::update_actions(){

}

void Canvas::load_images() {
    QVector<QString> file_paths;
    file_paths.push_back("~/Documents/DigitalWall/image_sandbox/city_sunlight.jpeg");
    file_paths.push_back("~/Documents/DigitalWall/image_sandbox/great_arch.jpeg");
    file_paths.push_back("~/Documents/DigitalWall/image_sandbox/guitar.jpeg");
    file_paths.push_back("~/Documents/DigitalWall/image_sandbox/skiier.jpeg");

    for(int i = 0; i < file_paths.size();  i ++){
        QImageReader reader(file_paths.at(i));
        reader.setAutoTransform(true);
        const QImage new_image = reader.read();
        if(!new_image.isNull()){
            _images.push_back(new_image);
        }
    }
}

void Canvas::show_images(){
    scroll_area->setVisible(true);
    fit_to_window_act->setEnabled(true);
    update_actions();
    if(!fit_to_window_act->isChecked()){
        image_label->adjustSize();
    }
    image_label->resize(image_label->pixmap()->size());
}

