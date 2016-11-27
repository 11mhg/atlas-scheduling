#include "atlaswelcome.h"
#include <QApplication>
#include "botan/botan.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AtlasWelcome w;
    w.show();
    Botan::InitializationVector init;
    return a.exec();
}
