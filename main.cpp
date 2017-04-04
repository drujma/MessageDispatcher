#include <QCoreApplication>

#include "CommunicationController.h"

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    CommunicationController c;

    return app.exec();
}
