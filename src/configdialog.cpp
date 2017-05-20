/**
 * @file configdialog.cpp
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

#include "configdialog.h"
#include "configdialogconn.h"
#include "mainwidget.h"
#include "overlaydialogbox.h"
#include "dinerapplication.h"
#include "loader.h"

#include <QtWidgets>

ConfigDialog::ConfigDialog(QWidget *parent)
    : QWidget(parent)
{
    m_contentswidget = new QListWidget;
    m_contentswidget->setViewMode(QListView::IconMode);
    m_contentswidget->setIconSize(QSize(96, 84));
    m_contentswidget->setMovement(QListView::Static);
    m_contentswidget->setMaximumWidth(150);
    m_contentswidget->setSpacing(12);

    // Set no fucus border listwidget.
    m_contentswidget->setFocusPolicy(Qt::NoFocus);

    // Created the direct access to class ConfigDialogConn.
    this->m_configdialogconn = (ConfigDialogConn*) parent;

    // Created the direct access to class mainwidget.
    this->m_mainwidget = (MainWidget*) parent;

    m_pageswidget = new QStackedWidget;
    m_pageswidget->addWidget(new ConfigDialogConn);

    m_cancelbt = new QPushButton(QObject::tr("Cancel"));
    m_savebt = new QPushButton(QObject::tr("Save"));

    createIcons();
    m_contentswidget->setCurrentRow(0);

    // Signals and slots.
    QObject::connect(m_cancelbt, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(m_savebt, SIGNAL(clicked()), this, SLOT(saveMsg()));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(m_contentswidget);
    horizontalLayout->addWidget(m_pageswidget, 1);

    QSpacerItem *horizontalSpacer = new QSpacerItem(25,0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(m_savebt);
    buttonsLayout->addItem(horizontalSpacer);
    buttonsLayout->addWidget(m_cancelbt);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    // Set window title.
    this->setWindowTitle(QObject::tr("Diner Tablet - Configuration"));

    this->setStyleSheet("QFrame {"
                        "    border-radius: 40px; "
                        "    background: rgba(0,0,0,40%); "
                        "}");
}

ConfigDialog::~ConfigDialog()
{
}

void ConfigDialog::cancel()
{
    this->m_mainwidget->disableObjects(false);
    this->close();
}

void ConfigDialog::saveMsg()
{
    // Hide objects.
    m_pageswidget->hide();
    m_contentswidget->hide();
    m_savebt->hide();
    m_cancelbt->hide();

    const QString msg = QObject::tr("Do you really want to save the configurations? "
                                    "The application restarts.");

    OverlayDialogBox* overlaybox = new OverlayDialogBox(this->m_mainwidget,
                                                        Loader::wordwrap(msg, 47), true);

    DinerApplication::calcCenter(505, 180,
                                 this->m_mainwidget->printSize().width(),
                                 this->m_mainwidget->printSize().height());
    overlaybox->resize(DinerApplication::printCalcCenter().value("width"),
                       DinerApplication::printCalcCenter().value("height"));
    overlaybox->move(DinerApplication::printCalcCenter().value("x"),
                     DinerApplication::printCalcCenter().value("y"));
    overlaybox->show();

    // Signals and slots.
    QObject::connect(overlaybox, SIGNAL(okClicked()), this, SLOT(save()));
    QObject::connect(overlaybox, SIGNAL(cancelClicked()), this, SLOT(cancelMsg()));
}

void ConfigDialog::save()
{
    this->m_configdialogconn->save();
    this->m_mainwidget->disableObjects(false);
    this->close();
    qApp->quit(); // Force close app.
}

void ConfigDialog::cancelMsg()
{
    // Show objects.
    m_pageswidget->show();
    m_contentswidget->show();
    m_savebt->show();
    m_cancelbt->show();

    this->repaint();
}

void ConfigDialog::createIcons()
{
    QListWidgetItem *configButton = new QListWidgetItem(m_contentswidget);
    configButton->setIcon(QIcon(":/images/config.png"));
    configButton->setText(QObject::tr("Configuration"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QObject::connect(m_contentswidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(!current) {
        current = previous;
    }

    this->m_pageswidget->setCurrentIndex(m_contentswidget->row(current));
}
