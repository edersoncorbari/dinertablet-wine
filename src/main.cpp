/**
 * @file main.cpp
 *
 * Implementations for an diner-tablet main.
 *
 * MOBILE-APP - Project DinerTablet.
 *
 * Copyright (c) 2014 BlueSalute Company Ltda.
 *
 * @author Ederson Moura - <ederson.moura@bluesalute.com.br>
 *
 * $Id: Exp$
 */

#include "dinerapplication.h"
#include "loader.h"
#include "getdeviceinfo.h"

#include <QApplication>
#include <QFontDatabase>
#include <QDir>

int main(int argc, char *argv[])
{
    // Initializes the resources.
    Q_INIT_RESOURCE(images);
    Q_INIT_RESOURCE(others);
    Q_INIT_RESOURCE(qml);

    DinerApplication app(argc, argv);

    // Set other directory app work.
    QDir::setCurrent(DinerApplication::printPathDirConfig());

    // About this app.
    app.setOrganizationName("BlueSalute Company");
    app.setOrganizationDomain("bluesalute.com.br");
    app.setApplicationName("DinerTablet");

    // Add fonts in database.
    QFontDatabase fontDB;
    fontDB.addApplicationFont(":/fonts/arizonia/Arizonia-Regular.ttf");
    fontDB.addApplicationFont(":/fonts/great-vibes/GreatVibes-Regular.ttf");

    // Loader app.
    Loader* loader = new Loader(0);
    loader->start(&app);

    //qDebug() << GetDeviceInfo::printMacAddress();
    //qDebug() << GetDeviceInfo::printSystemPlataform();

    int result = app.exec();

    delete loader;

    return result;
}
