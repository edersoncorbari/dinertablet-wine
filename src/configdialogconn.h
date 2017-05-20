/**
 * @file configdialogconn.h
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

#ifndef CONFIGDIALOGCONN_H
#define CONFIGDIALOGCONN_H

#include <QtWidgets>

/**
 * @brief Page widget local configuration tablet connection.
 */
class ConfigDialogConn : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    ConfigDialogConn(QWidget *parent = 0);

    /// Destructor.
    ~ConfigDialogConn();

    /**
     * @brief Save file configuration.
     * @return Return true if save file success.
     */
    bool save();

private Q_SLOTS:
    /**
     * @brief Save the operation mode combo.
     * @param text - Text to save.
     */
    void saveOperationModeCombo(const QString &text);

    /**
     * @brief Save the number table combo.
     * @param text - Text to save.
     */
    void saveNumberTableModeCombo(const QString &text);

    /**
     * @brief Save the server protocol combo.
     * @param text - Text to save.
     */
    void saveServerProtocolCombo(const QString &text);

    /**
     * @brief Save the server port combo.
     * @param text - Text to save.
     */
    void saveServerPortCombo(const QString &text);

    /**
     * @brief Save the ip line edit.
     * @param text - Text to save.
     */
    void saveServerIpLineEdit(const QString &text);

protected:
    /**
     * @brief Reading the configuration file of the tablet.
     */
    void readSettings();

    /**
     * @brief Write the configuration file of the tablet.
     */
    void writeSettings();

private:
    /// The pointer line edit.
    QLineEdit *m_serverIpLineEdit;

    /// Store ip server or hostname.
    static QString m_saveIpLineEdit;

    /// The pointer combo protocol.
    QComboBox *m_serverProtocolCombo;

    /// The pointer combo table.
    QComboBox *m_numberTableCombo;

    /// Store protocol http or https.
    static QString m_saveServerProtocolCombo;

    /// The pointer combo mode.
    QComboBox *m_operationModeCombo;

    /// Store operation protocol.
    static QString m_saveOperationModeCombo;

    /// The pointer combo port.
    QComboBox *m_serverPortCombo;

    /// Store server port.
    static QString m_saveServerPortCombo;
};

#endif // CONFIGDIALOGCONN_H
