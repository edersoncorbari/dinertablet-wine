/**
 * @file menuchoice.cpp
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

#include "menuchoice.h"
#include "ui_menuchoice.h"
#include "menuwidget.h"
#include "mainwidget.h"
#include "dinerapplication.h"

#include <QDesktopWidget>

MenuChoice::MenuChoice(QWidget *parent, int idorder) :
    QWidget(parent), ui(new Ui::MenuChoice), m_idorder(idorder)
{
    // Call ui interface.
    ui->setupUi(this);

    // Read settings.
    this->readSettings("DinerTabletGlobal.conf");

    // Created the direct access to class mainwidget.
    this->m_mainwidget = (MainWidget*) parent;

    // Set font label message.
    QFont fontLB("Great Vibes", 25, QFont::Bold);
    ui->label->setFont(fontLB);
    ui->label->setStyleSheet("QLabel { background-color : transparent; color : white; }");

    // Add value in order.
    if(m_idorder == 0) {
        m_idorder = 1;
    }

    ui->labelOrderNumber->setStyleSheet("QLabel { background-color : transparent; "
                                        "color : white; }");
    ui->labelOrderNumber->setText("Order: " + QString::number(m_idorder));

    // Set size buttons and text.
    ui->pushButtonFoods->setMinimumSize(QSize(100,100));
    ui->pushButtonFoods->setMaximumSize(QSize(1000,1000));
    ui->pushButtonFoods->setText(QObject::tr("Foods"));

    ui->pushButtonDesserts->setMinimumSize(QSize(100,100));
    ui->pushButtonDesserts->setMaximumSize(QSize(1000,1000));
    ui->pushButtonDesserts->setText(QObject::tr("Desserts"));

    ui->pushButtonDrinks->setMinimumSize(QSize(100,100));
    ui->pushButtonDrinks->setMaximumSize(QSize(1000,1000));
    ui->pushButtonDrinks->setText(QObject::tr("Beverages"));

    ui->pushButtonWines->setMinimumSize(QSize(100,100));
    ui->pushButtonWines->setMaximumSize(QSize(1000,1000));
    ui->pushButtonWines->setText(QObject::tr("Wines"));

    // Signals and slots.
    QObject::connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(ui->pushButtonFoods, SIGNAL(clicked()), this, SLOT(showMenuDishesFoods()));
    QObject::connect(ui->pushButtonDrinks, SIGNAL(clicked()), this, SLOT(showMenuDrinks()));
    QObject::connect(ui->pushButtonDesserts, SIGNAL(clicked()), this, SLOT(showMenuDesserts()));
    QObject::connect(ui->pushButtonWines, SIGNAL(clicked()), this, SLOT(showMenuWines()));
}

MenuChoice::~MenuChoice()
{
    delete ui;
}

void MenuChoice::cancel()
{
    this->m_mainwidget->disableObjects(false);
    this->close();
}

void MenuChoice::showMainOrder()
{
    if(!MainWidget::enableSeparateOrder()) {
        this->m_mainwidget->showObjectListWidget(true);
        this->m_mainwidget->setListWidget();
    } else {
        this->m_mainwidget->showObjectListWidget(false);
        this->m_mainwidget->setListWidget();
    }
}

void MenuChoice::showMenuDishesFoods()
{
    this->showMainOrder();

    MenuWidget *w = new MenuWidget(0);

    // Delete from memory after closing.
    w->setAttribute(Qt::WA_DeleteOnClose);

    w->setShowMenu("MenuFoods");
    w->setBackgroundImage(MainWidget::printBackgroundImage(), QPixmap());
    w->setIdOrder(m_idorder);

    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    DinerApplication::calcCenter(1024, 768, screenWidth, screenHeight);
    w->resize(DinerApplication::printCalcCenter().value("width"),
              DinerApplication::printCalcCenter().value("height"));
    w->move(DinerApplication::printCalcCenter().value("x"),
            DinerApplication::printCalcCenter().value("y"));
    w->show();
    this->cancel();
}

void MenuChoice::showMenuDrinks()
{    
    this->showMainOrder();

    MenuWidget *w = new MenuWidget(0);

    // Delete from memory after closing.
    w->setAttribute(Qt::WA_DeleteOnClose);

    w->setShowMenu("MenuDrinks");
    w->setBackgroundImage(MainWidget::printBackgroundImage(), QPixmap());
    w->setIdOrder(m_idorder);

    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    DinerApplication::calcCenter(1024, 768, screenWidth, screenHeight);
    w->resize(DinerApplication::printCalcCenter().value("width"),
              DinerApplication::printCalcCenter().value("height"));
    w->move(DinerApplication::printCalcCenter().value("x"),
            DinerApplication::printCalcCenter().value("y"));

    w->show();
    this->cancel();
}

void MenuChoice::showMenuDesserts()
{    
    this->showMainOrder();
    //qDebug() << "Desserts ";
    this->cancel();
}

void MenuChoice::showMenuWines()
{    
    this->showMainOrder();

    MenuWidget *w = new MenuWidget(0);

    // Delete from memory after closing.
    w->setAttribute(Qt::WA_DeleteOnClose);

    w->setShowMenu("MenuWine");
    w->setBackgroundImage(MainWidget::printBackgroundImage(), QPixmap());
    w->setIdOrder(m_idorder);

    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    DinerApplication::calcCenter(1024, 768, screenWidth, screenHeight);
    w->resize(DinerApplication::printCalcCenter().value("width"),
              DinerApplication::printCalcCenter().value("height"));
    w->move(DinerApplication::printCalcCenter().value("x"),
            DinerApplication::printCalcCenter().value("y"));

    w->show();
    this->cancel();
}

void MenuChoice::readSettings(const QString &conf)
{
    QSettings settings(conf, QSettings::IniFormat);

    settings.beginGroup("MenuChoice");

    // Check buttons.
    int fontSizeBtChoice = settings.value("fontSizeButtonsChoice").toInt();
    if(fontSizeBtChoice >= 10) {
        QString sizeF = ("font: bold " + QString::number(fontSizeBtChoice) + "px;");

        ui->pushButtonDesserts->setStyleSheet(sizeF);
        ui->pushButtonDrinks->setStyleSheet(sizeF);
        ui->pushButtonFoods->setStyleSheet(sizeF);
        ui->pushButtonWines->setStyleSheet(sizeF);
    }

    settings.endGroup();
}
