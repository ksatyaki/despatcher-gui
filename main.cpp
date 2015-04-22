#include "despatcher_gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DespatcherGUI w;
    w.show();

    return a.exec();
}
