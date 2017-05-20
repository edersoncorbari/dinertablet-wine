/**
 * @file dinerapplication.cpp
 *
 * Implementations for an diner-tablet.
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

#include <QDir>
#include <QStandardPaths>

#include <iostream>

// Start static objects.
QMap<QString, int> DinerApplication::m_mapcenter = QMap<QString, int>();

DinerApplication::DinerApplication(int argc, char* argv[]) :
    QApplication(argc,argv)
{
}

DinerApplication::~DinerApplication()
{
}

void DinerApplication::setUserIdle(int time)
{
    m_timer.setInterval(time);
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(idle()));
    m_timer.start();
}

void DinerApplication::idle()
{
    m_timer.stop();
    emit idleCalled();
}

bool DinerApplication::notify(QObject *receiver, QEvent *event)
{
    if(event->type() == QEvent::MouseMove || event->type() == QEvent::KeyPress) {
        m_timer.stop();
        m_timer.start();
    }
    return QApplication::notify(receiver, event);
}

void DinerApplication::calcCenter(int width, int height, int screenWidth, int screenHeight)
{
    unsigned int x = 0;
    unsigned int y = 0;

    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;

    // Clear values.
    DinerApplication::m_mapcenter.clear();

    // Set values.
    DinerApplication::m_mapcenter["width"] = width;
    DinerApplication::m_mapcenter["height"] = height;
    DinerApplication::m_mapcenter["x"] = x;
    DinerApplication::m_mapcenter["y"] = y;
}

QMap<QString, int> DinerApplication::printCalcCenter()
{
    return DinerApplication::m_mapcenter;
}

QString DinerApplication::printPathDirIos7()
{
    const QString curdir = QDir::currentPath();

    int found = curdir.lastIndexOf("/");

    QString leftside = curdir.left(found+1);
    leftside += "Documents";

    return leftside;
}

QString DinerApplication::printPathDirIos8()
{
    QString path = QStandardPaths::standardLocations(QStandardPaths::DataLocation).value(0);
    QDir dir(path);

    if(!dir.exists()) {
        dir.mkpath(path);
    }

    if(!path.isEmpty() && !path.endsWith("/")) {
        path += "/";
    }

    return path;
}

QString DinerApplication::printPathDirConfig()
{
    static QString path = QString();

#ifdef Q_OS_IOS
    switch(QSysInfo::macVersion()) {
    case QSysInfo::MV_IOS_7_0:
        path = DinerApplication::printPathDirIos7();
        break;
    case QSysInfo::MV_IOS_7_1:
        path = DinerApplication::printPathDirIos7();
        break;
    case QSysInfo::MV_IOS_8_0:
        path = DinerApplication::printPathDirIos8();
        break;
    default:
        path = DinerApplication::printPathDirIos8();
    }
#else
    path = QCoreApplication::applicationDirPath();
#endif

    return path;
}

void DinerApplication::printListFiles()
{
    QDir dir;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    std::cout << "     Bytes Filename" << std::endl;
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                                .arg(fileInfo.fileName()));
        std::cout << std::endl;
    }
}
