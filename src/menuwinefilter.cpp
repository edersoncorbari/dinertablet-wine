/**
 * @file menuwinefilter.cpp
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

#include "menuwinefilter.h"
#include "ui_menuwinefilter.h"
#include "xmlrpcclient.h"
#include "overlaydialogbox.h"
#include "listorder.h"
#include "listitemdetails.h"
#include "loader.h"
#include "dinerapplication.h"
#include "mainwidget.h"

// Start static variable and object.
QString MenuWineFilter::m_paramquery = QString();
QString MenuWineFilter::m_paramquerytype = QString();
QString MenuWineFilter::m_paramqueryvarietals = QString();
QString MenuWineFilter::m_paramquerycountries = QString();
QString MenuWineFilter::m_paramqueryregion = QString();
QString MenuWineFilter::m_paramqueryproducer = QString();
QString MenuWineFilter::m_namefilter = QString();
int MenuWineFilter::m_winefilter = 0;

MenuWineFilter::MenuWineFilter(QWidget *parent) :
    QWidget(parent), ui(new Ui::MenuWineFilter)
{
    // Set init variables.
    MenuWineFilter::m_winefilter = 0;

    // Call ui interface.
    ui->setupUi(this);

    // Set confs listwidget.
    ui->listWidget->setFocusPolicy(Qt::NoFocus);
    ui->listWidget->setIconSize(QSize(48, 48));

    // Signals and slots.
    QObject::connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(ui->listWidget,
                     SIGNAL(itemClicked(QListWidgetItem*)),
                     this, SLOT(itemClicked(QListWidgetItem*)));
    QObject::connect(ui->listWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(currentItemChanged(QListWidgetItem*,QListWidgetItem*)));
}

MenuWineFilter::~MenuWineFilter()
{
    delete ui;
}

void MenuWineFilter::closeEvent(QCloseEvent *event)
{
    this->cancel();
    event->accept();
}

void MenuWineFilter::cancel()
{
    this->close();
    //Q_EMIT addClicked();
}

void MenuWineFilter::setFilterType()
{
    MenuWineFilter::m_winefilter = 1;

    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "vinho-tipo", "getTipos");

    // Connect slot category and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallTypeWines()));
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
}

void MenuWineFilter::setFilterVarietals()
{
    MenuWineFilter::m_winefilter = 2;

    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "vinho-uva", "getUvas");

    // Connect slot category and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallTypeWines()));
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
}

void MenuWineFilter::setFilterCountries()
{
    MenuWineFilter::m_winefilter = 3;

    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "vinho-pais", "getPaises");

    // Connect slot category and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallTypeWines()));
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
}

void MenuWineFilter::setFilterRegion()
{
    MenuWineFilter::m_winefilter = 4;

    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "vinho-regiao", "getRegioes");

    // Connect slot category and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallTypeWines()));
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
}

void MenuWineFilter::setFilterProducer()
{
    MenuWineFilter::m_winefilter = 5;

    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "vinho-produtor", "getProdutores");

    // Connect slot category and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallTypeWines()));
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
}

void MenuWineFilter::xmlRpcError()
{
    const QString msg = QObject::tr("Sorry, wine not found! Please try a new search.");

    OverlayDialogBox* overlaybox = new OverlayDialogBox(this, Loader::wordwrap(msg, 47));

    DinerApplication::calcCenter(510, 170, this->width(), this->height());
    overlaybox->resize(DinerApplication::printCalcCenter().value("width"),
                       DinerApplication::printCalcCenter().value("height"));
    overlaybox->move(DinerApplication::printCalcCenter().value("x"),
                     DinerApplication::printCalcCenter().value("y"));
    overlaybox->show();
}

void MenuWineFilter::xmlRpcCallTypeWines()
{
    QList<QVariant> data = m_xmlrpc->printValues().toList();

    // Check the return value of rpc is empty.
    if(data.isEmpty()) {
        this->xmlRpcError();
    }

    // Group buttons.
    this->m_groupbutton = new QButtonGroup(this);

    for(int i = 0; i < data.size(); ++i) {
        int identify = 0;

        if(MenuWineFilter::m_winefilter == 1) {
            identify = data[i].toMap().value("cd_tipo").toInt();
        } else if(MenuWineFilter::m_winefilter == 2) {
            identify = data[i].toMap().value("cd_uva").toInt();
        } else if(MenuWineFilter::m_winefilter == 3) {
            identify = data[i].toMap().value("cd_pais").toInt();
        } else if(MenuWineFilter::m_winefilter == 4) {
            identify = data[i].toMap().value("cd_regiao").toInt();
        } else if(MenuWineFilter::m_winefilter == 5) {
            identify = data[i].toMap().value("cd_produtor").toInt();
        }

        QIcon icon = QIcon::fromTheme("edit-undo");
        QListWidgetItem *item = new QListWidgetItem();
        item->setIcon(icon);
        item->setWhatsThis(QString::number(identify));
        ui->listWidget->addItem(item);

        QString name = QString();

        // Check name filter.
        if((MenuWineFilter::m_winefilter == 1) | (MenuWineFilter::m_winefilter == 3)) {
            if(MainWidget::printLanguage() == "en_US") {
                name = data[i].toMap().value("nome_en").toString();
            } else if(MainWidget::printLanguage() == "pt_BR") {
                name = data[i].toMap().value("nome_br").toString();
            } else if(MainWidget::printLanguage() == "es") {
                name = data[i].toMap().value("nome_es").toString();
            }
        } else if((MenuWineFilter::m_winefilter == 2) | (MenuWineFilter::m_winefilter == 4) |
                  (MenuWineFilter::m_winefilter == 5)) {
            name = data[i].toMap().value("nome").toString();
        }

        // Create push buttons.
        QPushButton *bt = new QPushButton;

        //bt->setMinimumSize(QSize(180,180));
        //bt->setMaximumSize(QSize(100,100));

        QString sizeF = ("font: bold 14px;");
        bt->setStyleSheet(sizeF);

        bt->setText(name);
        bt->setObjectName(QString::number(identify));
        m_buttonlist.append(bt);
        m_groupbutton->addButton(bt, i);

        QHBoxLayout *layout= new QHBoxLayout();
        layout->addWidget(bt, Qt::AlignVCenter);
        layout->addStretch(1);

        QWidget *widget = new QWidget();
        widget->setLayout(layout);
        item->setSizeHint(widget->sizeHint());
        ui->listWidget->setItemWidget(item, widget);

        // Store values.
        m_data << data[i];
    }

    // Signals and slots.
    QObject::connect(m_groupbutton, SIGNAL(buttonClicked(int)),
                     this, SLOT(buttonMenuWasClicked(int)));
}

void MenuWineFilter::buttonMenuWasClicked(int buttonid)
{
    for(int i = 0; i < m_buttonlist.size(); ++i) {

        unsigned int id = 0;

        if(m_winefilter == 1) {
            id = m_data[i].toMap().value("cd_tipo").toInt();
        } else if(m_winefilter == 2) {
            id = m_data[i].toMap().value("cd_uva").toInt();
        } else if(m_winefilter == 3) {
            id = m_data[i].toMap().value("cd_pais").toInt();
        } else if(m_winefilter == 4) {
            id = m_data[i].toMap().value("cd_regiao").toInt();
        } else if(m_winefilter == 5) {
            id = m_data[i].toMap().value("cd_produtor").toInt();
        }

        if(m_buttonlist[buttonid]->objectName() == QString::number(id)) {

            QString name = QString();
            QString query = QString();

            // Check and determine type query.
            if(MenuWineFilter::m_winefilter == 1) {
                m_paramquerytype.clear();
                m_paramquerytype = "vinho.cd_tipo = " + QString::number(id);
            } else if(MenuWineFilter::m_winefilter == 2) {
                m_paramqueryvarietals.clear();
                m_paramqueryvarietals = "vinho.cd_uva = " + QString::number(id);
            } else if(MenuWineFilter::m_winefilter == 3) {
                m_paramquerycountries.clear();
                m_paramquerycountries = "vinho.cd_pais = " + QString::number(id);
            } else if(MenuWineFilter::m_winefilter == 4) {
                m_paramqueryregion.clear();
                m_paramqueryregion = "vinho.cd_regiao = " + QString::number(id);
            } else if(MenuWineFilter::m_winefilter == 5) {
                m_paramqueryproducer.clear();
                m_paramqueryproducer = "vinho.cd_produtor = " + QString::number(id);
            }

            // Check name filter.
            if((MenuWineFilter::m_winefilter == 1) | (MenuWineFilter::m_winefilter == 3)) {
                if(MainWidget::printLanguage() == "en_US") {
                    MenuWineFilter::m_namefilter = m_data[i].toMap().value("nome_en").toString();
                } else if(MainWidget::printLanguage() == "pt_BR") {
                    MenuWineFilter::m_namefilter = m_data[i].toMap().value("nome_br").toString();
                } else if(MainWidget::printLanguage() == "es") {
                    MenuWineFilter::m_namefilter = m_data[i].toMap().value("nome_es").toString();
                }
            } else if((MenuWineFilter::m_winefilter == 2) | (MenuWineFilter::m_winefilter == 4) |
                      (MenuWineFilter::m_winefilter == 5)) {
                MenuWineFilter::m_namefilter = m_data[i].toMap().value("nome").toString();
            }

            Q_EMIT buttonClicked();
            break;
        }
    }

    this->close();
}

void MenuWineFilter::currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(!current) {
        current = previous;
    }

    current->setSelected(true);
    ui->listWidget->setCurrentItem(current);
    ui->listWidget->row(current);
}

void MenuWineFilter::itemClicked(QListWidgetItem *item)
{
    item->setSelected(true);
    ui->listWidget->setCurrentItem(item);
    ui->listWidget->row(item);
}

QString MenuWineFilter::printQueryFilter()
{
    while(true) {
        // Test filter type.
        if((!m_paramquerytype.isEmpty() & !m_paramqueryvarietals.isEmpty()) |
                (!m_paramquerytype.isEmpty() & !m_paramquerycountries.isEmpty()) |
                (!m_paramquerytype.isEmpty() & !m_paramqueryregion.isEmpty()) |
                (!m_paramquerytype.isEmpty() & !m_paramqueryproducer.isEmpty()) ) {
            m_paramquery += " AND ";
            break;
        }

        // Test filter varietals.
        if((!m_paramqueryvarietals.isEmpty() & !m_paramquerytype.isEmpty()) |
                (!m_paramqueryvarietals.isEmpty() & !m_paramquerycountries.isEmpty()) |
                (!m_paramqueryvarietals.isEmpty() & !m_paramqueryregion.isEmpty()) |
                (!m_paramqueryvarietals.isEmpty() & !m_paramqueryproducer.isEmpty()) ) {
            m_paramquery += " AND ";
            break;
        }

        // Test filter countries.
        if((!m_paramquerycountries.isEmpty() & !m_paramquerytype.isEmpty()) |
                (!m_paramquerycountries.isEmpty() & !m_paramqueryvarietals.isEmpty()) |
                (!m_paramquerycountries.isEmpty() & !m_paramqueryregion.isEmpty()) |
                (!m_paramquerycountries.isEmpty() & !m_paramqueryproducer.isEmpty()) ) {
            m_paramquery += " AND ";
            break;
        }

        // Test filter region.
        if( (!m_paramqueryregion.isEmpty() & !m_paramquerytype.isEmpty()) |
                (!m_paramqueryregion.isEmpty() & !m_paramqueryvarietals.isEmpty()) |
                (!m_paramqueryregion.isEmpty() & !m_paramquerycountries.isEmpty()) |
                (!m_paramqueryregion.isEmpty() & !m_paramqueryproducer.isEmpty()) ) {
            m_paramquery += " AND ";
            break;
        }

        // Test filter producer.
        if( (!m_paramqueryproducer.isEmpty() & !m_paramquerytype.isEmpty()) |
                (!m_paramqueryproducer.isEmpty() & !m_paramqueryvarietals.isEmpty()) |
                (!m_paramqueryproducer.isEmpty() & !m_paramquerycountries.isEmpty()) |
                (!m_paramqueryproducer.isEmpty() & !m_paramqueryregion.isEmpty()) ) {
            m_paramquery += " AND ";
            break;
        }

        break;
    }


    if(MenuWineFilter::m_winefilter == 1) {
        m_paramquery += m_paramquerytype;
    } else if(MenuWineFilter::m_winefilter == 2) {
        m_paramquery += m_paramqueryvarietals;
    } else if(MenuWineFilter::m_winefilter == 3) {
        m_paramquery += m_paramquerycountries;
    } else if(MenuWineFilter::m_winefilter == 4) {
        m_paramquery += m_paramqueryregion;
    } else if(MenuWineFilter::m_winefilter == 5) {
        m_paramquery += m_paramqueryproducer;
    }

    return MenuWineFilter::m_paramquery;
}

void MenuWineFilter::clearQueryFilter()
{
    MenuWineFilter::m_paramquery.clear();
    MenuWineFilter::m_paramquerytype.clear();
    MenuWineFilter::m_paramqueryvarietals.clear();
    MenuWineFilter::m_paramquerycountries.clear();
    MenuWineFilter::m_paramqueryregion.clear();
    MenuWineFilter::m_paramqueryproducer.clear();
}

QString MenuWineFilter::printNameFilterSelected()
{
    if(MenuWineFilter::m_namefilter.isEmpty()) {
        return QString();
    }

    return MenuWineFilter::m_namefilter;
}

void MenuWineFilter::clearNameFilterSelected()
{
    MenuWineFilter::m_namefilter.clear();
}

void MenuWineFilter::setBackgroundImage(const QString &img, const QPixmap &pix)
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
