/**
 * @file printout.cpp
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

#include "printout.h"
#include "xmlrpcclient.h"
#include "loader.h"
#include "mainwidget.h"
#include "bill.h"

// Start static variable and objects.
PrintOut* PrintOut::instance = 0;

PrintOut* PrintOut::getInstance()
{
    if(instance == 0) {
        instance = new PrintOut;
    }
    return instance;
}

PrintOut::PrintOut(QObject *parent, int printN, int typeForm) :
    QObject(parent), m_printid(printN), m_typeform(typeForm),
    m_html(QString())
{
    if(typeForm == 1) {
        // Cash...
    } else if(typeForm == 2) {
        // Foods
    } else if(typeForm == 3) {
        // Bar...
    }
}

PrintOut::~PrintOut()
{
}

void PrintOut::sendToPrinter(QList<QVariant> datalocal, QList<QVariant> datalocaln)
{
    QStringList html;

    for(int i = 0; i < datalocal.size(); ++i) {
        QString name = QString();
        const int active = datalocal[i].toMap().value("ativo").toInt();

        if(active == 1) {

            // Check language.
            if(MainWidget::printLanguage() == "en_US") {
                name = datalocal[i].toMap().value("nome_en").toString();
            } else if(MainWidget::printLanguage() == "pt_BR") {
                name = datalocal[i].toMap().value("nome_br").toString();
            } else if(MainWidget::printLanguage() == "es") {
                name = datalocal[i].toMap().value("nome_es").toString();
            }

            int amount = datalocaln[i].toInt();

            // Set HTML.
            QString str = ("<tr>\n"
                           "<td align=\"center\">" + QString::number(amount) + "</td>\n"
                           "<td align=\"left\">" + name + "</td>\n"
                           "<td align=\"center\"></td>\n"
                           "</tr>\n");
            html.append(str);
        }
    }

    // Create a file html.
    this->createHtmlToSend(html, "PEDIDO COZINHA", QString());

    // Send html file to server RPC and printer.
    this->callRpcPrinter();
}

void PrintOut::callRpcPrinter()
{
    // Call xml rpc server (print).
    const QString param = this->printHtml();

    // Set list parameters.
    QVariantList paraml;
    paraml.append(param);
    paraml.append(QString::number(m_printid));

    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "print", "imprimindo", paraml);

    // Connect slot error.
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
}

void PrintOut::xmlRpcError()
{
    qDebug() << "Error....";
}

void PrintOut::createHtmlToSend(QStringList listhtmlitems, const QString msgh,
                                const QString desc)
{
    QString urlserverimg = "/home/www/dinerweb/assets/img/logo-res.png";

    const QString datetime = DateTime::currentDateTimeFormat();
    QString restaurantname = QString();

    // @TODO Change this!!!! Add is in configuration class.
    const QString tablename = "MESA 2 - Normal";
    QVariantList data = Loader::printRestaurantInfo();

    if(data.isEmpty()) {
        return; // Add message error.
    }

    for(int i = 0; i < data.size(); ++i) {
        restaurantname = data[i].toMap().value("nome_fantasia").toString();
    }

    QString html = ("<!DOCTYPE html>\n"
                    "<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"pt-br\" xml:lang=\"pt-br\">\n"
                    "<head>\n"
                    "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n"
                    "<style>\n"
                    "#page {\n"
                    "   position: absolute;\n"
                    "   margin-left: auto;\n"
                    "   margin-right: auto;\n"
                    "   /*height: 300px;*/\n"
                    "   width: 265px;\n"
                    "   heigth: 100%;\n"
                    "}\n"
                    "table, th, td {\n"
                    "   border-collapse: collapse;\n"
                    "}\n"
                    "th, td {\n"
                    "   padding: 5px;\n"
                    "}\n"
                    ".toLeft {\n"
                    "   float: left;\n"
                    "}\n"
                    ".toRight {\n"
                    "    float: right;\n"
                    "}\n"
                    "</style>\n"
                    "</head>\n"
                    "<body>\n"
                    "   <div id=\"page\">\n"
                    "       <p style=\"font-size:12px;font-family:verdana\">\n"
                    "       <img src=\"" + urlserverimg + "\" "
                    "       width=\"60\" height=\"60\" align=\"left\">\n"
                    "       <br>\n"
                    "       <b> " + restaurantname + "</b>\n"
                    "       </p>\n\n"
                    "       <p align=\"center\" style=\"font-size:11px;font-family:verdana\">\n"
                    "       <br>\n"
                    "       <b>" + tablename + "</b>\n"
                    "       </p>\n\n"
                    "       <div class=\"toLeft\">"
                    "       <p style=\"font-size:11px;font-family:verdana\">" + msgh + "</p></div>\n"
                    "       <div class=\"toRight\">"
                    "       <p style=\"font-size:11px;font-family:verdana\">" + datetime + "</p></div>\n\n"
                    "       <table style=\"width:100%;font-size:11px;font-family:verdana\">\n"
                    "       <tr>\n"
                    "         <th>Qtd</th>\n"
                    "         <th align=\"left\">Descrição</th>\n"
                    "       </tr>\n"
                    );

    // Search items.
    for(int i = 0; i < listhtmlitems.size(); ++i) {
        html += listhtmlitems[i];
    }

    html += "</table>\n"
            "<hr>\n";

    if(!desc.isEmpty()) {
        html += "<div>\n"
                "<p style=\"font-size:11px;font-family:verdana\">\n"
                "<b>OBS: </b>" + desc + "</b>\n"
                "</div>\n";
    }

    html += "<script>\n"
            "    var divHeight;\n"
            "    var obj = document.getElementById('page');\n\n"
            "    if(obj.offsetHeight) { \n"
            "        divHeight=obj.offsetHeight;\n"
            "        alert(divHeight);\n"
            "    } else if(obj.style.pixelHeight) {\n"
            "       divHeight=obj.style.pixelHeight;\n"
            "       alert(divHeight);\n"
            "    }\n"
            "</script>\n\n"
            "</body>\n"
            "</html>";

    // Save string html.
    this->m_html = html;
}

void PrintOut::createHtmlToView(QStringList listhtmlitems, const QString msgh)
{
    QString urlserverimg = "images-static/logo-res-color.png";

    const QString datetime = DateTime::currentDateTimeFormat();
    QString restaurantname = QString();

    // @TODO Change this!!!! Add is in configuration class.
    const QString tablename = "MESA 2 - Normal";
    QVariantList data = Loader::printRestaurantInfo();

    if(data.isEmpty()) {
        return; // Add message error.
    }

    for(int i = 0; i < data.size(); ++i) {
        restaurantname = data[i].toMap().value("nome_fantasia").toString();
    }

    QString html = ("<!DOCTYPE html>\n"
                    "<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"pt-br\" xml:lang=\"pt-br\">\n"
                    "<head>\n"
                    "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n"
                    "<style>\n"
                    "#page {\n"
                    "   position: absolute;\n"
                    "   margin-left: auto;\n"
                    "   margin-right: auto;\n"
                    "   width: 100%;\n"
                    "   heigth: 100%;\n"
                    "}\n"
                    "table, th, td {\n"
                    "   border-collapse: collapse;\n"
                    "}\n"
                    "th, td {\n"
                    "   padding: 5px;\n"
                    "}\n"
                    ".toLeft {\n"
                    "   float: left;\n"
                    "}\n"
                    ".toRight {\n"
                    "    float: right;\n"
                    "}\n"
                    "</style>\n"
                    "</head>\n"
                    "<body>\n"
                    "   <div id=\"page\">\n"
                    "       <p style=\"font-size:25px;font-family:verdana\">\n"
                    "       <img src=\"" + urlserverimg + "\" "
                    "       width=\"100\" height=\"100\" align=\"left\">\n"
                    "       <br>\n"
                    "       <b> " + restaurantname + "</b>\n"
                    "       </p>\n\n"
                    "       <p align=\"center\" style=\"font-size:18px;font-family:verdana\">\n"
                    "       <br>\n"
                    "       <b>" + tablename + "</b>\n"
                    "       </p>\n\n"
                    "       <div class=\"toLeft\">"
                    "       <p style=\"font-size:15px;font-family:verdana\">" + msgh + " " + datetime +"</p></div>\n"
                    "       <table style=\"width:100%;font-size:18px;font-family:verdana\">\n"
                    "       <tr>\n"
                    "         <th>Quantidade</th>\n"
                    "         <th align=\"center\">Descrição</th>\n"
                    "         <th align=\"center\">Total</th>\n"
                    "       </tr>\n"
                    );

    // Search items.
    for(int i = 0; i < listhtmlitems.size(); ++i) {
        html += listhtmlitems[i];
    }

    // Calculate the bill for payment.
    double total = Bill::printTotal();
    double extra = total * 1.1; // Add 10%.
    double vdiff = extra - total;

    html += "</table>\n"
            "<br><hr>\n"
            "<div class=\"toLeft\">"
            "  <p style=\"font-size:15px;font-family:verdana\">Taxa de serviço "
            "R$ " + QString::number(vdiff, 'd', 2) + "\n"
            "<div class=\"toLeft\">"
            "  <p style=\"font-size:20px;font-family:verdana\"><b>Total "
            "R$ " + QString::number(extra, 'd', 2) + "</b>\n"
            "</p></div>\n"
            "</body>\n"
            "</html>";

    // Save string html.
    this->m_html = html;
}

QString PrintOut::printHtml()
{
    return PrintOut::m_html;
}
