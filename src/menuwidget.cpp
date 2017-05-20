/**
 * @file menuwidget.cpp
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

#include "menuwidget.h"
#include "ui_menuwidget.h"
#include "listorder.h"
#include "menufoods.h"
#include "menudrinks.h"
#include "menuwine.h"
#include "dinerapplication.h"
#include "overlaydialogbox.h"
#include "loader.h"

MenuWidget::MenuWidget(QWidget *parent, int idorder) :
    QWidget(parent), ui(new Ui::MenuWidget), m_idorder(idorder)
{
    // Call ui interface.
    ui->setupUi(this);

    // Set font label message.
    QFont fontLB("Great Vibes", 35, QFont::Bold);
    ui->label->setFont(fontLB);
    ui->label->setStyleSheet("QLabel { background-color : transparent; "
                             "color : white; }");
    ui->label->setText(QObject::tr("  Please choise an option"));

    // Menu Foods.
    m_menufoods = new MenuFoods(this);
    m_menufoods->setIdOrder(m_idorder);

    // Menu Drinks.
    m_menudrinks = new MenuDrinks(this);
    m_menudrinks->setAttribute(Qt::WA_DeleteOnClose);
    m_menudrinks->setIdOrder(m_idorder);

    // Menu Wine.
    m_menuwine = new MenuWine(this);
    m_menuwine->setAttribute(Qt::WA_DeleteOnClose);
    m_menuwine->setIdOrder(m_idorder);

    // Add widget pages.
    m_pageswidget = new QStackedWidget;
    m_pageswidget->addWidget(m_menufoods);
    m_pageswidget->addWidget(m_menudrinks);
    m_pageswidget->addWidget(m_menuwine);

    // Set style.
    m_pageswidget->setStyleSheet("QTabWidget QStackedWidget { background: none };");

    // Add stacked widget in grid.
    ui->gridLayout_2->addWidget(m_pageswidget);

    // Signals and slots.
    QObject::connect(ui->pushButtonNext, SIGNAL(clicked()), this, SLOT(changeNextPage()));
    QObject::connect(ui->pushButtonBack, SIGNAL(clicked()), this, SLOT(changeBackPage()));
    QObject::connect(ui->pushButtonViewOrder, SIGNAL(clicked()), this, SLOT(showMyOrder()));
}

MenuWidget::~MenuWidget()
{
    delete ui;
}

void MenuWidget::setIdOrder(int idorder)
{
    this->m_idorder = idorder;
}

int MenuWidget::printIdCurrentOrder()
{
    return this->m_idorder;
}

void MenuWidget::changeNextPage()
{
    int nextPage = m_pageswidget->currentIndex() + 1;

    if(nextPage >= m_pageswidget->count()) {
        nextPage = 0;
    }

    if(nextPage == 0) {
        ui->pushButtonBack->setText(QObject::tr("Back"));
        ui->pushButtonNext->setText(QObject::tr("Next Beverages"));
    } else if(nextPage == 1) {
        ui->pushButtonBack->setText(QObject::tr("Back Foods"));
        ui->pushButtonNext->setText(QObject::tr("Next Wines"));
    } else if(nextPage == 2) {
        ui->pushButtonBack->setText(QObject::tr("Back Beverages"));
        ui->pushButtonNext->setText(QObject::tr("Next Foods"));
    }

    m_pageswidget->setCurrentIndex(nextPage);
}

void MenuWidget::changeBackPage()
{
    int backPage = m_pageswidget->currentIndex() - 1;

    if(backPage >= m_pageswidget->count()) {
        backPage = 0;
    }

    if(backPage == 0) {
        ui->pushButtonBack->setText(QObject::tr("Back"));
        ui->pushButtonNext->setText(QObject::tr("Next Beverages"));
    } else if(backPage == 1) {
        ui->pushButtonBack->setText(QObject::tr("Back Foods"));
        ui->pushButtonNext->setText(QObject::tr("Next Wines"));
    } else if(backPage == 2) {
        ui->pushButtonBack->setText(QObject::tr("Back Beverages"));
        ui->pushButtonNext->setText(QObject::tr("Next Foods"));
    }

    if(backPage == -1) {
        this->close();
    }

    m_pageswidget->setCurrentIndex(backPage);
}

void MenuWidget::showMyOrder()
{
    ListOrder *w = new ListOrder(0);

    // Delete from memory after closing.
    w->setAttribute(Qt::WA_DeleteOnClose);

    // Show all orders.
    w->showAll();

    // Check is list is empty.
    if(w->checkOrderIsEmpty() == 0) {
        const QString msg = QObject::tr("You didn't even no request. Please add an item.");
        OverlayDialogBox* overlaybox = new OverlayDialogBox(this, Loader::wordwrap(msg, 47));

        DinerApplication::calcCenter(515, 140, this->width(), this->height());
        overlaybox->resize(DinerApplication::printCalcCenter().value("width"),
                           DinerApplication::printCalcCenter().value("height"));
        overlaybox->move(DinerApplication::printCalcCenter().value("x"),
                         DinerApplication::printCalcCenter().value("y"));
        overlaybox->show();
        return;
    }

    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    DinerApplication::calcCenter(500, 500, screenWidth, screenHeight);
    w->resize(DinerApplication::printCalcCenter().value("width"),
                   DinerApplication::printCalcCenter().value("height"));
    w->move(DinerApplication::printCalcCenter().value("x"),
                 DinerApplication::printCalcCenter().value("y"));
    w->show();

    // Signals and slots.
    QObject::connect(w, SIGNAL(addMoreClicked()), this, SLOT(closeForms()));
    QObject::connect(w, SIGNAL(afterRequestOrder()), this, SLOT(showMessageAfterRequestOrder()));

    this->disableObjects(true);
}

void MenuWidget::showMessageAfterRequestOrder()
{
    this->disableObjects(true);

    // Print new message.
    const QString msg = QObject::tr("Your order has been sent! And being prepared. "
                                    "Any questions call the waiter. Thank you.");

    OverlayDialogBox* overlaybox = new OverlayDialogBox(this, Loader::wordwrap(msg, 47));

    DinerApplication::calcCenter(515, 180, this->width(), this->height());
    overlaybox->resize(DinerApplication::printCalcCenter().value("width"),
                       DinerApplication::printCalcCenter().value("height"));
    overlaybox->move(DinerApplication::printCalcCenter().value("x"),
                     DinerApplication::printCalcCenter().value("y"));
    overlaybox->show();

    QObject::connect(overlaybox, SIGNAL(accepted()), this, SLOT(closeAllForms()));
}

void MenuWidget::closeAllForms()
{
    this->close();
}

void MenuWidget::closeForms()
{
    this->disableObjects(false);
}

void MenuWidget::setShowMenu(const QString objectName)
{
    if(m_menufoods->objectName() == objectName) {
        m_pageswidget->setCurrentIndex(0);
    } else if(m_menudrinks->objectName() == objectName) {
        m_pageswidget->setCurrentIndex(1);
    } else if(m_menuwine->objectName() == objectName) {
        m_pageswidget->setCurrentIndex(2);
    }

}

void MenuWidget::disableObjects(bool disable)
{
    //this->m_pageswidget->setDisabled(true);
    //this->m_menudrinks->setDisabled(true);

    if(disable) {
        this->m_pageswidget->setDisabled(true);
        this->ui->pushButtonBack->setDisabled(true);
        this->ui->pushButtonNext->setDisabled(true);
        this->ui->pushButtonViewOrder->setDisabled(true);
    } else {
        this->m_pageswidget->setDisabled(false);
        this->ui->pushButtonBack->setDisabled(false);
        this->ui->pushButtonNext->setDisabled(false);
        this->ui->pushButtonViewOrder->setDisabled(false);
    }
}

void MenuWidget::setBackgroundImage(const QString &img, const QPixmap &pix)
{
    // Using QPalette you can set background image as follows.
    QPalette p = palette();

    // Load image to QPixmap, Give full path of image.
    QPixmap pixmap1;
    if(!img.isEmpty()) {
        pixmap1 = img;
    } else {
        pixmap1 = pix;
    }

    // Resize image if it is larger than screen size.
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect rect = desktopWidget->availableGeometry();

    QSize size(rect.width(), rect.height());

    // Resize as per your requirement..
    QPixmap pixmap(pixmap1.scaled(size));

    p.setBrush(QPalette::Background,  pixmap);
    this->setPalette(p);
}
