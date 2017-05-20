/**
 * @file listorder.cpp
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

#include "listorder.h"
#include "ui_listorder.h"
#include "xmlrpcclient.h"
#include "overlaydialogbox.h"
#include "loader.h"
#include "menufoods.h"
#include "menuwidget.h"
#include "mainwidget.h"
#include "dinerapplication.h"
#include "printout.h"

// Start static variable and objects.
ListOrder* ListOrder::instance = 0;

ListOrder* ListOrder::getInstance()
{
    if(instance == 0) {
        instance = new ListOrder;
    }
    return instance;
}

ListOrder::ListOrder(QWidget *parent) :
    QWidget(parent), ui(new Ui::ListOrder)
{
    // Call ui interface.
    ui->setupUi(this);

    // Set background image.
    this->setBackgroundImage(":/images/waiter-order.jpg", QPixmap());

    // Set font label message.
    QFont fontLB("Great Vibes", 20, QFont::Bold);
    QString style = ( "QLabel { background-color : transparent; "
                      "color : white; }" );
    ui->labelFood->setFont(fontLB);
    ui->labelFood->setStyleSheet(style);
    ui->labelDrink->setFont(fontLB);
    ui->labelDrink->setStyleSheet(style);
    ui->labelWine->setFont(fontLB);
    ui->labelWine->setStyleSheet(style);

    // Hide labels.
    ui->labelFood->hide();
    ui->labelDrink->hide();
    ui->labelWine->hide();

    // Set no fucus border listwidget.
    ui->listWidgetFoods->setFocusPolicy(Qt::NoFocus);
    ui->listWidgetDrinks->setFocusPolicy(Qt::NoFocus);
    ui->listWidgetWine->setFocusPolicy(Qt::NoFocus);

    // Hide listwidgets.
    ui->listWidgetFoods->hide();
    ui->listWidgetDrinks->hide();
    ui->listWidgetWine->hide();

    // Signals and slots.
    QObject::connect(ui->pushButtonRequest, SIGNAL(clicked()), this, SLOT(orderRequest()));
    QObject::connect(ui->pushButtonAddMore, SIGNAL(clicked()), this, SLOT(addMore()));
}

ListOrder::~ListOrder()
{
    delete ui;
}

void ListOrder::closeEvent(QCloseEvent *event)
{
    this->addMore();
    event->accept();
}

void ListOrder::showAll()
{
    this->startListFoods(0);
    this->startListDrinks(0);
    this->startListWine(0);
}

void ListOrder::startListFoods(int id)
{
    // Set names store data.
    m_foods.filename = "datafoods-" + QString::number(MainWidget::printNumberOrder());
    m_foods.filenameids = "datafoodsids-" + QString::number(MainWidget::printNumberOrder());
    m_foods.filenamespin = "datafoodsspins-" + QString::number(MainWidget::printNumberOrder());

    m_idfood = id;

    if(m_idfood == 0) {
        this->xmlRpcCallDishes();
    } else {
        // Call xml rpc server (filter dishe).
        const QString param = "cd_prato = " + QString::number(m_idfood);

        // Set list parameters.
        QVariantList paraml;
        paraml.append(param);

        m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                    "prato", "getPratos", paraml);

        // Connect slot dishes and error.
        QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallDishes()));
        QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
    }

    // Connect slot in list foods.
    QObject::connect(ui->listWidgetFoods,
            SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemClickedFoods(QListWidgetItem*)));
    QObject::connect(ui->listWidgetFoods,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(currentItemChangedFoods(QListWidgetItem*,QListWidgetItem*)));
}

void ListOrder::startListDrinks(int id)
{
    // Set names store data.
    m_drinks.filename = "datadrinks-" + QString::number(MainWidget::printNumberOrder());
    m_drinks.filenameids = "datadrinksids-" + QString::number(MainWidget::printNumberOrder());
    m_drinks.filenamespin = "datadrinksspins-" + QString::number(MainWidget::printNumberOrder());

    m_iddrinks = id;

    if(m_iddrinks == 0) {
        this->xmlRpcCallDrinks();
    } else {
        // Call xml rpc server (filter drinks).
        const QString param = "cd_bebida = " + QString::number(m_iddrinks);

        // Set list parameters.
        QVariantList paraml;
        paraml.append(param);

        m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                    "bebida", "getBebidas", paraml);

        // Connect slot dishes and error.
        QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallDrinks()));
        QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
    }

    // Connect slot in list drinks.
    QObject::connect(ui->listWidgetDrinks,
            SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemClickedDrinks(QListWidgetItem*)));
    QObject::connect(ui->listWidgetDrinks,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(currentItemChangedDrinks(QListWidgetItem*,QListWidgetItem*)));
}

void ListOrder::startListWine(int id)
{
    // Set names store data.
    m_wine.filename = "datawine-" + QString::number(MainWidget::printNumberOrder());
    m_wine.filenameids = "datawineids-" + QString::number(MainWidget::printNumberOrder());
    m_wine.filenamespin = "datawinespins-" + QString::number(MainWidget::printNumberOrder());

    m_idwine = id;

    if(m_idwine == 0) {
        this->xmlRpcCallWines();
    } else {
        // Call xml rpc server (filter wine).
        const QString param = "cd_vinho = " + QString::number(m_idwine);

        // Set list parameters.
        QVariantList paraml;
        paraml.append(param);

        m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                    "vinho", "getVinhos", paraml);

        // Connect slot dishes and error.
        QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallWines()));
        QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
    }

    // Connect slot in list drinks.
    QObject::connect(ui->listWidgetWine,
            SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemClickedWines(QListWidgetItem*)));
    QObject::connect(ui->listWidgetWine,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(currentItemChangedWines(QListWidgetItem*,QListWidgetItem*)));
}

void ListOrder::saveData()
{
    // Save and serialize data (foods).
    Loader::serializeRecordData(m_foods.filename, m_foods.datalocal);
    Loader::serializeRecordData(m_foods.filenameids, m_foods.id);
    Loader::serializeRecordData(m_foods.filenamespin, m_foods.mapspins);

    // Save and serialize data (drinks).
    Loader::serializeRecordData(m_drinks.filename, m_drinks.datalocal);
    Loader::serializeRecordData(m_drinks.filenameids, m_drinks.id);
    Loader::serializeRecordData(m_drinks.filenamespin, m_drinks.mapspins);

    // Save and serialize data (wine).
    Loader::serializeRecordData(m_wine.filename, m_wine.datalocal);
    Loader::serializeRecordData(m_wine.filenameids, m_wine.id);
    Loader::serializeRecordData(m_wine.filenamespin, m_wine.mapspins);
}

void ListOrder::addMore()
{
    this->saveData();
    this->close();
    Q_EMIT addMoreClicked();
}

void ListOrder::orderRequest()
{
    const QString msg = QObject::tr("Do you really want to place your order now? "
                                    "You can still add more items.");

    OverlayDialogBox* overlaybox = new OverlayDialogBox(this, Loader::wordwrap(msg, 47), true);

    DinerApplication::calcCenter(515, 180, this->width(), this->height());
    overlaybox->resize(DinerApplication::printCalcCenter().value("width"),
                       DinerApplication::printCalcCenter().value("height"));
    overlaybox->move(DinerApplication::printCalcCenter().value("x"),
                     DinerApplication::printCalcCenter().value("y"));
    overlaybox->show();

    // Signals and slots.
    QObject::connect(overlaybox, SIGNAL(okClicked()), this, SLOT(orderRequestNow()));
}

void ListOrder::orderRequestNow()
{
    qDebug() << "OK clicked.";

    qDebug() << "DataLocal " << m_foods.datalocal << m_foods.filename;
    qDebug() << "FileNameids " << m_foods.id;
    qDebug() << "FileNameSpin " << m_foods.mapspins;

    // Send to Kitchen.
    if(!m_foods.datalocal.isEmpty()) {
        QList<QVariant> datalocaln;

        QMap<int, int>::iterator im;
        for(im = m_foods.mapspins.begin(); im != m_foods.mapspins.end(); ++im) {
            datalocaln.append(im.value());
        }

        const int size = datalocaln.size();

        // Avoid segmentation fault.
        if(size == 0) {
            datalocaln.append("1");
        }

        // Send file to printer.
        PrintOut *w = new PrintOut(0, 1, 1);
        w->sendToPrinter(m_foods.datalocal, datalocaln);

        // Save and serialize data to payment (bill foods).
        Loader::serializeRecordData("bill" + m_foods.filename, m_foods.datalocal);
        Loader::serializeRecordData("bill" + m_foods.filenameids, m_foods.id);
        Loader::serializeRecordData("bill" + m_foods.filenamespin, m_foods.mapspins);

        // Remove data.
        Loader::removeFile(m_foods.filename);
        Loader::removeFile(m_foods.filenameids);
        Loader::removeFile(m_foods.filenamespin);

        // Clear variables.
        m_foods.datalocal.clear();
        m_foods.id.clear();
        m_foods.mapspins.clear();
    }

    // Send to Bar.
    if(!m_drinks.datalocal.isEmpty() | !m_wine.datalocal.isEmpty()) {
        QList<QVariant> datalocaln;

        QMap<int, int>::iterator imd;
        for(imd = m_drinks.mapspins.begin(); imd != m_drinks.mapspins.end(); ++imd) {
            datalocaln.append(imd.value());
        }

        QMap<int, int>::iterator imw;
        for(imw = m_wine.mapspins.begin(); imw != m_wine.mapspins.end(); ++imw) {
            datalocaln.append(imw.value());
        }

        const int size = datalocaln.size();

        // Avoid segmentation fault.
        if(size == 0) {
            datalocaln.append("1");
        }

        QList<QVariant> joindata;
        joindata.append(m_drinks.datalocal);
        joindata.append(m_wine.datalocal);

        //qDebug() << joindata;
        //PrintOut *w = new PrintOut(0, 1);
        //w->sendToKitchen(m_foods.datalocal, datalocaln);
    }

    this->addMore();
    Q_EMIT afterRequestOrder();
}

void ListOrder::showListWidgetFoods()
{
    ui->labelFood->show();
    ui->listWidgetFoods->show();
}

void ListOrder::showListWidgetDrinks()
{
    ui->labelDrink->show();
    ui->listWidgetDrinks->show();
}

void ListOrder::showListWidgetWine()
{
    ui->labelWine->show();
    ui->listWidgetWine->show();
}

void ListOrder::xmlRpcError()
{
    QString msg = QObject::tr("No communication with the DinerWeb server! "
                              "Error number: ");

    OverlayDialogBox* overlaybox = new OverlayDialogBox(this, msg + XmlRpcClient::errorCode());

    DinerApplication::calcCenter(450, 450, this->width(), this->height());
    overlaybox->resize(DinerApplication::printCalcCenter().value("width"),
                       DinerApplication::printCalcCenter().value("height"));
    overlaybox->move(DinerApplication::printCalcCenter().value("x"),
                     DinerApplication::printCalcCenter().value("y"));
    overlaybox->show();
}

void ListOrder::xmlRpcCallDishes()
{
    QList<QVariant> data;

    if(m_idfood >= 1) {
        data = m_xmlrpc->printValues().toList();

        // Check the return value of rpc is empty.
        if(data.isEmpty()) {
            this->xmlRpcError();
        }
    }

    // Extract data id foods in file.
    m_foods.id.append(Loader::serializeExtractData(m_foods.filenameids));

    // Avoids duplicate item!
    if(!m_foods.id.contains(this->m_idfood)) {

        // Store id food list.
        m_foods.id.append(this->m_idfood);

        if(m_idfood >= 1) {
            // Store data in datalocal list.
            m_foods.datalocal.append(data);
        }
    }

    // Extract data foods in file.
    m_foods.datalocal.append(Loader::serializeExtractData(m_foods.filename));

    // Extract data spin map values.
    m_foods.mapspins = Loader::serializeExtractDataMap(m_foods.filenamespin);

    // Show list widget if exist values.
    if(m_foods.datalocal.count() >= 1) {
        // @TODO: Incredibly, it works not calling the show()
        // in listview directly here.
        //QTimer::singleShot(0, this, SLOT(showListWidgetFoods()));
        this->showListWidgetFoods();
    }

    // Group button.
    m_foods.groupbuttonremove = new QButtonGroup(this);
    m_foods.groupbuttonadd = new QButtonGroup(this);

    for(int i = 0; i < m_foods.datalocal.size(); ++i) {
        QString name = QString();
        QString price = QString();
        const int active = m_foods.datalocal[i].toMap().value("ativo").toInt();

        if(active == 1) {
           const int identify = m_foods.datalocal[i].toMap().value("cd_prato").toInt();
           price = m_foods.datalocal[i].toMap().value("preco").toString();

           // Check language.
           if(MainWidget::printLanguage() == "en_US") {
               name = m_foods.datalocal[i].toMap().value("nome_en").toString();
           } else if(MainWidget::printLanguage() == "pt_BR") {
               name = m_foods.datalocal[i].toMap().value("nome_br").toString();
           } else if(MainWidget::printLanguage() == "es") {
               name = m_foods.datalocal[i].toMap().value("nome_es").toString();
           }

           QIcon icon = QIcon::fromTheme("edit-undo");
           QListWidgetItem *item = new QListWidgetItem();
           item->setIcon(icon);
           item->setWhatsThis(QString::number(identify));
           ui->listWidgetFoods->addItem(item);

           QLabel *labelFoodName = new QLabel(name);
           labelFoodName->setStyleSheet("QLabel { background-color : transparent; "
                                        "color : white; }");

           QPushButton *buttonRemove = new QPushButton("-");
           buttonRemove->setObjectName(QString::number(identify));
           buttonRemove->setMinimumWidth(100);
           buttonRemove->setMinimumHeight(40);
           m_foods.groupbuttonremove->addButton(buttonRemove, i);

           QSpinBox *spinUnit = new QSpinBox;
           spinUnit->setObjectName(QString::number(identify));
           spinUnit->setMaximumWidth(25);
           spinUnit->setMinimumHeight(40);
           spinUnit->setMinimum(0);
           spinUnit->setMaximum(50);
           spinUnit->setValue(1);
           spinUnit->setButtonSymbols(QAbstractSpinBox::NoButtons);
           spinUnit->setStyleSheet("QSpinBox { border-radius: 40px; "
                                   "background-color : transparent; color: white; }");
           spinUnit->setFocusPolicy(Qt::NoFocus);
           m_foods.spinlist.append(spinUnit);

           QFont* spinFont = new QFont();
           spinFont->setBold(true);
           spinFont->setPixelSize(15);
           spinUnit->setFont(*spinFont);

           QMap<int, int>::iterator im;
           for(im = m_foods.mapspins.begin(); im != m_foods.mapspins.end(); ++im) {
               if(im.key() == identify) {
                   spinUnit->setValue(im.value());
                   break;
               }
           }

           QPushButton *buttonAdd = new QPushButton("+");
           buttonAdd->setObjectName(QString::number(identify));
           buttonAdd->setMinimumWidth(100);
           buttonAdd->setMinimumHeight(40);
           m_foods.groupbuttonadd->addButton(buttonAdd, i);

           QSpacerItem *spacer = new QSpacerItem(40, 20,
                                                 QSizePolicy::MinimumExpanding,
                                                 QSizePolicy::Minimum);

           QHBoxLayout *layout= new QHBoxLayout();
           layout->addWidget(labelFoodName);
           layout->addItem(spacer);
           layout->addWidget(buttonRemove);
           layout->addWidget(spinUnit);
           layout->addWidget(buttonAdd);

           QWidget *widget = new QWidget();
           widget->setLayout(layout);
           item->setSizeHint(widget->sizeHint());
           ui->listWidgetFoods->setItemWidget(item, widget);
        }
    }

    // Signals and slots.
    QObject::connect(m_foods.groupbuttonremove, SIGNAL(buttonClicked(int)),
                     this, SLOT(buttonListFoodsRemoveWasClicked(int)));
    QObject::connect(m_foods.groupbuttonadd, SIGNAL(buttonClicked(int)),
                     this, SLOT(buttonListFoodsAddWasClicked(int)));
}

void ListOrder::xmlRpcCallDrinks()
{
    QList<QVariant> data;

    if(m_iddrinks >= 1) {
        data = m_xmlrpc->printValues().toList();

        // Check the return value of rpc is empty.
        if(data.isEmpty()) {
            this->xmlRpcError();
        }
    }

    // Extract data id drinks in file.
    m_drinks.id.append(Loader::serializeExtractData(m_drinks.filenameids));

    // Avoids duplicate item!
    if(!m_drinks.id.contains(this->m_iddrinks)) {

        // Store id drinks list.
        m_drinks.id.append(this->m_iddrinks);

        if(m_iddrinks >= 1) {
            // Store data in datalocal list.
            m_drinks.datalocal.append(data);
        }
    }

    // Extract data drinks in file.
    m_drinks.datalocal.append(Loader::serializeExtractData(m_drinks.filename));

    // Extract data spin map values.
    m_drinks.mapspins = Loader::serializeExtractDataMap(m_drinks.filenamespin);

    // Show list widget if exist values.
    if(m_drinks.datalocal.count() >= 1) {
        // @TODO: Incredibly, it works not calling the show()
        // in listview directly here.
        //QTimer::singleShot(0, this, SLOT(showListWidgetDrinks()));
        this->showListWidgetDrinks();
    }

    // Group button.
    m_drinks.groupbuttonremove = new QButtonGroup(this);
    m_drinks.groupbuttonadd = new QButtonGroup(this);

    for(int i = 0; i < m_drinks.datalocal.size(); ++i) {
        QString name = QString();
        QString price = QString();
        const int active = m_drinks.datalocal[i].toMap().value("ativo").toInt();

        if(active == 1) {
           const int identify = m_drinks.datalocal[i].toMap().value("cd_bebida").toInt();
           price = m_drinks.datalocal[i].toMap().value("preco").toString();

           // Check language.
           if(MainWidget::printLanguage() == "en_US") {
               name = m_drinks.datalocal[i].toMap().value("nome_en").toString();
           } else if(MainWidget::printLanguage() == "pt_BR") {
               name = m_drinks.datalocal[i].toMap().value("nome_br").toString();
           } else if(MainWidget::printLanguage() == "es") {
               name = m_drinks.datalocal[i].toMap().value("nome_es").toString();
           }

           QIcon icon = QIcon::fromTheme("edit-undo");
           QListWidgetItem *item = new QListWidgetItem();
           item->setIcon(icon);
           item->setWhatsThis(QString::number(identify));
           ui->listWidgetDrinks->addItem(item);

           QLabel *labelFoodName = new QLabel(name);
           labelFoodName->setStyleSheet("QLabel { background-color : transparent; "
                                        "color : white; }");

           QPushButton *buttonRemove = new QPushButton("-");
           buttonRemove->setObjectName(QString::number(identify));
           buttonRemove->setMinimumWidth(100);
           buttonRemove->setMinimumHeight(40);
           m_drinks.groupbuttonremove->addButton(buttonRemove, i);

           QSpinBox *spinUnit = new QSpinBox;
           spinUnit->setObjectName(QString::number(identify));
           spinUnit->setMaximumWidth(25);
           spinUnit->setMinimumHeight(40);
           spinUnit->setMinimum(0);
           spinUnit->setMaximum(50);
           spinUnit->setValue(1);
           spinUnit->setButtonSymbols(QAbstractSpinBox::NoButtons);
           spinUnit->setStyleSheet("QSpinBox { border-radius: 40px; "
                                   "background-color : transparent; color: white; }");
           spinUnit->setFocusPolicy(Qt::NoFocus);
           m_drinks.spinlist.append(spinUnit);

           QFont* spinFont = new QFont();
           spinFont->setBold(true);
           spinFont->setPixelSize(15);
           spinUnit->setFont(*spinFont);

           QMap<int, int>::iterator im;
           for(im = m_drinks.mapspins.begin(); im != m_drinks.mapspins.end(); ++im) {
               if(im.key() == identify) {
                   spinUnit->setValue(im.value());
                   break;
               }
           }

           QPushButton *buttonAdd = new QPushButton("+");
           buttonAdd->setObjectName(QString::number(identify));
           buttonAdd->setMinimumWidth(100);
           buttonAdd->setMinimumHeight(40);
           m_drinks.groupbuttonadd->addButton(buttonAdd, i);

           QSpacerItem *spacer = new QSpacerItem(40, 20,
                                                 QSizePolicy::MinimumExpanding,
                                                 QSizePolicy::Minimum);

           QHBoxLayout *layout= new QHBoxLayout();
           layout->addWidget(labelFoodName);
           layout->addItem(spacer);
           layout->addWidget(buttonRemove);
           layout->addWidget(spinUnit);
           layout->addWidget(buttonAdd);

           QWidget *widget = new QWidget();
           widget->setLayout(layout);
           item->setSizeHint(widget->sizeHint());
           ui->listWidgetDrinks->setItemWidget(item, widget);
        }
    }

    // Signals and slots.
    QObject::connect(m_drinks.groupbuttonremove, SIGNAL(buttonClicked(int)),
                     this, SLOT(buttonListDrinksRemoveWasClicked(int)));
    QObject::connect(m_drinks.groupbuttonadd, SIGNAL(buttonClicked(int)),
                     this, SLOT(buttonListDrinksAddWasClicked(int)));
}

void ListOrder::xmlRpcCallWines()
{
    QList<QVariant> data;

    if(m_idwine >= 1) {
        data = m_xmlrpc->printValues().toList();

        // Check the return value of rpc is empty.
        if(data.isEmpty()) {
            this->xmlRpcError();
        }
    }

    // Extract data id wine in file.
    m_wine.id.append(Loader::serializeExtractData(m_wine.filenameids));

    // Avoids duplicate item!
    if(!m_wine.id.contains(this->m_idwine)) {

        // Store id wine list.
        m_wine.id.append(this->m_idwine);

        if(m_idwine >= 1) {
            // Store data in datalocal list.
            m_wine.datalocal.append(data);
        }
    }

    // Extract data wine in file.
    m_wine.datalocal.append(Loader::serializeExtractData(m_wine.filename));

    // Extract data spin map values.
    m_wine.mapspins = Loader::serializeExtractDataMap(m_wine.filenamespin);

    // Show list widget if exist values.
    if(m_wine.datalocal.count() >= 1) {
        // @TODO: Incredibly, it works not calling the show()
        // in listview directly here.
        //QTimer::singleShot(0, this, SLOT(showListWidgetWine()));
        this->showListWidgetWine();
    }

    // Group button.
    m_wine.groupbuttonremove = new QButtonGroup(this);
    m_wine.groupbuttonadd = new QButtonGroup(this);

    for(int i = 0; i < m_wine.datalocal.size(); ++i) {
        QString name = QString();
        QString price = QString();
        const int active = m_wine.datalocal[i].toMap().value("ativo").toInt();

        if(active == 1) {
           const int identify = m_wine.datalocal[i].toMap().value("cd_vinho").toInt();
           price = m_wine.datalocal[i].toMap().value("preco").toString();
           name = m_wine.datalocal[i].toMap().value("nome").toString();

           QIcon icon = QIcon::fromTheme("edit-undo");
           QListWidgetItem *item = new QListWidgetItem();
           item->setIcon(icon);
           item->setWhatsThis(QString::number(identify));
           ui->listWidgetWine->addItem(item);

           QLabel *labelFoodName = new QLabel(name);
           labelFoodName->setStyleSheet("QLabel { background-color : transparent; "
                                        "color : white; }");

           QPushButton *buttonRemove = new QPushButton("-");
           buttonRemove->setObjectName(QString::number(identify));
           buttonRemove->setMinimumWidth(100);
           buttonRemove->setMinimumHeight(40);
           m_wine.groupbuttonremove->addButton(buttonRemove, i);

           QSpinBox *spinUnit = new QSpinBox;
           spinUnit->setObjectName(QString::number(identify));
           spinUnit->setMaximumWidth(25);
           spinUnit->setMinimumHeight(40);
           spinUnit->setMinimum(0);
           spinUnit->setMaximum(50);
           spinUnit->setValue(1);
           spinUnit->setButtonSymbols(QAbstractSpinBox::NoButtons);
           spinUnit->setStyleSheet("QSpinBox { border-radius: 40px; "
                                   "background-color : transparent; color: white; }");
           spinUnit->setFocusPolicy(Qt::NoFocus);
           m_wine.spinlist.append(spinUnit);

           QFont* spinFont = new QFont();
           spinFont->setBold(true);
           spinFont->setPixelSize(15);
           spinUnit->setFont(*spinFont);

           QMap<int, int>::iterator im;
           for(im = m_wine.mapspins.begin(); im != m_wine.mapspins.end(); ++im) {
               if(im.key() == identify) {
                   spinUnit->setValue(im.value());
                   break;
               }
           }

           QPushButton *buttonAdd = new QPushButton("+");
           buttonAdd->setObjectName(QString::number(identify));
           buttonAdd->setMinimumWidth(100);
           buttonAdd->setMinimumHeight(40);
           m_wine.groupbuttonadd->addButton(buttonAdd, i);

           QSpacerItem *spacer = new QSpacerItem(40, 20,
                                                 QSizePolicy::MinimumExpanding,
                                                 QSizePolicy::Minimum);

           QHBoxLayout *layout= new QHBoxLayout();
           layout->addWidget(labelFoodName);
           layout->addItem(spacer);
           layout->addWidget(buttonRemove);
           layout->addWidget(spinUnit);
           layout->addWidget(buttonAdd);

           QWidget *widget = new QWidget();
           widget->setLayout(layout);
           item->setSizeHint(widget->sizeHint());
           ui->listWidgetWine->setItemWidget(item, widget);
        }
    }

    // Signals and slots.
    QObject::connect(m_wine.groupbuttonremove, SIGNAL(buttonClicked(int)),
                     this, SLOT(buttonListWinesRemoveWasClicked(int)));
    QObject::connect(m_wine.groupbuttonadd, SIGNAL(buttonClicked(int)),
                     this, SLOT(buttonListWinesAddWasClicked(int)));
}

void ListOrder::buttonListWinesRemoveWasClicked(int buttonid)
{
    ui->listWidgetWine->setCurrentRow(buttonid);

    for(int i = 0; i < m_wine.spinlist.size(); ++i) {
        const int id = m_wine.datalocal[i].toMap().value("cd_vinho").toInt();

        if(m_wine.spinlist[buttonid]->objectName() == QString::number(id)) {

            const int val = m_wine.spinlist[buttonid]->value() - 1;
            m_wine.spinlist[buttonid]->setValue(val);
            m_wine.mapspins[id] = val;
            const int valzero = m_wine.spinlist[buttonid]->value();

            if(valzero == 0) {
                m_wine.mapspins.remove(id);
                m_wine.spinlist.removeAt(buttonid);
                m_wine.id.removeAt(buttonid);
                m_wine.datalocal.removeAt(buttonid);
                ui->listWidgetWine->takeItem(ui->listWidgetWine->row(ui->listWidgetWine->currentItem()));
                break;
            }
        }
    }
}

void ListOrder::buttonListWinesAddWasClicked(int buttonid)
{
    ui->listWidgetWine->setCurrentRow(buttonid);

    for(int i = 0; i < m_wine.spinlist.size(); ++i) {
        const int id = m_wine.datalocal[i].toMap().value("cd_vinho").toInt();

        if(m_wine.spinlist[buttonid]->objectName() == QString::number(id)) {
            const int val = m_wine.spinlist[buttonid]->value() + 1;
            m_wine.spinlist[buttonid]->setValue(val);
            m_wine.mapspins[id] = val;
        }
    }
}

void ListOrder::buttonListDrinksRemoveWasClicked(int buttonid)
{
    ui->listWidgetDrinks->setCurrentRow(buttonid);

    for(int i = 0; i < m_drinks.spinlist.size(); ++i) {
        const int id = m_drinks.datalocal[i].toMap().value("cd_bebida").toInt();

        if(m_drinks.spinlist[buttonid]->objectName() == QString::number(id)) {

            const int val = m_drinks.spinlist[buttonid]->value() - 1;
            m_drinks.spinlist[buttonid]->setValue(val);
            m_drinks.mapspins[id] = val;
            const int valzero = m_drinks.spinlist[buttonid]->value();

            if(valzero == 0) {
                m_drinks.mapspins.remove(id);
                m_drinks.spinlist.removeAt(buttonid);
                m_drinks.id.removeAt(buttonid);
                m_drinks.datalocal.removeAt(buttonid);
                ui->listWidgetDrinks->takeItem(ui->listWidgetDrinks->row(ui->listWidgetDrinks->currentItem()));
                break;
            }
        }
    }
}

void ListOrder::buttonListDrinksAddWasClicked(int buttonid)
{
    ui->listWidgetDrinks->setCurrentRow(buttonid);

    for(int i = 0; i < m_drinks.spinlist.size(); ++i) {
        const int id = m_drinks.datalocal[i].toMap().value("cd_bebida").toInt();

        if(m_drinks.spinlist[buttonid]->objectName() == QString::number(id)) {
            const int val = m_drinks.spinlist[buttonid]->value() + 1;
            m_drinks.spinlist[buttonid]->setValue(val);
            m_drinks.mapspins[id] = val;
        }
    }
}

void ListOrder::buttonListFoodsRemoveWasClicked(int buttonid)
{
    ui->listWidgetFoods->setCurrentRow(buttonid);

    for(int i = 0; i < m_foods.spinlist.size(); ++i) {
        const int id = m_foods.datalocal[i].toMap().value("cd_prato").toInt();

        if(m_foods.spinlist[buttonid]->objectName() == QString::number(id)) {
            const int val = m_foods.spinlist[buttonid]->value() - 1;
            m_foods.spinlist[buttonid]->setValue(val);
            m_foods.mapspins[id] = val;
            const int valzero = m_foods.spinlist[buttonid]->value();

            if(valzero == 0) {
                m_foods.mapspins.remove(id);
                m_foods.spinlist.removeAt(buttonid);
                m_foods.id.removeAt(buttonid);
                m_foods.datalocal.removeAt(buttonid);
                ui->listWidgetFoods->takeItem(ui->listWidgetFoods->row(ui->listWidgetFoods->currentItem()));
                break;
            }
        }
    }
}

void ListOrder::buttonListFoodsAddWasClicked(int buttonid)
{
    ui->listWidgetFoods->setCurrentRow(buttonid);

    for(int i = 0; i < m_foods.spinlist.size(); ++i) {
        const int id = m_foods.datalocal[i].toMap().value("cd_prato").toInt();

        if(m_foods.spinlist[buttonid]->objectName() == QString::number(id)) {
            const int val = m_foods.spinlist[buttonid]->value() + 1;
            m_foods.spinlist[buttonid]->setValue(val);
            m_foods.mapspins[id] = val;
        }
    }
}

void ListOrder::itemClickedFoods(QListWidgetItem *item)
{
    item->setSelected(true);
    ui->listWidgetFoods->setCurrentItem(item);
    ui->listWidgetFoods->row(item);
}

void ListOrder::currentItemChangedFoods(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(!current) {
        current = previous;
    }

    current->setSelected(true);
    ui->listWidgetFoods->setCurrentItem(current);
    ui->listWidgetFoods->row(current);
}

void ListOrder::itemClickedDrinks(QListWidgetItem *item)
{
    item->setSelected(true);
    ui->listWidgetDrinks->setCurrentItem(item);
    ui->listWidgetDrinks->row(item);
}

void ListOrder::currentItemChangedDrinks(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(!current) {
        current = previous;
    }

    current->setSelected(true);
    ui->listWidgetDrinks->setCurrentItem(current);
    ui->listWidgetDrinks->row(current);
}

void ListOrder::itemClickedWines(QListWidgetItem *item)
{
    item->setSelected(true);
    ui->listWidgetWine->setCurrentItem(item);
    ui->listWidgetWine->row(item);
}

void ListOrder::currentItemChangedWines(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(!current) {
        current = previous;
    }

    current->setSelected(true);
    ui->listWidgetWine->setCurrentItem(current);
    ui->listWidgetWine->row(current);
}

int ListOrder::checkOrderIsEmpty()
{
    unsigned int countFoods = m_foods.datalocal.count();
    unsigned int countDrinks = m_drinks.datalocal.count();

    if((countFoods == 0) & (countDrinks == 0)) {
        return 0;
    }

    return 1;
}

void ListOrder::setBackgroundImage(const QString &img, const QPixmap &pix)
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
