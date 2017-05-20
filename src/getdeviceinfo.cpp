/**
 * @file getdeviceinfo.cpp
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

#include "getdeviceinfo.h"

#include <QSysInfo>
#include <QLibraryInfo>
#include <QNetworkInterface>

GetDeviceInfo::GetDeviceInfo(QObject *parent)
    : QObject(parent)
{
}

GetDeviceInfo::~GetDeviceInfo()
{
}

QString GetDeviceInfo::printMacAddress()
{
    QString text = QString();
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces()) {
        if(!interface.hardwareAddress().isEmpty()) {
            text += interface.hardwareAddress() + "\n";
        }
    }
    return text;
}

QString GetDeviceInfo::printSystemPlataform()
{
    QString text = QString();
#ifdef Q_OS_IOS
    switch(QSysInfo::macVersion()) {
    case QSysInfo::MV_IOS:
        text = "iOS";
    default:
        text = "MacOS";
    }
#endif
    return text;
}
