
#include "Window.h"


using namespace std;

Window::Window() {
    resize(QApplication::primaryScreen()->size()/4);

    l1 = new QHBoxLayout(this);
    scrollArea = new QScrollArea();
    image = new QLabel("Nothing here yet...", scrollArea);
    l1->addWidget(scrollArea);

    l2 = new QFormLayout();

    chair = new QComboBox();
    chair->addItem("Blue");
    chair->addItem("Red");
    chair->addItem("Green");
    chair->addItem("Yellow");

    box = new QComboBox();
    box->addItem("Disabled");
    box->addItem("Blue");
    box->addItem("Red");
    box->addItem("Green");
    box->addItem("Yellow");

    table = new QComboBox();
    table->addItem("Disabled");
    table->addItem("Blue");
    table->addItem("Red");
    table->addItem("Green");
    table->addItem("Yellow");

    refresh_button = new QPushButton("Resfresh");
    save_button = new QPushButton("Save");

    l2->addRow("Chair Color:", chair);
    l2->addRow("Box Color:", box);
    l2->addRow("Table Color:", table);
    l2->addRow(refresh_button);
    l2->addRow(save_button);


    l1->addLayout(l2);

    //connecting widgets
    connect(chair,SIGNAL(activated(int)), this, SLOT(refresh()));
    connect(table,SIGNAL(activated(int)), this, SLOT(refresh()));
    connect(box,SIGNAL(activated(int)), this, SLOT(refresh()));
    connect(refresh_button, SIGNAL(pressed()), this, SLOT(refresh()));
    connect(save_button, SIGNAL(pressed()),this, SLOT(save()));

    refresh();
}

//acessers
QString Window::getChair() {
    return chair->currentText();
}
QString Window::getTable() {
    return table->currentText();
}
QString Window::getBox() {
    return box->currentText();
}

void Window::refresh() {
    QImage result = compute();
    //fetch to screen
    QPixmap r;
    image->setPixmap(r.fromImage(result.scaled(width(),height())));
}


QImage Window::compute() {
    QString assets = QApplication::applicationDirPath()+"/Assets/";
    vector<QImage> temp_imList;

    //importing background
    temp_imList.push_back(QImage(assets+"Background.png"));
    //importing Box
    if(getBox() != "Disabled"){
        temp_imList.push_back(QImage(assets+"Box/"+getBox()+".png"));
        temp_imList.push_back(QImage(assets+"Box/Lines.png"));
    }
    //importing chair and chair structure
    temp_imList.push_back(QImage(assets+"Chair/"+getChair()+".png"));
    temp_imList.push_back(QImage(assets+"Chair/Lines.png"));
    temp_imList.push_back(QImage(assets+"Struct-Up.png"));
    //importing Table
    if(getTable() != "Disabled"){
        temp_imList.push_back(QImage(assets+"Table/"+getTable()+".png"));
        temp_imList.push_back(QImage(assets+"Table/Lines.png"));
    }

    //processing
    QImage result(temp_imList[0].width(), temp_imList[0].height(), temp_imList[0].format()); // Size of final image
    QPainter painter(&result);
    //image mergeing
    for (int i = 0; i < temp_imList.size(); i++){
        painter.drawImage(0, 0, temp_imList[i]);
    }
    return result;
}

void Window::save() {
    QImage result = compute();
    QString path = QFileDialog::getSaveFileName(this, "Please save your file", QApplication::applicationDirPath(),"*.png");
    result.save(path);
}
