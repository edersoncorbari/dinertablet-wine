/**
 * @file configdialogconn.cpp
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

#include "configdialogconn.h"
#include "dinerapplication.h"

// Start static variables and objects.
QString ConfigDialogConn::m_saveOperationModeCombo = QString();
QString ConfigDialogConn::m_saveServerProtocolCombo = QString();
QString ConfigDialogConn::m_saveServerPortCombo = QString();
QString ConfigDialogConn::m_saveIpLineEdit = QString();

ConfigDialogConn::ConfigDialogConn(QWidget *parent)
    : QWidget(parent)
{
    this->setFocusPolicy(Qt::NoFocus);

    QGroupBox *configGroup = new QGroupBox();
    configGroup->setStyleSheet("QGroupBox { "
                               "background-color : transparent; "
                               "color : white; font: bold 18px; "
                               "border: 0px; "
                               "}");

    QLabel *operationModeLabel = new QLabel(QObject::tr("Mode operation:"));
    operationModeLabel->setStyleSheet("QLabel { background-color : transparent; "
                                      "color : white; font: bold 18px; }");

    this->m_operationModeCombo = new QComboBox;
    this->m_operationModeCombo->addItem(QObject::tr("Table"));
    this->m_operationModeCombo->addItem(QObject::tr("Waiter"));

    QObject::connect(m_operationModeCombo, SIGNAL(currentIndexChanged(const QString &)),
                     this, SLOT(saveOperationModeCombo(const QString &)));

    QLabel *numberTableLabel = new QLabel(QObject::tr("Table number:"));
    numberTableLabel->setStyleSheet("QLabel { background-color : transparent; "
                                    "color : white; font: bold 18px; }");

    this->m_numberTableCombo = new QComboBox;

    unsigned int count = 21;
    for(int i = 1; 1 < count; ++i) {
        this->m_numberTableCombo->addItem(QString::number(i));
        count--;
    }

    QObject::connect(m_numberTableCombo, SIGNAL(currentIndexChanged(const QString &)),
                     this, SLOT(saveNumberTableModeCombo(const QString &)));

    QLabel *serverProtocolLabel = new QLabel(QObject::tr("Protocol:"));
    serverProtocolLabel->setStyleSheet("QLabel { background-color : transparent; "
                                       "color : white; font: bold 18px; }");

    this->m_serverProtocolCombo = new QComboBox;
    this->m_serverProtocolCombo->addItem("HTTP");
    this->m_serverProtocolCombo->addItem("HTTPS");

    QObject::connect(m_serverProtocolCombo, SIGNAL(currentIndexChanged(const QString &)),
                     this, SLOT(saveServerProtocolCombo(const QString &)));

    QLabel *serverIpLabel = new QLabel(QObject::tr("Server Name:"));
    serverIpLabel->setStyleSheet("QLabel { background-color : transparent; "
                                 "color : white; font: bold 18px; }");

    this->m_serverIpLineEdit = new QLineEdit;
    this->m_serverIpLineEdit->setStyleSheet("QLineEdit { "
                                            "border: transparent; border-radius: 8px; "
                                            "background: rgba(255,255,255,40%); "
                                            "color : black; font: bold 18px;}");

    // Disable focus.
    this->m_serverIpLineEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);

    QObject::connect(m_serverIpLineEdit, SIGNAL(textChanged(const QString &)),
                     this, SLOT(saveServerIpLineEdit(const QString &)));


    QLabel *serverPortLabel = new QLabel(QObject::tr("Port:"));
    serverPortLabel->setStyleSheet("QLabel { background-color : transparent; "
                                   "color : white; font: bold 18px; }");

    this->m_serverPortCombo = new QComboBox;
    this->m_serverPortCombo->addItem("80");
    this->m_serverPortCombo->addItem("8080");

    QObject::connect(m_serverPortCombo, SIGNAL(currentIndexChanged(const QString &)),
                     this, SLOT(saveServerPortCombo(const QString &)));

    QGridLayout *serverLayout = new QGridLayout;
    serverLayout->addWidget(operationModeLabel, 1, 0);
    serverLayout->addWidget(m_operationModeCombo, 1, 1);
    serverLayout->addWidget(numberTableLabel, 2, 0);
    serverLayout->addWidget(m_numberTableCombo, 2, 1);
    serverLayout->addWidget(serverProtocolLabel, 3, 0);
    serverLayout->addWidget(m_serverProtocolCombo, 3, 1);
    serverLayout->addWidget(serverIpLabel, 4, 0);
    serverLayout->addWidget(m_serverIpLineEdit, 4, 1);
    serverLayout->addWidget(serverPortLabel, 5, 0);
    serverLayout->addWidget(m_serverPortCombo, 5, 1);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(serverLayout);
    configGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addSpacing(10);

    // Set layout.
    this->setLayout(mainLayout);

    // Set default values in static variables.
    ConfigDialogConn::m_saveOperationModeCombo = this->m_operationModeCombo->currentText().toLower();
    ConfigDialogConn::m_saveServerProtocolCombo = this->m_serverProtocolCombo->currentText().toLower();
    ConfigDialogConn::m_saveServerPortCombo = this->m_serverPortCombo->currentText().toLower();
    ConfigDialogConn::m_saveIpLineEdit = m_serverIpLineEdit->text().toLower();

    // Read settings.
    this->readSettings();
}

ConfigDialogConn::~ConfigDialogConn()
{
}

void ConfigDialogConn::saveOperationModeCombo(const QString &text)
{
    ConfigDialogConn::m_saveOperationModeCombo = text;
}

void ConfigDialogConn::saveNumberTableModeCombo(const QString &text)
{
    qDebug() << text;
}

void ConfigDialogConn::saveServerProtocolCombo(const QString &text)
{
    ConfigDialogConn::m_saveServerProtocolCombo = text;
}

void ConfigDialogConn::saveServerPortCombo(const QString &text)
{
    ConfigDialogConn::m_saveServerPortCombo = text;
}

void ConfigDialogConn::saveServerIpLineEdit(const QString &text)
{
    ConfigDialogConn::m_saveIpLineEdit = text;
}

bool ConfigDialogConn::save()
{
    this->writeSettings();
    return true;
}

void ConfigDialogConn::writeSettings()
{
    QSettings settings("DinerTabletLocal.conf", QSettings::IniFormat);

    settings.beginGroup("ConfigDialog");
    settings.setValue("operationMode", ConfigDialogConn::m_saveOperationModeCombo.toLower());
    settings.setValue("protocolLocalServer", ConfigDialogConn::m_saveServerProtocolCombo.toLower());
    settings.setValue("portLocalServer", ConfigDialogConn::m_saveServerPortCombo.toLower());
    settings.setValue("ipLocalServer", ConfigDialogConn::m_saveIpLineEdit.toLower());
    settings.endGroup();
}

void ConfigDialogConn::readSettings()
{
    QSettings settings("DinerTabletLocal.conf", QSettings::IniFormat);

    settings.beginGroup("ConfigDialog");

    // Check mode operation.
    QString operationMode = settings.value("operationMode").toString();
    if(operationMode == QString("table")) {
         this->m_operationModeCombo->setCurrentIndex(0);
    } else if(operationMode == QString("waiter")) {
        this->m_operationModeCombo->setCurrentIndex(1);
    }

    // Check protocol.
    QString protocolLocalServer = settings.value("protocolLocalServer").toString();
    if(!protocolLocalServer.isEmpty()) {
        if(protocolLocalServer == "http") {
            this->m_serverProtocolCombo->setCurrentIndex(0);
        } else if(protocolLocalServer == "https") {
            this->m_serverProtocolCombo->setCurrentIndex(1);
        }
    }

    // Check port.
    QString portLocalServer = settings.value("portLocalServer").toString();
    if(!portLocalServer.isEmpty()) {
        if(portLocalServer == "80") {
            this->m_serverPortCombo->setCurrentIndex(0);
        } else if(portLocalServer == "8080") {
            this->m_serverPortCombo->setCurrentIndex(1);
        }
    }

    // Check ip server.
    QString ipLocalServer = settings.value("ipLocalServer").toString();
    if(!ipLocalServer.isEmpty() ) {
        this->m_serverIpLineEdit->setText(ipLocalServer);
    }

    settings.endGroup();
}
