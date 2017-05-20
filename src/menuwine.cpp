/**
 * @file menuwine.cpp
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

#include "menuwine.h"
#include "ui_menuwine.h"
#include "xmlrpcclient.h"
#include "overlaydialogbox.h"
#include "listorder.h"
#include "listitemwinedetails.h"
#include "loader.h"
#include "dinerapplication.h"
#include "mainwidget.h"
#include "menuwinefilter.h"

MenuWine::MenuWine(QWidget *parent, int idorder) :
    QWidget(parent), ui(new Ui::MenuWine),
    m_idorder(idorder), m_winefilter(0), m_idwine(0)
{
    // Call ui interface.
    ui->setupUi(this);

    // Read settings.
    this->readSettings("DinerTabletGlobal.conf");

    // Call xml rpc server.
    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "vinho-foto", "getFotos");

    // Connect slot category and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallPhotos()));
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));

    // Set confs listwidget.
    ui->listWidget->setFocusPolicy(Qt::NoFocus);
    ui->listWidget->setIconSize(QSize(48, 48));

    // Set font Diner Tablet.
    ui->labelFilter->setStyleSheet("QLabel { background-color : transparent; color : white; }");
    ui->labelFilter->setText(QObject::tr("         Filters")); // (9) white space.

    // Check timer image random.
    if(m_timerandomadsimages >= 5000) {
        QTimer *timer = new QTimer(this);
        timer->start(m_timerandomadsimages);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(imageFrameRandom()));
    }

    // Signals and slots.
    QObject::connect(ui->pushButtonAllWines, SIGNAL(clicked()), this, SLOT(listAllWines()));
    QObject::connect(ui->pushButtonFilterType, SIGNAL(clicked()), this, SLOT(listWineType()));
    QObject::connect(ui->pushButtonFilterVarietals, SIGNAL(clicked()), this, SLOT(listWineVarietals()));
    QObject::connect(ui->pushButtonFilterCountry, SIGNAL(clicked()), this, SLOT(listWineCountries()));
    QObject::connect(ui->pushButtonFilterRegion, SIGNAL(clicked()), this, SLOT(listWineRegion()));
    QObject::connect(ui->pushButtonFilterProducer, SIGNAL(clicked()), this, SLOT(listWineProducer()));
    QObject::connect(ui->listWidget,
                     SIGNAL(itemClicked(QListWidgetItem*)),
                     this, SLOT(itemClicked(QListWidgetItem*)));
    QObject::connect(ui->listWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(currentItemChanged(QListWidgetItem*,QListWidgetItem*)));
}

MenuWine::~MenuWine()
{
    delete ui;
}

void MenuWine::readSettings(const QString &conf)
{
    QSettings settings(conf, QSettings::IniFormat);

    settings.beginGroup("MenuWine");

    // Read time random images.
    m_timerandomadsimages = settings.value("timeRandomWineImages").toInt();

    bool btFilterType = settings.value("pushButtonFilterType").toBool();
    if(!btFilterType) {
        ui->pushButtonFilterType->hide();
    }

    bool btFilterVarietals = settings.value("pushButtonFilterVarietals").toBool();
    if(!btFilterVarietals) {
        ui->pushButtonFilterVarietals->hide();
    }

    bool btFilterCountry = settings.value("pushButtonFilterCountry").toBool();
    if(!btFilterCountry) {
        ui->pushButtonFilterCountry->hide();
    }

    bool btFilterRegion = settings.value("pushButtonFilterRegion").toBool();
    if(!btFilterRegion) {
        ui->pushButtonFilterRegion->hide();
    }

    bool btFilterProducer = settings.value("pushButtonFilterProducer").toBool();
    if(!btFilterProducer) {
        ui->pushButtonFilterProducer->hide();
    }

    settings.endGroup();
}

void MenuWine::listAllWines()
{
    // Clear values.
    this->ui->listWidget->clear();
    m_rpcparam.clear();
    MenuWineFilter::clearQueryFilter();

    // Set button name default.
    ui->pushButtonFilterType->setText(QObject::tr("Type"));
    ui->pushButtonFilterVarietals->setText(QObject::tr("Varietals"));
    ui->pushButtonFilterCountry->setText(QObject::tr("Country"));
    ui->pushButtonFilterRegion->setText(QObject::tr("Region"));
    ui->pushButtonFilterProducer->setText(QObject::tr("Producer"));

    // Set type filter.
    m_winefilter = 0;

    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "vinho", "getVinhos");

    // Connect slot category and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallWines()));
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
}

void MenuWine::listWineParameter()
{
    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "vinho", "getVinhos", m_rpcparam);

    // Connect slot category and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallWines()));
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
}

void MenuWine::listWineType()
{
    // Set type filter.
    m_winefilter = 1;

    MenuWineFilter *w = new MenuWineFilter(0);

    // Delete from memory after closing.
    w->setAttribute(Qt::WA_DeleteOnClose);

    w->setBackgroundImage(":/images/wine-type.jpg", QPixmap());
    w->setFilterType();
    w->show();

    QObject::connect(w, SIGNAL(buttonClicked()), this, SLOT(getQueryParam()));
}

void MenuWine::listWineVarietals()
{
    // Set type filter.
    m_winefilter = 2;

    MenuWineFilter *w = new MenuWineFilter(0);

    // Delete from memory after closing.
    w->setAttribute(Qt::WA_DeleteOnClose);

    w->setBackgroundImage(":/images/wine-varietals.jpg", QPixmap());
    w->setFilterVarietals();
    w->show();

    QObject::connect(w, SIGNAL(buttonClicked()), this, SLOT(getQueryParam()));
}

void MenuWine::listWineCountries()
{
    // Set type filter.
    m_winefilter = 3;

    MenuWineFilter *w = new MenuWineFilter(0);

    // Delete from memory after closing.
    w->setAttribute(Qt::WA_DeleteOnClose);

    w->setBackgroundImage(":/images/wine-country.jpg", QPixmap());
    w->setFilterCountries();
    w->show();

    QObject::connect(w, SIGNAL(buttonClicked()), this, SLOT(getQueryParam()));
}

void MenuWine::listWineRegion()
{
    // Set type filter.
    m_winefilter = 4;

    MenuWineFilter *w = new MenuWineFilter(0);

    // Delete from memory after closing.
    w->setAttribute(Qt::WA_DeleteOnClose);

    w->setBackgroundImage(":/images/wine-region.jpg", QPixmap());
    w->setFilterRegion();
    w->show();

    QObject::connect(w, SIGNAL(buttonClicked()), this, SLOT(getQueryParam()));
}

void MenuWine::listWineProducer()
{
    // Set type filter.
    m_winefilter = 5;

    MenuWineFilter *w = new MenuWineFilter(0);

    // Delete from memory after closing.
    w->setAttribute(Qt::WA_DeleteOnClose);

    w->setBackgroundImage(":/images/wine-producer.jpg", QPixmap());
    w->setFilterProducer();
    w->show();

    QObject::connect(w, SIGNAL(buttonClicked()), this, SLOT(getQueryParam()));
}

void MenuWine::getQueryParam()
{
    const QString param = MenuWineFilter::printQueryFilter();
    const QString name = MenuWineFilter::printNameFilterSelected();

    //qDebug() << param;
    //qDebug() << name;

    if(m_winefilter == 1) {
        ui->pushButtonFilterType->setText(name);
    } else if(m_winefilter == 2) {
        ui->pushButtonFilterVarietals->setText(name);
    } else if(m_winefilter == 3) {
        ui->pushButtonFilterCountry->setText(name);
    } else if(m_winefilter == 4) {
        ui->pushButtonFilterRegion->setText(name);
    } else if(m_winefilter == 5) {
        ui->pushButtonFilterProducer->setText(name);
    }

    // Clear variable.
    m_rpcparam.clear();

    // Set list parameters.
    m_rpcparam.append(param);

    this->ui->listWidget->clear();
    this->listWineParameter();
}

void MenuWine::setIdOrder(int idorder)
{
    m_idorder = idorder;
}

void MenuWine::finishedDownload()
{
    // Set image.
    this->imageFrameRandom();
}

void MenuWine::imageFrameRandom()
{
    const QStringList strlist = Loader::printListReadDownload();

    // Avoid segmentation fault.
    if(strlist.isEmpty()) {
        return;
    }

    QStringList strlistfilter  = strlist.filter(QRegExp("^(images-dynamic/MenuWines)", Qt::CaseInsensitive));

    // Avoid segmentation fault.
    if(strlistfilter.isEmpty()) {
        return;
    }

    QString str = strlistfilter.at(qrand() % strlistfilter.size());
    QString setImg = "QListWidget {"
                     "  background-image: url(" + str + ");"
                     "  background-position: center; "
                     "} ";

    ui->listWidget->setStyleSheet(setImg);
}

void MenuWine::xmlRpcError()
{
    // Clear values.
    this->ui->listWidget->clear();
    m_rpcparam.clear();
    MenuWineFilter::clearQueryFilter();

    // Set button name default.
    ui->pushButtonFilterType->setText(QObject::tr("Type"));
    ui->pushButtonFilterVarietals->setText(QObject::tr("Varietals"));
    ui->pushButtonFilterCountry->setText(QObject::tr("Country"));
    ui->pushButtonFilterRegion->setText(QObject::tr("Region"));
    ui->pushButtonFilterProducer->setText(QObject::tr("Producer"));

    // Set type filter.
    m_winefilter = 0;

    const QString msg = QObject::tr("Sorry, wine not found! Please try a new search.");

    OverlayDialogBox* overlaybox = new OverlayDialogBox(this, Loader::wordwrap(msg, 47));

    DinerApplication::calcCenter(510, 170, 1024, 500);
    overlaybox->resize(DinerApplication::printCalcCenter().value("width"),
                       DinerApplication::printCalcCenter().value("height"));
    overlaybox->move(DinerApplication::printCalcCenter().value("x"),
                     DinerApplication::printCalcCenter().value("y"));
    overlaybox->show();
}

void MenuWine::xmlRpcCallPhotos()
{
    QList<QVariant> data = m_xmlrpc->printValues().toList();

    // Check the return value of rpc is empty.
    if(data.isEmpty()) {
        this->xmlRpcError();
    }

    for(int i = 0; i < data.size(); ++i) {
        //const int id = data[i].toMap().value("cd_foto").toInt();
        const QString photo = data[i].toMap().value("foto").toString();

        // Download image.
        Loader* dd = new Loader;
        dd->download(photo, "images-dynamic", 0);

        // Connect loader.
        QObject::connect(dd, SIGNAL(finishedDownload()),
                         this, SLOT(finishedDownload()));
    }
}

void MenuWine::xmlRpcCallWines()
{
    QList<QVariant> data = m_xmlrpc->printValues().toList();

    // Check the return value of rpc is empty.
    if(data.isEmpty()) {
        this->xmlRpcError();
    }

    // Group buttons.
    this->m_groupbuttonadd = new QButtonGroup(this);
    this->m_groupbuttondetail = new QButtonGroup(this);

    for(int i = 0; i < data.size(); ++i) {
        QString name = QString();
        QString price = QString();
        const int active = data[i].toMap().value("ativo").toInt();

        if(active == 1) {
           int identify = data[i].toMap().value("cd_vinho").toInt();
           price = data[i].toMap().value("preco").toString();
           QString name = data[i].toMap().value("nome").toString();

           QIcon icon = QIcon::fromTheme("edit-undo");
           QListWidgetItem *item = new QListWidgetItem();
           item->setIcon(icon);
           item->setWhatsThis(QString::number(identify));
           ui->listWidget->addItem(item);

           QLabel *labelFoodName = new QLabel(name);
           labelFoodName->setStyleSheet("QLabel { background-color : transparent; "
                                        "color : white; font: bold 15px;}");

           QLabel *labelPrice = new QLabel("R$ " + price);
           labelPrice->setStyleSheet("QLabel { background-color : transparent; "
                                     "color : white; font: bold 15px;}");

           QPushButton *buttonAdd = new QPushButton(QObject::tr("Add"));
           buttonAdd->setObjectName(QString::number(identify));
           buttonAdd->setMinimumWidth(100);
           buttonAdd->setMinimumHeight(40);
           //buttonAdd->resize(100,100);
           m_groupbuttonadd->addButton(buttonAdd, i);

           QPushButton *buttonDetailing = new QPushButton(QObject::tr("Detailing"));
           buttonDetailing->setMinimumWidth(100);
           buttonDetailing->setMinimumHeight(40);
           //buttonDetailing->resize(100,100);
           m_groupbuttondetail->addButton(buttonDetailing, i);

           QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding,
                                                 QSizePolicy::Minimum);

           QHBoxLayout *layout= new QHBoxLayout();
           layout->addWidget(labelFoodName);
           layout->addItem(spacer);
           layout->addWidget(labelPrice);

           layout->addWidget(buttonAdd);
           layout->addWidget(buttonDetailing);

           QWidget *widget = new QWidget();
           widget->setLayout(layout);
           item->setSizeHint(widget->sizeHint());
           ui->listWidget->setItemWidget(item, widget);
        }
    }

    // Signals and slots.
    QObject::connect(m_groupbuttonadd, SIGNAL(buttonClicked(int)),
                     this, SLOT(buttonListAddWasClicked(int)));
    QObject::connect(m_groupbuttondetail, SIGNAL(buttonClicked(int)),
                     this, SLOT(buttonListDetailWasClicked(int)));
}

void MenuWine::buttonListAddWasClicked(int buttonid)
{
    ui->listWidget->setCurrentRow(buttonid);
    showMyOrder();
}

void MenuWine::buttonListDetailWasClicked(int buttonid)
{
    ui->listWidget->setCurrentRow(buttonid);
    showDetails();
}

void MenuWine::showMyOrder()
{
    ListOrder *w = new ListOrder(0);

    w->startListWine(m_idwine);

    // Delete from memory after closing.
    w->setAttribute(Qt::WA_DeleteOnClose);

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

    this->disableObjects(true);
}

void MenuWine::showDetails()
{
    ListItemWineDetails *w = new ListItemWineDetails(0);

    w->startDetailsWine(m_idwine);

    // Delete from memory after closing.
    w->setAttribute(Qt::WA_DeleteOnClose);

    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    DinerApplication::calcCenter(695, 550, screenWidth, screenHeight);
    w->resize(DinerApplication::printCalcCenter().value("width"),
                   DinerApplication::printCalcCenter().value("height"));
    w->move(DinerApplication::printCalcCenter().value("x"),
                 DinerApplication::printCalcCenter().value("y"));
    w->show();

    // Signals and slots.
    QObject::connect(w, SIGNAL(addClicked()), this, SLOT(closeForms()));

    this->disableObjects(true);
}

void MenuWine::closeForms()
{
    this->disableObjects(false);
}

void MenuWine::disableObjects(bool disable)
{
    if(disable) {
        this->ui->frameMenuWineButtons->setDisabled(true);
        this->ui->listWidget->setDisabled(true);
    } else {
        this->ui->frameMenuWineButtons->setDisabled(false);
        this->ui->listWidget->setDisabled(false);
    }
}

void MenuWine::currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(!current) {
        current = previous;
    }

    current->setSelected(true);
    ui->listWidget->setCurrentItem(current);
    ui->listWidget->row(current);

    if(!current->whatsThis().isEmpty() | !current->whatsThis().isNull()) {
        m_idwine = current->whatsThis().toInt();
    }
}

void MenuWine::itemClicked(QListWidgetItem *item)
{
    item->setSelected(true);
    ui->listWidget->setCurrentItem(item);
    ui->listWidget->row(item);

    if(!item->whatsThis().isEmpty() | !item->whatsThis().isNull()) {
        m_idwine = item->whatsThis().toInt();
    }
}
