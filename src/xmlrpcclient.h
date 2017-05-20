/**
 * @file xmlrpcclient.h
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

#ifndef XMLRPCCLIENT_H
#define XMLRPCCLIENT_H

// Qt XML-RPC API
#include "maiaXmlRpcClient.h"

#include <QObject>

/**
 * @brief Makes search, update and insert the XML-RPC
 * Server information.
 */
class XmlRpcClient : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - The object.
     * @param url - The path url.
     * @param service - Name service.
     * @param method - The method.
     * @param parameter - The parameters.
     */
    explicit XmlRpcClient(QObject *parent = 0, QString url = QString(),
                          QString service = QString(),
                          QString method = QString(),
                          QVariantList parameter = QVariantList());

    /// Destructor.
    ~XmlRpcClient();

    /**
     * @brief Print values found in server rpc.
     *
     * @return The variant values.
     */
    QVariant printValues();

    /**
     * @brief Print the error code message.
     * @return Return message error code.
     */
    static QString errorCode();

public Q_SLOTS:
    /**
     * @brief The calling method in the RPC Server.
     *
     * @param parameter - The method parameter.
     */
    void doClient(QVariantList parameter = QVariantList());

Q_SIGNALS:
    /**
     * @brief Signal emitted when the RPC Server responds.
     */
    void response();

    /**
     * @brief Signal emitted when the RPC Server error responds.
     */
    void responseError();

private Q_SLOTS:
    /**
     * @brief Slot triggered after connecting with rpc.
     *
     * @param arg - Varaint values.
     */
    void serverResponse(QVariant &arg);

    /**
     * @brief If an error occurs with the rpc server.
     *
     * @param error - Number of server error.
     * @param message - Messag server error.
     */
    void testFault(int error, const QString &message);

protected:
    /// Store the URL Server RPC.
    QString m_url;

    /// Store the Service Server RPC.
    QString m_service;

    /// Store the Method Server RPC.
    QString m_method;

    /// Store the Parameter Server RPC.
    QVariantList m_parameter;

    /// Store message and erro code RPC.
    static QString m_error;

private:
    /// The xml rpc.
    MaiaXmlRpcClient *m_rpc;

    /// The store variant.
    QVariant m_variant;
};

#endif // XMLRPCCLIENT_H
