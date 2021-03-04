#include <QApplication>
#include "Window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Pimp my chair !");
    app.setWindowIcon(QIcon(app.applicationDirPath()+"/Assets/icon.png"));
    Window window;
    window.show();
    return app.exec();
}
