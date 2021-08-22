#include "cli.h"

#include <QtCore>
#include <QDebug>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("Mere Auth");
    QCoreApplication::setApplicationVersion("0.0.1");
    QCoreApplication::setSetuidAllowed(true);

    QCoreApplication app(argc, argv);

    Cli *cli = new Cli(&app);
    QObject::connect(cli, SIGNAL(done()), &app, SLOT(quit()));
    QTimer::singleShot(0, cli, SLOT(run()));

    return app.exec();
}
