/**
 * @file clientnamelist.cpp
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

#include "clientnamelist.h"
#include "ui_clientnamelist.h"
#include "mainwidget.h"

// Initialization of static variables.
QString ClientNameList::m_shortname = QString();

ClientNameList::ClientNameList(QWidget *parent) :
    QWidget(parent), ui(new Ui::ClientNameList)
{
    // Call ui interface.
    ui->setupUi(this);

    // Created the direct access to class mainwidget.
    this->m_mainwidget = (MainWidget*) parent;

    // Set font Diner Tablet.
    QFont fontDT("Great Vibes", 35, QFont::Bold);
    ui->label->setFont(fontDT);
    ui->label->setStyleSheet("QLabel { background-color : transparent; color : white; }");

    ui->labelShortName->setStyleSheet("QLabel { background-color : transparent; color : white; "
                                     "font: bold 15px; }");

    // Set focus.
    ui->lineEditShortName->setFocus();

    // Signals and slots.
    QObject::connect(ui->pushButtonOk, SIGNAL(clicked()), this, SLOT(addList()));
    QObject::connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(ui->lineEditShortName, SIGNAL(textChanged(const QString&)), this,
                     SLOT(textChanged(const QString&)));
}

ClientNameList::~ClientNameList()
{
    delete ui;
}

void ClientNameList::cancel()
{
    this->m_mainwidget->disableObjects(false);
    this->close();
}

void ClientNameList::addList()
{
    this->m_mainwidget->addItemList();
    this->cancel();
}

void ClientNameList::textChanged(const QString &text)
{
    m_shortname = text;
}

QString ClientNameList::printShortName()
{
    return m_shortname;
}
