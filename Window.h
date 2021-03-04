//
// Created by kalic on 03/01/2021.
//

#ifndef UNTITLED_WINDOW_H
#define UNTITLED_WINDOW_H

#include <QtWidgets>

class Window : public QWidget{

    Q_OBJECT

public slots:
    void refresh();
    void save();

public:
    Window();
    QImage compute();
    QString getChair();
    QString getTable();
    QString getBox();

protected:
    QHBoxLayout *l1;
    QFormLayout *l2;

    QScrollArea *scrollArea;
    QLabel *image;

    QComboBox *chair;
    QComboBox *table;
    QComboBox *box;
    QPushButton *refresh_button;
    QPushButton *save_button;
};


#endif //UNTITLED_WINDOW_H
