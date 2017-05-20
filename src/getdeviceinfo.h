/**
 * @file getdeviceinfo.h
 *
 * Definitions for an diner-tablet.
 *
 * MOBILE-APP - Project DinerTablet.
 *
 * Copyright (c) 2014 BlueSalute Company Ltda.
 *
 * @author Ederson Moura - <ederson.moura@bluesalute.com.br>
 *
 * $Id: Exp$
 */

#ifndef GETDEVICEINFO_H
#define GETDEVICEINFO_H

#include <QObject>
#include <QString>

/**
 * @brief Used to collect information from the hardware device.
 */
class GetDeviceInfo : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    explicit GetDeviceInfo(QObject *parent = 0);

    /// Destructor.
    ~GetDeviceInfo();

    /**
     * @brief Print number the mac address interfaces.
     * @return Mac address found in all interfaces.
     */
    static QString printMacAddress();

    /**
     * @brief Print name the system plataform.
     * @return The name platform.
     */
    static QString printSystemPlataform();
};

#endif // GETDEVICEINFO_H
