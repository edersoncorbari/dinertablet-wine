/**
 * @file menufoods.cpp
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

#include "menufoods.h"
#include "ui_menufoods.h"
#include "xmlrpcclient.h"
#include "overlaydialogbox.h"
#include "listorder.h"
#include "listitemdetails.h"
#include "loader.h"
#include "dinerapplication.h"
#include "mainwidget.h"

MenuFoods::MenuFoods(QWidget *parent, int idorder) :
    QWidget(parent), ui(new Ui::MenuFoods), m_iddishe(0), m_idorder(idorder)
{
    // Call ui interface.
    ui->setupUi(this);

    // Read settings.
    this->readSettings("DinerTabletGlobal.conf");

    // Call xml rpc server.
    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "categoria-prato", "getCategorias");

    // Connect slot category and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallCategory()));
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));

    // Set confs listwidget.
    ui->listWidget->setFocusPolicy(Qt::NoFocus);
    ui->listWidget->setIconSize(QSize(48, 48));

    // Check timer image random.
    if(m_timerandomadsimages >= 5000) {
        QTimer *timer = new QTimer(this);
        timer->start(m_timerandomadsimages);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(imageFrameRandom()));
    }

    // Signals and slots.
    QObject::connect(ui->listWidget,
                     SIGNAL(itemClicked(QListWidgetItem*)),
                     this, SLOT(itemClicked(QListWidgetItem*)));
    QObject::connect(ui->listWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(currentItemChanged(QListWidgetItem*,QListWidgetItem*)));
}

MenuFoods::~MenuFoods()
{
    delete ui;
}

void MenuFoods::readSettings(const QString &conf)
{
    QSettings settings(conf, QSettings::IniFormat);

    settings.beginGroup("MenuFoods");

    // Read time random images.
    m_timerandomadsimages = settings.value("timeRandomFoodsImages").toInt();

    settings.endGroup();
}

void MenuFoods::xmlRpcError()
{
    const QString msg = QObject::tr("No communication with the DinerWeb server!");

    OverlayDialogBox* overlaybox = new OverlayDialogBox(this, Loader::wordwrap(msg, 47));

    DinerApplication::calcCenter(510, 170, 1024, 500);
    overlaybox->resize(DinerApplication::printCalcCenter().value("width"),
                       DinerApplication::printCalcCenter().value("height"));
    overlaybox->move(DinerApplication::printCalcCenter().value("x"),
                     DinerApplication::printCalcCenter().value("y"));
    overlaybox->show();
}

void MenuFoods::finishedDownload()
{
    // Set image.
    this->imageFrameRandom();
}

void MenuFoods::xmlRpcCallCategory()
{
    QList<QVariant> data = m_xmlrpc->printValues().toList();
    QVBoxLayout *layout = new QVBoxLayout;

    // Check the return value of rpc is empty.
    if(data.isEmpty()) {
        this->xmlRpcError();
    }

    // Group button.
    this->m_groupbuttonmenu = new QButtonGroup(this);

    for(int i = 0; i < data.size(); ++i) {
        QString name = QString();
        const int active = data[i].toMap().value("ativo").toInt();

        if(active == 1) {
            const int id = data[i].toMap().value("cd_categoria").toInt();
            const QString photo = data[i].toMap().value("foto").toString();

            // Check language.
            if(MainWidget::printLanguage() == "en_US") {
                name = data[i].toMap().value("nome_en").toString();
            } else if(MainWidget::printLanguage() == "pt_BR") {
                name = data[i].toMap().value("nome_br").toString();
            } else if(MainWidget::printLanguage() == "es") {
                name = data[i].toMap().value("nome_es").toString();
            }

            // Download image.
            Loader* dd = new Loader;
            dd->download(photo, "images-dynamic", 0);

            // Connect loader.
            QObject::connect(dd, SIGNAL(finishedDownload()),
                             this, SLOT(finishedDownload()));

            // Create push buttons.
            QPushButton *bt = new QPushButton;

            //bt->setMinimumSize(QSize(180,180));
            //bt->setMaximumSize(QSize(100,100));

            QString sizeF = ("font: bold 14px;");
            bt->setStyleSheet(sizeF);

            bt->setText(name);
            bt->setObjectName(QString::number(id));
            m_buttonlist.append(bt);
            m_groupbuttonmenu->addButton(bt, i);
            layout->addWidget(bt, Qt::AlignHCenter);
            layout->addStretch(1);

            // Store values categories.
            m_categories << data[i];
        }
    }

    // Add vertical layout.
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    layout->addLayout(verticalLayout);

    // Signals and slots.
    QObject::connect(m_groupbuttonmenu, SIGNAL(buttonClicked(int)),
                     this, SLOT(buttonMenuWasClicked(int)));

    // Set layout buttons in frame.
    ui->frameMenuFoodsButtons->setLayout(layout);
}

void MenuFoods::xmlRpcCallDishes()
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
           int identify = data[i].toMap().value("cd_prato").toInt();
           price = data[i].toMap().value("preco").toString();
           QString name = QString();

           if(MainWidget::printLanguage() == "en_US") {
               name = data[i].toMap().value("nome_en").toString();
           } else if(MainWidget::printLanguage() == "pt_BR") {
               name = data[i].toMap().value("nome_br").toString();
           } else if(MainWidget::printLanguage() == "es") {
               name = data[i].toMap().value("nome_es").toString();
           }

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

void MenuFoods::buttonListAddWasClicked(int buttonid)
{
    ui->listWidget->setCurrentRow(buttonid);
    showMyOrder();
}

void MenuFoods::buttonListDetailWasClicked(int buttonid)
{
    ui->listWidget->setCurrentRow(buttonid);
    showDetails();
}

void MenuFoods::buttonMenuWasClicked(int buttonid)
{
    ui->listWidget->clear();

    for(int i = 0; i < m_buttonlist.size(); ++i) {
        const int id = m_categories[i].toMap().value("cd_categoria").toInt();

        if(m_buttonlist[buttonid]->objectName() == QString::number(id)) {
            const QString param = "prato.cd_categoria = " + QString::number(id);

            // Set list parameters.
            QVariantList paraml;
            paraml.append(param);

            // Disconnect slot category and error.
            QObject::disconnect(this, SLOT(xmlRpcCallCategory()));
            QObject::disconnect(this, SLOT(xmlRpcError()));

            // Delete pointer.
            if(m_xmlrpc) {
                delete m_xmlrpc;
            }

            // Call xml rpc server (filter dishes).
            m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                        "prato", "getPratos", paraml);

            // Connect slot dishes and error.
            QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallDishes()));
            QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));

            break;
        }
    }
}

void MenuFoods::imageFrameRandom()
{
    const QStringList strlist = Loader::printListReadDownload();

    // Avoid segmentation fault.
    if(strlist.isEmpty()) {
        return;
    }

    QStringList strlistfilter = strlist.filter(QRegExp("^(images-dynamic/MenuFoods)", Qt::CaseInsensitive));

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

void MenuFoods::setIdOrder(int idorder)
{
    m_idorder = idorder;
}

int MenuFoods::printIdCurrentOrder()
{
    return m_idorder;
}

void MenuFoods::showMyOrder()
{
    ListOrder *w = new ListOrder(0);

    w->startListFoods(m_iddishe);

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

void MenuFoods::showDetails()
{
    ListItemDetails *w = new ListItemDetails(0);

    w->startDetailsFoods(m_iddishe);

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

void MenuFoods::closeForms()
{
    this->disableObjects(false);
}

void MenuFoods::disableObjects(bool disable)
{
    if(disable) {
        this->ui->frameMenuFoodsButtons->setDisabled(true);
        this->ui->listWidget->setDisabled(true);
    } else {
        this->ui->frameMenuFoodsButtons->setDisabled(false);
        this->ui->listWidget->setDisabled(false);
    }
}

void MenuFoods::currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(!current) {
        current = previous;
    }

    current->setSelected(true);
    ui->listWidget->setCurrentItem(current);
    ui->listWidget->row(current);

    if(!current->whatsThis().isEmpty() | !current->whatsThis().isNull()) {
        m_iddishe = current->whatsThis().toInt();
    }
}

void MenuFoods::itemClicked(QListWidgetItem *item)
{
    item->setSelected(true);
    ui->listWidget->setCurrentItem(item);
    ui->listWidget->row(item);

    if(!item->whatsThis().isEmpty() | !item->whatsThis().isNull()) {
        m_iddishe = item->whatsThis().toInt();
    }
}
