
#include "BuildWindow.h"
#include <iostream>

using namespace std;

BuildWindow::BuildWindow() {
    setFixedSize(QApplication::primaryScreen()->size()/2);
    initOne();
}

void BuildWindow::initOne() {

    //creating the first layout and adding a label object
    l1 = new QHBoxLayout(this);
    image = new QLabel("Nothing here yet...");
    l1->addWidget(image);

    //creating a new FormLayout
    l2 = new QFormLayout();

    //Creationg a new combobox and setting up the content
    chair = new QComboBox();
    chair->addItems(QList<QString>{"Blue 🟦","Red 🟥","Green 🟩","Yellow 🟨"});

    //Creationg a new combobox and setting up the content
    box = new QComboBox();
    box->addItems(QList<QString>{"Disabled ⬜","Blue 🟦","Red 🟥","Green 🟩","Yellow 🟨"});

    //Creationg a new combobox and setting up the content
    table = new QComboBox();
    table->addItems(QList<QString>{"Disabled ⬜","Blue 🟦","Red 🟥","Green 🟩","Yellow 🟨"});

    //Creationg a new combobox and setting up the content
    repair = new QComboBox();
    repair->addItems(QList<QString>{"Photoshop 🎇", "Welding 🕶", "Glue 🩹", "Pipes ╠", "Bamboo 🐼", "Magic 🏹", "Rope ➰", "Technologic 💻", "D.N.A. 🧬", "Steampunk ⚙"});

    //creating a new QPushButton called "Next"
    next_button = new QPushButton("Next");

    //adding items in layout 2
    l2->addRow("Chair Color:", chair);
    l2->addRow("Box Color:", box);
    l2->addRow("Table Color:", table);
    l2->addRow("", next_button);

    //adding layout2 to layout1
    l1->addLayout(l2);

    //connecting widgets with slots
    connect(chair,SIGNAL(activated(int)), this, SLOT(refresh()));
    connect(table,SIGNAL(activated(int)), this, SLOT(refresh()));
    connect(box,SIGNAL(activated(int)), this, SLOT(refresh()));
    connect(repair,SIGNAL(activated(int)), this, SLOT(refresh()));
    connect(next_button, SIGNAL(clicked()), this, SLOT(next()));
    refresh();
}

//accessors returning asset index
QString BuildWindow::getChair() {
    return QString::number(chair->currentIndex());
}
QString BuildWindow::getTable() {
    return QString::number(table->currentIndex());
}
QString BuildWindow::getBox() {
    return QString::number(box->currentIndex());
}
QString BuildWindow::getRepair() {
    return QString::number(repair->currentIndex());
}

//image refresh logic
void BuildWindow::refresh() {
    //clearing image
    image->setPixmap(QPixmap());
    image->setText("Assembling your new image...");
    image->setFont(QFont("arial", width()/30));
    image->repaint();

    //generating image
    QImage result = compute();

    //fetch to screen
    QPixmap r;
    image->setPixmap(r.fromImage(result.scaled(size())));
}


QImage BuildWindow::compute(bool background) {
    //initialisating vars
    QString assets = QApplication::applicationDirPath()+"/Assets/";
    vector<QImage> temp_imList;

    //background
    if (background != 0) {
        temp_imList.push_back(QImage(assets+"Garden-Background.png"));
    }

    //importing chair structure
    temp_imList.push_back(QImage(assets+"Struct-Down.png"));

    //importing Box combobox item
    if(getBox() != "0"){
        temp_imList.push_back(QImage(assets+"Box/"+getBox()+".png"));
    }

    //importing chair combobox item and chair structure
    temp_imList.push_back(QImage(assets+"Chair/"+getChair()+".png"));
    temp_imList.push_back(QImage(assets+"Struct-Up.png"));

    //importing Table combobox item
    if(getTable() != "0"){
        temp_imList.push_back(QImage(assets+"Table/"+getTable()+".png"));
    }

    //importing repair combobox item
    temp_imList.push_back(QImage(assets+"Repair/"+getRepair()+".png"));

    //processing
    QImage result(temp_imList[0].width(), temp_imList[0].height(), temp_imList[0].format()); // Size of final image
    QPainter painter(&result);
    //image merging
    for (int i = 0; i < temp_imList.size(); i++){
        painter.drawImage(0, 0, temp_imList[i]);
    }

    return result;
}

void BuildWindow::next() {

    //talking with the user
    QMessageBox::critical(this, "Oh oh...", "Un problème est survenu lors de la génération de votre chaise... Un bug s'est échapé et l'a partiellement détruite, vous allez devoir la réparer... ");

    //deleting widgets labels
    delete(l2->labelForField(chair));
    delete(l2->labelForField(table));
    delete(l2->labelForField(box));

    //Removing widgets from the layout
    l2->takeRow(chair);
    l2->takeRow(table);
    l2->takeRow(box);

    //hiding widgets
    chair->hide();
    table->hide();
    box->hide();

    //deleting next button
    l2->removeRow(next_button);

    //creating a new layout and setting up two buttons in it
    l3 = new QHBoxLayout();
    keep_button = new QPushButton("Keep");
    sell_button = new QPushButton("Sell");

    //connecting theres two buttons to there functions
    connect(keep_button, SIGNAL(pressed()), this, SLOT(keep()));
    connect(sell_button, SIGNAL(pressed()), this, SLOT(sell()));

    //adding there two buttons in the layout
    l3->addWidget(keep_button);
    l3->addWidget(sell_button);

    //ading repair combo box in the layout2 and importing layout3 into it
    l2->addRow("Repair Method:", repair);
    l2->addRow(l3);

}

void BuildWindow::keep() {
    QImage result = compute(true); //processing image with the garden background
    result.save(QApplication::applicationDirPath()+"/result.png"); //saving this image
    QDesktopServices::openUrl(QApplication::applicationDirPath()+"./result.png"); //opening this image with the default system application
}

void BuildWindow::sell() {
    QImage result = sellCompute(); //processing image with the website background
    result.save(QApplication::applicationDirPath()+"/result.png"); //saving this image
    QDesktopServices::openUrl(QApplication::applicationDirPath()+"./result.png"); //opening this image with the default system application

}

QImage BuildWindow::sellCompute() {
    QImage background(QApplication::applicationDirPath()+"/Assets/Sell-Background.png"); //loading background asset
    QImage image(compute(true)); //generating a chair picture with the garden background
    QImage result(background.size(), background.format()); //creating the result var
    QPainter painter(&result); //configurating QPainter object
    painter.drawImage(0, 0, background); //painting the website background on the final var
    painter.drawImage(background.width()/7, background.height()/8, image.scaled(background.size()/3.5)); //painting the resized chair picture in the final var

    return result;
}