#include <QApplication>
#include "BuildWindow.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv); //creating a Qt application
    app.setApplicationName("Pimp my chair !"); //set the window name
    app.setWindowIcon(QIcon(app.applicationDirPath()+"/Assets/icon.png")); // set the window icon
    BuildWindow window; //creating a new "window" object
    window.show(); //show the window
    return app.exec(); //execute the application
}
