#include <QtWidgets/QApplication>
#include "MainMenu.h"
#include "Login.h"

int main(int argc, char *argv[])
{
    user.StartSubroutine();
    QApplication a(argc, argv);
    MainMenu gui;
    gui.show();
    return a.exec();
}
