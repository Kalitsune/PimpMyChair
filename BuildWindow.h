//
// Created by kalic on 03/01/2021.
//

#ifndef PIMPMYCHAIR_BUILDWINDOW_H
#define PIMPMYCHAIR_BUILDWINDOW_H

#include <QtWidgets>

class BuildWindow : public QWidget{

    Q_OBJECT

public slots:
    void refresh();
    void next();
    void keep();
    void sell();

public:
    BuildWindow();
    QImage compute(bool background = false);
    QImage sellCompute();
    QString getChair();
    QString getTable();
    QString getBox();
    QString getRepair();

protected:
    void initOne();

    QHBoxLayout *l1;
    QFormLayout *l2;

    QLabel *image;

    //build mode
    QComboBox *chair;
    QComboBox *table;
    QComboBox *box;
    QPushButton *next_button;

    //repair mode
    QComboBox *repair;
    QHBoxLayout *l3;
    QPushButton *keep_button;
    QPushButton *sell_button;
};


#endif //PIMPMYCHAIR_BUILDWINDOW_H
