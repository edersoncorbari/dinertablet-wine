/**
 * @file loading.cpp
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

#include "loading.h"
#include "ui_loading.h"

// Start static variable and objects.
Loading* Loading::instance = 0;

Loading* Loading::getInstance()
{
    if(instance == 0) {
        instance = new Loading;
    }
    return instance;
}

Loading::Loading(QWidget *parent) :
    QWidget(parent), ui(new Ui::Loading)
{
    // Call ui interface.
    ui->setupUi(this);

    // Delete from memory after closing.
    this->setAttribute(Qt::WA_DeleteOnClose);

    // Signals and slots.
    //QObject::connect(ui->pushButtonOk, SIGNAL(clicked()), this, SLOT(checkLogin()));
    //QObject::connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
}

Loading::~Loading()
{
    delete ui;
}

void Loading::showLoading()
{
    // Show form.
    this->show();

    // Load animated GIF.
    m_movie = new QMovie(":/images/loading.gif");

    // Make sure the GIF was loaded correctly.
    if(!m_movie->isValid()) {
        qDebug() << "Error...";
    }

    // Play GIF.
    ui->labelGif->setMovie(m_movie);
    m_movie->start();
}

void Loading::hideLoading()
{
    m_movie->stop();
    this->close();
}
