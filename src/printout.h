/**
 * @file printout.h
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

#ifndef PRINTOUT_H
#define PRINTOUT_H

#include <QtWidgets>

// Override.
class XmlRpcClient;

/**
 * @brief Class responsible for making printing with
 * the XML-RRC.
 */
class PrintOut : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - The object.
     * @param printN - The number print in RPC Server.
     * @param typeForm - The number form.
     */
    explicit PrintOut(QObject *parent = 0, int printN = 1, int typeForm = 1);

    /// Destructor.
    ~PrintOut();

    /**
     * @brief Singleton PrintOut class get instance.
     *
     * @return The static ListOrder.
     */
    static PrintOut* getInstance();

    /**
     * @brief Sends the file to the kitchen printer.
     *
     * @param datalocal - The list foods.
     * @param datalocalids - Quantity of food.
     */
    void sendToPrinter(QList<QVariant> datalocal, QList<QVariant> datalocaln);

    /**
     * @brief Create file html to send from after send to
     * XML RPC Server.
     *
     * @param listhtmlitems - The list items.
     * @param msgh - The message in html.
     * @param desc - The desc obs, in request.
     */
    void createHtmlToSend(QStringList listhtmlitems, const QString msgh,
                          const QString desc);

    /**
     * @brief Create file html to view.
     *
     * @param listhtmlitems - The list items.
     * @param msgh - The message in html.
     * @param desc - The desc obs, in request.
     */
    void createHtmlToView(QStringList listhtmlitems, const QString msgh);

    /**
     * @brief Print string html.
     * @return The string html.
     */
    QString printHtml();

private Q_SLOTS:
    /**
     * @brief Calls the slot method when an error occurs
     * in the RPC Server.
     */
    void xmlRpcError();

protected:
    /**
     * @brief Calls the print method in the RPC server, and
     * prints the file to the physical printer.
     */
    void callRpcPrinter();

    /// Pointer class for singleton instance.
    static PrintOut *instance;

private:
    /// The XML Rpc Client.
    XmlRpcClient* m_xmlrpc;

    /// The ID printer.
    int m_printid;

    /// The type form.
    int m_typeform;

    /// Store value html.
    QString m_html;

};

#endif // PRINTOUT_H
