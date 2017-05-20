/**
 * @file mainwidget.cpp
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

#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "menufoods.h"
#include "overlaydialogbox.h"
#include "wigglytext.h"
#include "menuwidget.h"
#include "menuchoice.h"
#include "clientnamelist.h"
#include "loader.h"
#include "dinerapplication.h"
#include "advertisingnews.h"
#include "configdialog.h"
#include "login.h"
#include "bill.h"

// Initialization of static variables.
int MainWidget::m_numberorder = 0;
QString MainWidget::m_backgroundimage = QString();
QString MainWidget::m_language = QString();
bool MainWidget::m_enableseparateorders = false;
MainWidget* MainWidget::instance = 0;

MainWidget* MainWidget::getInstance()
{
    if(instance == 0){
        instance = new MainWidget;
    }
    return instance;
}

MainWidget::MainWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWidget)
{
    // Call ui interface.
    ui->setupUi(this);

    // Create instance translator.
    this->m_translator = new QTranslator(this);

    // Initial verification of the app settings.
    this->startCheck();

    // Create instance wiggly text.
    WigglyText *wigglyText = new WigglyText(this);

    // Set wiggly text.
    wigglyText->setText("Menu");
    ui->gridLayout_4->addWidget(wigglyText);

    // Set font Diner Tablet.
    QFont fontDT("Great Vibes", 45, QFont::Bold);
    ui->labelDinerTablet->setFont(fontDT);
    ui->labelDinerTablet->setStyleSheet("QLabel { background-color : transparent; "
                                        "color : white; }");

    // Set font Name Customer.
    QFont fontNC("Arizonia", 35, QFont::Bold);
    ui->labelNameCustomer->setFont(fontNC);
    ui->labelNameCustomer->setStyleSheet("QLabel { background-color : transparent; "
                                         "color : white; }");

    // Set font Text Menu.
    QFont fontTM("Great Vibes", 25, QFont::Bold);
    ui->labelTextMenu->setFont(fontTM);
    ui->labelTextMenu->setStyleSheet("QLabel { background-color : transparent; "
                                     "color : white; }");

    // Set font Text Order.
    QFont fontTO("Great Vibes", 25, QFont::Bold);
    ui->labelTextOrder->setFont(fontTO);
    ui->labelTextOrder->setStyleSheet("QLabel { background-color : transparent; "
                                      "color : white; }");

    // Set mode listWidget.
    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setIconSize(QSize(90, 90));
    ui->listWidget->setMovement(QListView::Static);
    ui->listWidget->setMaximumWidth(384); // 128+128+128!
    ui->listWidget->setSpacing(12);
    ui->listWidget->setStyleSheet("QListWidget { background-color : transparent; }");

    // Set no fucus border listwidget.
    ui->listWidget->setFocusPolicy(Qt::NoFocus);

    // Hide frames widgets.
    ui->frameMenu->hide();
    ui->frameMenuButtons->hide();
    ui->frameOrder->hide();
    ui->frameLangButtons->hide();

    // Start animation widgets.
    this->animatewidgets();

    // Signals and slots.
    QObject::connect(ui->pushButtonMenu, SIGNAL(clicked()), this, SLOT(menu()));
    QObject::connect(ui->pushButtonAddList, SIGNAL(clicked()), this, SLOT(setClientNameList()));
    QObject::connect(ui->pushButtonRemoveList, SIGNAL(clicked()), this, SLOT(removeItemList()));
    QObject::connect(ui->pushButtonPTBR, SIGNAL(clicked()), this, SLOT(changeLanguageToPortugueseBR()));
    QObject::connect(ui->pushButtonUS, SIGNAL(clicked()), this, SLOT(changeLanguageToEnglishUS()));
    QObject::connect(ui->pushButtonES, SIGNAL(clicked()), this, SLOT(changeLanguageToSpanish()));
    QObject::connect(ui->pushButtonStatusTablet, SIGNAL(clicked()), this, SLOT(checkLogin()));
    QObject::connect(ui->pushButtonBill, SIGNAL(clicked()), this, SLOT(checkMyBill()));

    QObject::connect(ui->pushButtonChefSuggestion, SIGNAL(clicked()), this, SLOT(printMsgNotImplemented()));
    QObject::connect(ui->pushButtonNews, SIGNAL(clicked()), this, SLOT(printMsgNotImplemented()));
    QObject::connect(ui->pushButtonInternet, SIGNAL(clicked()), this, SLOT(printMsgNotImplemented()));
    QObject::connect(ui->pushButtonPhotos, SIGNAL(clicked()), this, SLOT(printMsgNotImplemented()));
    QObject::connect(ui->pushButtonGames, SIGNAL(clicked()), this, SLOT(printMsgNotImplemented()));
    QObject::connect(ui->pushButtonTaxi, SIGNAL(clicked()), this, SLOT(printMsgNotImplemented()));
    QObject::connect(ui->pushButtonValet, SIGNAL(clicked()), this, SLOT(printMsgNotImplemented()));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::test()
{
}

void MainWidget::checkMyBill()
{
    Bill *w = new Bill(0);

    // Delete from memory after closing.
    w->setAttribute(Qt::WA_DeleteOnClose);

    //w->setShowMenu("MenuFoods");
    w->setBackgroundImage(MainWidget::printBackgroundImage(), QPixmap());
    //w->setIdOrder(m_idorder);

    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    DinerApplication::calcCenter(1024, 768, screenWidth, screenHeight);
    w->resize(DinerApplication::printCalcCenter().value("width"),
              DinerApplication::printCalcCenter().value("height"));
    w->move(DinerApplication::printCalcCenter().value("x"),
            DinerApplication::printCalcCenter().value("y"));
    w->show();
}

void MainWidget::setListWidget()
{
    if(ui->listWidget->currentRow() == -1) {
        //qDebug() << "This is order = 1";
        MainWidget::m_numberorder = 1;
        this->addItemListView(1, "N1");
    }

    if(ui->listWidget->currentRow() == 0) {
        //qDebug() << "This is order = 1";
        MainWidget::m_numberorder = 1;
    }

    if(ui->listWidget->currentRow() == 1) {
        //qDebug() << "This is order = 2";
        MainWidget::m_numberorder = 2;
    }

    if(ui->listWidget->currentRow() == 2) {
        //qDebug() << "This is order = 3";
        MainWidget::m_numberorder = 3;
    }

    if(ui->listWidget->currentRow() == 3) {
        //qDebug() << "This is order = 4";
        MainWidget::m_numberorder = 4;
    }

    if(ui->listWidget->currentRow() == 4) {
        //qDebug() << "This is order = 5";
        MainWidget::m_numberorder = 5;
    }

    if(ui->listWidget->currentRow() == 5) {
        //qDebug() << "This is order = 6";
        MainWidget::m_numberorder = 6;
    }

    if(ui->listWidget->currentRow() == 6) {
        //qDebug() << "This is order = 7";
        MainWidget::m_numberorder = 7;
    }

    if(ui->listWidget->currentRow() == 7) {
        //qDebug() << "This is order = 8";
        MainWidget::m_numberorder = 8;
    }

    if(ui->listWidget->currentRow() == 8) {
        //qDebug() << "This is order = 9";
        MainWidget::m_numberorder = 9;
    }

    if(ui->listWidget->currentRow() == 9) {
        //qDebug() << "This is order = 10";
        MainWidget::m_numberorder = 10;
    }
}


int MainWidget::printNumberOrder()
{
    return MainWidget::m_numberorder;
}

bool MainWidget::enableSeparateOrder()
{
    return MainWidget::m_enableseparateorders;
}

void MainWidget::menu()
{
    if(!MainWidget::enableSeparateOrder()) {
        if(MainWidget::m_numberorder >= 1) {
            this->showObjectListWidget(true);
            this->setListWidget();
        }
    }

    MenuChoice *w = new MenuChoice(this, MainWidget::m_numberorder);

    // Delete from memory after closing.
    w->setAttribute(Qt::WA_DeleteOnClose);

    DinerApplication::calcCenter(290, 300, this->width(), this->height());
    w->resize(DinerApplication::printCalcCenter().value("width"),
                   DinerApplication::printCalcCenter().value("height"));
    w->move(DinerApplication::printCalcCenter().value("x"),
                 DinerApplication::printCalcCenter().value("y"));
    w->show();
    this->disableObjects(true);
}

void MainWidget::setClientNameList()
{
    ClientNameList *client = new ClientNameList(this);

    // Delete from memory after closing.
    client->setAttribute(Qt::WA_DeleteOnClose);

#ifdef Q_OS_IOS
    client->resize(300,250);
    client->move(390,390);
#else
    DinerApplication::calcCenter(250, 180, this->width(), this->height());
    client->resize(DinerApplication::printCalcCenter().value("width"),
                         DinerApplication::printCalcCenter().value("height"));
    client->move(DinerApplication::printCalcCenter().value("x"),
                       DinerApplication::printCalcCenter().value("y"));
#endif
    client->show();
    this->disableObjects(true);
}

void MainWidget::disableObjects(bool disable)
{
    if(disable) {
        this->ui->frameMenuButtons->setDisabled(true);
        this->ui->frameMenu->setDisabled(true);
        this->ui->frameLangButtons->setDisabled(true);
        this->ui->frameOrder->setDisabled(true);
    } else {
        this->ui->frameMenuButtons->setDisabled(false);
        this->ui->frameMenu->setDisabled(false);
        this->ui->frameLangButtons->setDisabled(false);
        this->ui->frameOrder->setDisabled(false);
    }
}

void MainWidget::addItemList()
{
    // Increment variable.
    ++MainWidget::m_numberorder;

    QString getShortName = ClientNameList::printShortName();

    if(getShortName.isEmpty()) {
        getShortName = "N" + QString::number(m_numberorder);
    }

    if(MainWidget::m_numberorder <= 10) {
        this->addItemListView(MainWidget::m_numberorder, getShortName);
    } else {
        //qDebug() << "Limit is 10...";
    }
}

void MainWidget::removeItemList()
{
    // Decrement variable.
    --MainWidget::m_numberorder;
    ui->listWidget->takeItem(ui->listWidget->row(ui->listWidget->currentItem()));
}

void MainWidget::itemClicked(QListWidgetItem *item)
{
    ui->listWidget->setCurrentItem(item);
    ui->listWidget->row(item);
}

void MainWidget::itemChanged(QListWidgetItem *item)
{
    item->setSelected(true);
    ui->listWidget->setCurrentItem(item);
    ui->listWidget->row(item);
}

void MainWidget::showObjectListWidget(bool show)
{
    if(show) {
        this->ui->frameOrder->show();
    } else {
        this->ui->frameOrder->hide();
    }

    QObject::connect(ui->listWidget,
            SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemClicked(QListWidgetItem*)));
    QObject::connect(ui->listWidget,
            SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(itemChanged(QListWidgetItem*)));
}

void MainWidget::addItemListView(int identify, const QString texticon)
{
    if(!ui->listWidget->currentItem()) {
    }

    QImage image(":/images/notes.png");

    // Tell the painter to draw on the QImage.
    QPainter* painter = new QPainter(&image);
    painter->setPen(Qt::white);
    painter->setFont(QFont("Great Vibes", 28, QFont::Bold));
    //painter->rotate(-15);
    painter->drawText(image.rect(), Qt::AlignAbsolute, " " + texticon);

    QIcon icon = QPixmap::fromImage(image);

    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setIcon(QIcon(icon));
    item->setWhatsThis(QString::number(identify));

    int row = ui->listWidget->row(ui->listWidget->currentItem());
    ui->listWidget->insertItem(row, item);
}

void MainWidget::closeEvent(QCloseEvent *event)
{
#ifdef DINER_APP_DEBUG
    Loader::removeDownloadFiles();
    event->accept();
#elif DINER_APP_RELEASE
    if(Login::loginCloseApp()) {
        Loader::removeDownloadFiles();
        event->accept();
    } else {
        checkLoginClose();
        event->ignore();
    }
#endif
}

void MainWidget::callAdvertisingNews()
{
    this->m_advertisingnews = new AdvertisingNews();

    // Delete from memory after closing.
    m_advertisingnews->setAttribute(Qt::WA_DeleteOnClose);

    QDesktopWidget *desktop = QApplication::desktop();

    DinerApplication::calcCenter(1024, 768, desktop->width(), desktop->height());
    m_advertisingnews->resize(DinerApplication::printCalcCenter().value("width"),
                   DinerApplication::printCalcCenter().value("height"));
    m_advertisingnews->move(DinerApplication::printCalcCenter().value("x"),
                 DinerApplication::printCalcCenter().value("y"));

    // Signal and slot.
    QObject::connect(m_advertisingnews, SIGNAL(clicked()), this, SLOT(closeAdvertisingNews()));

    m_advertisingnews->show();
    this->m_advertisingnews->activateWindow();
}

void MainWidget::closeAdvertisingNews()
{
    this->m_advertisingnews->close();
}

void MainWidget::resizeEvent(QResizeEvent *event)
{
    // Size is used in overlaydialogbox.
    this->m_size = event->size();
    event->accept();
}

void MainWidget::checkLoginClose()
{
    this->m_login = new Login(this);

    // Delete from memory after closing.
    this->m_login->setAttribute(Qt::WA_DeleteOnClose);

    this->m_login->setLoginClose(true);

#ifdef Q_OS_IOS
    m_login->resize(310,250);
    m_login->move(380,380);
#else
    DinerApplication::calcCenter(310, 210, this->width(), this->height());
    m_login->resize(DinerApplication::printCalcCenter().value("width"),
                         DinerApplication::printCalcCenter().value("height"));
    m_login->move(DinerApplication::printCalcCenter().value("x"),
                       DinerApplication::printCalcCenter().value("y"));
#endif

    this->m_login->show();
    this->disableObjects(true);
}

void MainWidget::checkLogin()
{
    this->m_login = new Login(this);

    // Delete from memory after closing.
    this->m_login->setAttribute(Qt::WA_DeleteOnClose);

#ifdef Q_OS_IOS
    m_login->resize(310,250);
    m_login->move(380,380);
#else
    DinerApplication::calcCenter(310, 210, this->width(), this->height());
    m_login->resize(DinerApplication::printCalcCenter().value("width"),
                         DinerApplication::printCalcCenter().value("height"));
    m_login->move(DinerApplication::printCalcCenter().value("x"),
                       DinerApplication::printCalcCenter().value("y"));
#endif

    m_login->show();
    this->disableObjects(true);
}

QSize MainWidget::printSize()
{
    return this->m_size;
}

void MainWidget::changeAppConfiguration()
{
    this->m_confdialog = new ConfigDialog(this);

    // Delete from memory after closing.
    m_confdialog->setAttribute(Qt::WA_DeleteOnClose);

    DinerApplication::calcCenter(600, 290, this->width(), this->height());
    m_confdialog->resize(DinerApplication::printCalcCenter().value("width"),
                         DinerApplication::printCalcCenter().value("height"));
    m_confdialog->move(DinerApplication::printCalcCenter().value("x"),
                       DinerApplication::printCalcCenter().value("y"));
    m_confdialog->show();
}

void MainWidget::startCheck()
{
    // Read local settings.
    this->readSettings("DinerTabletLocal.conf");

    // Check if file Local configuration exist.
    if(QFileInfo::exists("DinerTabletLocal.conf")) {
        // Set button status.
        this->tabletButtonStatus(true);
        // Read global conf.
        this->readSettings("DinerTabletGlobal.conf");
    } else {
        // Set button status.
        this->tabletButtonStatus(false);

        MainWidget::m_backgroundimage = (":/images/background-mainwidget.jpg");
        this->setBackgroundImage(MainWidget::m_backgroundimage, QPixmap());
    }

    // Check connection with diner server.
    if(!Loader::connectionOk()) {

        // Set button status.
        this->tabletButtonStatus(false);

        // Call error message in 2 secounds.
        QTimer::singleShot(2000, this, SLOT(callMsgErrorDinerServer()));
    }
}

void MainWidget::callMsgErrorDinerServer()
{
    // Hide objects!
    this->ui->frameMenu->hide();
    this->ui->frameMenuButtons->hide();
    this->ui->frameOrder->hide();
    this->ui->frameLangButtons->hide();

    const QString msg = QObject::tr("No communication with the DinerWeb server!");

    OverlayDialogBox* overlaybox = new OverlayDialogBox(this, Loader::wordwrap(msg, 47));

    DinerApplication::calcCenter(505, 150, this->width(), this->height());
    overlaybox->resize(DinerApplication::printCalcCenter().value("width"),
                       DinerApplication::printCalcCenter().value("height"));
    overlaybox->move(DinerApplication::printCalcCenter().value("x"),
                     DinerApplication::printCalcCenter().value("y"));
    overlaybox->show();
}

void MainWidget::printMsgNotImplemented()
{
    const QString msg = QObject::tr("Sorry, method not implemented!");

    OverlayDialogBox* overlaybox = new OverlayDialogBox(this, Loader::wordwrap(msg, 47));

    DinerApplication::calcCenter(400, 120, this->width(), this->height());
    overlaybox->resize(DinerApplication::printCalcCenter().value("width"),
                       DinerApplication::printCalcCenter().value("height"));
    overlaybox->move(DinerApplication::printCalcCenter().value("x"),
                     DinerApplication::printCalcCenter().value("y"));
    overlaybox->show();
}

void MainWidget::animatewidgets()
{
    this->ui->frameMenu->show();
    this->ui->frameMenuButtons->show();
    this->ui->frameLangButtons->show();

    // Create animation Frame Menu.
    QPropertyAnimation *animationMenu = new QPropertyAnimation(ui->frameMenu, "geometry");
    animationMenu->setDuration(1000);
    QRect startRectMenu(-100,50,50,200);
    QRect endRectMenu(ui->frameMenu->geometry());
    animationMenu->setStartValue(startRectMenu);
    animationMenu->setEndValue(endRectMenu);
    animationMenu->start();

    // Create animation Frame Menu Buttons.
    QPropertyAnimation *animationMenuBt = new QPropertyAnimation(ui->frameMenuButtons, "geometry");
    animationMenuBt->setDuration(1000);
    QRect startRectMenuBt(-100,50,50,200);
    QRect endRectMenuBt(740,20,241,461);
    animationMenuBt->setStartValue(startRectMenuBt);
    animationMenuBt->setEndValue(endRectMenuBt);
    animationMenuBt->start();

    // Create animation Frame Lang Buttons.
    QPropertyAnimation *animationMenuBtLang = new QPropertyAnimation(ui->frameLangButtons, "geometry");
    animationMenuBtLang->setDuration(1000);
    QRect startRectMenuBtLang(-100,50,50,200);
    QRect endRectMenuBtLang(740,490,232,86);
    animationMenuBtLang->setStartValue(startRectMenuBtLang);
    animationMenuBtLang->setEndValue(endRectMenuBtLang);
    animationMenuBtLang->start();

    // Create animation Button Status.
    QPropertyAnimation *animationBtStatus = new QPropertyAnimation(ui->pushButtonStatusTablet, "geometry");
    animationBtStatus->setDuration(1000);
    QRect startRectBtStatus(-100,50,50,200);
    QRect endRectBtStatus(830,580,51,51);
    animationBtStatus->setStartValue(startRectBtStatus);
    animationBtStatus->setEndValue(endRectBtStatus);
    animationBtStatus->start();
}

void MainWidget::tabletButtonStatus(bool status)
{
    QIcon icon;

    if(status) {
        // Status OK.
        icon.addFile(QStringLiteral(":/images/status-green.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui->pushButtonStatusTablet->setIcon(icon);
        ui->pushButtonStatusTablet->setIconSize(QSize(32, 32));
    } else {
        // Status problem.
        icon.addFile(QStringLiteral(":/images/status-red.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui->pushButtonStatusTablet->setIcon(icon);
        ui->pushButtonStatusTablet->setIconSize(QSize(32, 32));
    }
}

void MainWidget::setDownloadButtonMenuImage()
{
    ui->pushButtonMenu->setIcon(QIcon("images-static/menu.png"));
    ui->pushButtonMenu->setIconSize(QSize(190, 190));

    // @TODO: Correct this in the future.
    ui->pushButtonPTBR->setIcon(QIcon("images-static/flag-br.png"));
    ui->pushButtonUS->setIcon(QIcon("images-static/flag-us.png"));
    ui->pushButtonES->setIcon(QIcon("images-static/flag-es.png"));
}

QString MainWidget::printBackgroundImage()
{
    return MainWidget::m_backgroundimage;
}

void MainWidget::readSettings(const QString &conf)
{
    if(conf == "DinerTabletLocal.conf") {
        // ???
    } else if(conf == "DinerTabletGlobal.conf") {

        QSettings settings("DinerTabletGlobal.conf", QSettings::IniFormat);

        settings.beginGroup("MainWidget");

        //
        // MAINWIDGET OBJECTS
        //
        {
            // Download background image.
            bool dlBackgroundImage = settings.value("downloadBackgroundImage").toBool();
            if(dlBackgroundImage) {
                MainWidget::m_backgroundimage = ("images-static/background-mainwidget.jpg");
                this->setBackgroundImage(MainWidget::m_backgroundimage, QPixmap());
            } else {
                MainWidget::m_backgroundimage = (":/images/background-mainwidget.jpg");
                this->setBackgroundImage(MainWidget::m_backgroundimage, QPixmap());
            }

            // Download button menu image.
            bool dlButtonMenuImage = settings.value("downloadButtonMenuImage").toBool();
            if(dlButtonMenuImage) {
                this->setDownloadButtonMenuImage();
            }

            // Check default language.
            QString defaultLanguage = settings.value("defaultLanguage").toString();
            if(defaultLanguage.isEmpty() || defaultLanguage == "en_US") {
                changeLanguageToEnglishUS();
            } else if(defaultLanguage == "pt_BR") {
                changeLanguageToPortugueseBR();
            } else if(defaultLanguage == "es") {
                changeLanguageToSpanish();
            }

            bool btPTBR = settings.value("pushButtonPTBR").toBool();
            if(!btPTBR) {
                ui->pushButtonPTBR->hide();
            }

            bool btUS = settings.value("pushButtonUS").toBool();
            if(!btUS) {
                ui->pushButtonUS->hide();
            }

            bool btES = settings.value("pushButtonES").toBool();
            if(!btES) {
                ui->pushButtonES->hide();
            }

            // Check buttons.
            bool enableSeparateOrders = settings.value("enableSeparateOrders").toBool();
            if(!enableSeparateOrders) {
                MainWidget::m_enableseparateorders = true;
            } else {
                MainWidget::m_enableseparateorders = false;
            }
        }

        //
        // MAINWIDGET OBJECTS - frameMenuButtons
        //
        {
            // Check buttons.
            bool btChefSuggestion = settings.value("pushButtonChefSuggestion").toBool();
            if(!btChefSuggestion) {
                ui->pushButtonChefSuggestion->hide();
            }

            bool btNews = settings.value("pushButtonNews").toBool();
            if(!btNews) {
                ui->pushButtonNews->hide();
            }

            bool btInternet = settings.value("pushButtonInternet").toBool();
            if(!btInternet) {
                ui->pushButtonInternet->hide();
            }

            bool btPhotos = settings.value("pushButtonPhotos").toBool();
            if(!btPhotos) {
                ui->pushButtonPhotos->hide();
            }

            bool btGames = settings.value("pushButtonGames").toBool();
            if(!btGames) {
                ui->pushButtonGames->hide();
            }

            bool btTaxi = settings.value("pushButtonTaxi").toBool();
            if(!btTaxi) {
                ui->pushButtonTaxi->hide();
            }

            bool btBill = settings.value("pushButtonBill").toBool();
            if(!btBill) {
                ui->pushButtonBill->hide();
            }

            bool btValet = settings.value("pushButtonValet").toBool();
            if(!btValet) {
                ui->pushButtonValet->hide();
            }

            // Check buttons.
            int fontSizeBtFrameMenu = settings.value("fontSizeButtonsFrameMenu").toInt();
            if(fontSizeBtFrameMenu >= 10) {
                QString sizeF = ("font: bold " + QString::number(fontSizeBtFrameMenu) + "px;");

                ui->pushButtonBill->setStyleSheet(sizeF);
                ui->pushButtonChefSuggestion->setStyleSheet(sizeF);
                ui->pushButtonGames->setStyleSheet(sizeF);
                ui->pushButtonInternet->setStyleSheet(sizeF);
                ui->pushButtonNews->setStyleSheet(sizeF);
                ui->pushButtonPhotos->setStyleSheet(sizeF);
                ui->pushButtonTaxi->setStyleSheet(sizeF);
                ui->pushButtonValet->setStyleSheet(sizeF);
            }

        }

        settings.endGroup();
    }
}

void MainWidget::setBackgroundImage(const QString &img, const QPixmap &pix)
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

void MainWidget::changeEvent(QEvent *event)
{
    // Event change language.
    if(event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}

void MainWidget::changeLanguageToEnglishUS()
{
    MainWidget::m_language = "en_US";
    QCoreApplication::removeTranslator(this->m_translator);
}

void MainWidget::changeLanguageToPortugueseBR()
{
    MainWidget::m_language = "pt_BR";
    this->changeLanguageTo(MainWidget::m_language);
}

void MainWidget::changeLanguageToSpanish()
{
    MainWidget::m_language = "es";
    this->changeLanguageTo(MainWidget::m_language);
}

void MainWidget::changeLanguageTo(const QString &language)
{
    const QString ts =  ("DinerTablet_" + language);

    if(this->m_translator->load(ts, ":/translations")) {
        QCoreApplication::removeTranslator(this->m_translator);
        QCoreApplication::installTranslator(this->m_translator);
    }
}

QString MainWidget::printLanguage()
{
    // Default language is english.
    if(MainWidget::m_language.isEmpty()) {
        MainWidget::m_language = "en_US";
    }

    return MainWidget::m_language;
}
