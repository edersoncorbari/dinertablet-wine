/**
 * @file login.cpp
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

#include "login.h"
#include "ui_login.h"
#include "mainwidget.h"
#include "overlaydialogbox.h"
#include "dinerapplication.h"
#include "loader.h"

#include <QSettings>
#include <QDebug>

// Start static objects.
bool Login::m_loginCloseApp = false;

Login::Login(QWidget *parent) :
    QWidget(parent), ui(new Ui::Login), m_LoginClose(false),
    m_enableDefaultLogin(false), m_loginUserName(QString()),
    m_loginPassword(QString())
{
    // Call ui interface.
    ui->setupUi(this);

    // Created the direct access to class mainwidget.
    this->m_mainwidget = (MainWidget*) parent;

    // Set font Diner Tablet.
    QFont fontDT("Great Vibes", 35, QFont::Bold);
    ui->label->setFont(fontDT);
    ui->label->setStyleSheet("QLabel { background-color : transparent; color : white; }");

    ui->labelUserName->setStyleSheet("QLabel { background-color : transparent; color : white; "
                                     "font: bold 15px; }");
    ui->labelPassword->setStyleSheet("QLabel { background-color : transparent; color : white; "
                                     "font: bold 15px; }");

    // Set default user and set fucus.
    ui->lineEditUserName->setText("admin");
    ui->lineEditPassword->setFocus();

    // Read settings.
    this->readSettings();

    // Signals and slots.
    QObject::connect(ui->pushButtonOk, SIGNAL(clicked()), this, SLOT(checkLogin()));
    QObject::connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
}

Login::~Login()
{
    delete ui;
}

void Login::readSettings()
{
    QSettings settings("DinerTabletGlobal.conf", QSettings::IniFormat);

    settings.beginGroup("Login");

    // Check login.
    m_loginUserName = settings.value("loginUserName").toString();
    m_loginPassword = settings.value("loginPassword").toString();

    if(m_loginUserName.isEmpty() && m_loginPassword.isEmpty() ) {
        this->m_enableDefaultLogin = true;
    } else {
        this->m_enableDefaultLogin = false;
        ui->lineEditUserName->setText(m_loginUserName);
    }

    settings.endGroup();
}

void Login::checkLogin()
{
    const QString username = ui->lineEditUserName->text().toLower();
    const QString password = ui->lineEditPassword->text().toLower();

    // Check empty fields.
    if(username.isEmpty() | password.isEmpty()) {
        return;
    }

    try {

        if(this->m_enableDefaultLogin) {

            //
            // Login Hardcoding.
            //
            if(username == "admin" && password == "diner") {
                if(this->m_LoginClose) {
                    Login::m_loginCloseApp = true;
                    this->m_mainwidget->close();
                } else {
                    this->m_mainwidget->changeAppConfiguration();
                }

                this->close();
            } else {
                throw 1;
            }

        } else {

            //
            // Login read file configuration.
            //
            if(username == this->m_loginUserName && password == this->m_loginPassword) {
                if(this->m_LoginClose) {
                    Login::m_loginCloseApp = true;
                    this->m_mainwidget->close();
                } else {
                    this->m_mainwidget->changeAppConfiguration();
                }

                this->close();
            } else {
                throw 2;
            }

        }
    }

    catch(int errorLogin) {
        this->close();
        this->ui->lineEditPassword->clear();
        this->m_mainwidget->disableObjects(false);

        const QString msg = QObject::tr("UserName or Password is invalid!");

        OverlayDialogBox* overlaybox = new OverlayDialogBox(this->m_mainwidget, Loader::wordwrap(msg, 40));
        DinerApplication::calcCenter(410, 140,
                                     this->m_mainwidget->printSize().width(),
                                     this->m_mainwidget->printSize().height());

        overlaybox->resize(DinerApplication::printCalcCenter().value("width"),
                           DinerApplication::printCalcCenter().value("height"));
        overlaybox->move(DinerApplication::printCalcCenter().value("x"),
                         DinerApplication::printCalcCenter().value("y"));
        overlaybox->show();
    }
}

void Login::cancel()
{
    this->m_mainwidget->disableObjects(false);
    this->close();
}

void Login::setLoginClose(bool type)
{
    if(type) {
        this->m_LoginClose = true;
    } else {
        this->m_LoginClose = false;
    }
}

bool Login::loginCloseApp()
{
    return Login::m_loginCloseApp;
}
