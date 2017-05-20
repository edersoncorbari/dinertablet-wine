/**
 * @file overlaydialogbox.cpp
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

#include "overlaydialogbox.h"
#include "ui_overlaydialogbox.h"

OverlayDialogBox::OverlayDialogBox(QWidget *parent, const QString& text, bool confirm) :
    QWidget(parent), ui(new Ui::OverlayDialogBox), m_confirm(confirm)
{
    // Call ui interface.
    ui->setupUi(this);

    // Delete widget affter close.
    this->setAttribute(Qt::WA_DeleteOnClose, true);

#ifdef Q_OS_IOS
    // Not use shadow in iOS.
#else
    QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
    dse->setBlurRadius(7);
    this->setGraphicsEffect(dse);
#endif

    // Hide buttons.
    ui->pushButtonOk->hide();
    ui->pushButtonCancel->show();

    // Set text button.
    ui->pushButtonCancel->setText(QObject::tr("Ok"));

    // Set label message.
    ui->labelMsg->setStyleSheet("QLabel { background-color : transparent; "
                                "color : white; font: bold 20px; }");
    ui->labelMsg->setText(text);

    if(confirm) {
        m_confirm = true;
        if(m_confirm) {
            ui->pushButtonOk->show();
            ui->pushButtonCancel->show();

            // Set text button.
            ui->pushButtonCancel->setText(QObject::tr("Cancel"));
            ui->pushButtonOk->setText(QObject::tr("Ok"));
        }
    }

    // Signals and slots.
    QObject::connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(ui->pushButtonOk, SIGNAL(clicked()), this, SLOT(yes()));
}

OverlayDialogBox::~OverlayDialogBox()
{
    delete ui;
}

void OverlayDialogBox::closeEvent(QCloseEvent *event)
{
    Q_EMIT accepted();
    this->cancel();
    event->accept();
}

void OverlayDialogBox::cancel()
{
    Q_EMIT cancelClicked();
    this->close();
}

void OverlayDialogBox::yes()
{
    m_confirm = true;
    Q_EMIT okClicked();
    this->close();
}

bool OverlayDialogBox::ok()
{
    return m_confirm;
}
