/**
 * @file xmlrpcclient.cpp
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

#include "xmlrpcclient.h"

// Initialize static variable.
QString XmlRpcClient::m_error = QString();

XmlRpcClient::XmlRpcClient(QObject *parent, QString url, QString service,
                           QString method, QVariantList parameter)
    : QObject(parent),
      m_url(url),
      m_service(service),
      m_method(method)
{
    this->m_rpc = new MaiaXmlRpcClient(QUrl("http://" + m_url + "/server/" + m_service), this);
    m_parameter.append(parameter);
    this->doClient(m_parameter);
}

XmlRpcClient::~XmlRpcClient()
{
}

void XmlRpcClient::doClient(QVariantList parameter)
{
    m_rpc->call(m_method, parameter,
               this, SLOT(serverResponse(QVariant &)),
               this, SLOT(testFault(int, const QString &)));

}

void XmlRpcClient::serverResponse(QVariant &arg)
{
    if(arg.isNull()) {
        Q_EMIT responseError();
    } else {
        m_variant = arg;
        Q_EMIT response();
    }
}

void XmlRpcClient::testFault(int error, const QString &message)
{
    XmlRpcClient::m_error = "XMLRPC Error: " + QString::number(error) + " " + message + ".";
    Q_EMIT responseError();
}

QVariant XmlRpcClient::printValues()
{
    return this->m_variant;
}

QString XmlRpcClient::errorCode()
{
    return XmlRpcClient::m_error;
}
