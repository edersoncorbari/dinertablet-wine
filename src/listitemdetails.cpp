/**
 * @file listitemdetails.cpp
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

#include "listitemdetails.h"
#include "ui_listitemdetails.h"
#include "xmlrpcclient.h"
#include "overlaydialogbox.h"
#include "picturebrowser.h"
#include "loader.h"
#include "dinerapplication.h"
#include "mainwidget.h"
#include "listorder.h"

ListItemDetails::ListItemDetails(QWidget *parent) :
    QWidget(parent), ui(new Ui::ListItemDetails),
    m_id(0),
    m_countpictureflow(0),
    m_typeform(0)
{
    // Call ui interface.
    ui->setupUi(this);

    // Signals and slots.
    QObject::connect(ui->pushButtonClose, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(add()));
    QObject::connect(ui->pushButtonPictureHideOrShow,
                     SIGNAL(clicked()), this, SLOT(hidePictureFlow()));
}

ListItemDetails::~ListItemDetails()
{
    delete ui;
}

void ListItemDetails::closeEvent(QCloseEvent *event)
{
    this->cancel();
    event->accept();
}

void ListItemDetails::startDetailsFoods(int id)
{
    // Set variables.
    m_typeform = 1;
    m_id= id;
    m_countpictureflow = 0;

    // Call xml rpc server (filter dishe).
    const QString param = "cd_prato = " + QString::number(m_id);

    // Set list parameters.
    QVariantList paraml;
    paraml.append(param);

    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "prato", "getPratos", paraml);

    // Connect slot dishes and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallDetailDishe()));
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
}

void ListItemDetails::startDetailsDrinks(int id)
{
    // Set variables.
    m_typeform = 2;
    m_id= id;
    m_countpictureflow = 0;

    // Call xml rpc server (filter drinks).
    const QString param = "cd_bebida = " + QString::number(m_id);

    // Set list parameters.
    QVariantList paraml;
    paraml.append(param);

    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "bebida", "getBebidas", paraml);

    // Connect slot dishes and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallDetailDrink()));
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
}

void ListItemDetails::xmlRpcCallDetailDishe()
{
    QList<QVariant> data = m_xmlrpc->printValues().toList();

    // Check the return value of rpc is empty.
    if(data.isEmpty()) {
        this->xmlRpcError();
    }

    for(int i = 0; i < data.size(); ++i) {
        const int active = data[i].toMap().value("ativo").toInt();

        if(active == 1) {
           //const int identify = data[i].toMap().value("cd_prato").toInt();
           //const QString name = data[i].toMap().value("nome").toString();
           //const QString price = data[i].toMap().value("preco").toString();
           QString descFood = QString();

           // Check language.
           if(MainWidget::printLanguage() == "en_US") {
               descFood = data[i].toMap().value("descricao_en").toString();
           } else if(MainWidget::printLanguage() == "pt_BR") {
               descFood = data[i].toMap().value("descricao_br").toString();
           } else if(MainWidget::printLanguage() == "es") {
               descFood = data[i].toMap().value("descricao_es").toString();
           }

           ui->labelDescription->setStyleSheet("QLabel { background-color : transparent; "
                                               "color : white; font: bold 18px; }");
           ui->labelDescription->setText(Loader::wordwrap(descFood, 65));
        }
    }

    // Disconnect slot category and error.
    QObject::disconnect(this, SLOT(xmlRpcCallDetailDishe()));
    QObject::disconnect(this, SLOT(xmlRpcError()));

    // Free pointer.
    if(m_xmlrpc) {
        m_xmlrpc = 0;
    }

    // Call xml rpc server (filter photos).
    const QString param = "cd_prato = " + QString::number(m_id);

    // Set list parameters.
    QVariantList paraml;
    paraml.append(param);

    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "foto-prato", "getFotos", paraml);

    // Connect slot dishes and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallPhotos()));
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
}

void ListItemDetails::xmlRpcCallDetailDrink()
{
    QList<QVariant> data = m_xmlrpc->printValues().toList();

    // Check the return value of rpc is empty.
    if(data.isEmpty()) {
        this->xmlRpcError();
    }

    for(int i = 0; i < data.size(); ++i) {
        const int active = data[i].toMap().value("ativo").toInt();

        if(active == 1) {
           QString descFood = QString();

           // Check language.
           if(MainWidget::printLanguage() == "en_US") {
               descFood = data[i].toMap().value("descricao_en").toString();
           } else if(MainWidget::printLanguage() == "pt_BR") {
               descFood = data[i].toMap().value("descricao_br").toString();
           } else if(MainWidget::printLanguage() == "es") {
               descFood = data[i].toMap().value("descricao_es").toString();
           }

           ui->labelDescription->setStyleSheet("QLabel { background-color : transparent; "
                                               "color : white; font: bold 18px; }");
           ui->labelDescription->setText(Loader::wordwrap(descFood, 65));
        }
    }

    // Disconnect slot category and error.
    QObject::disconnect(this, SLOT(xmlRpcCallDetailDrink()));
    QObject::disconnect(this, SLOT(xmlRpcError()));

    // Free pointer.
    if(m_xmlrpc) {
        m_xmlrpc = 0;
    }

    // Call xml rpc server (filter photos).
    const QString param = "cd_bebida = " + QString::number(m_id);

    // Set list parameters.
    QVariantList paraml;
    paraml.append(param);

    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "foto-bebida", "getFotos", paraml);

    // Connect slot dishes and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallPhotos()));
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
}

void ListItemDetails::xmlRpcCallPhotos()
{
    QList<QVariant> data = m_xmlrpc->printValues().toList();

    // Set count pictures.
    this->m_countpictureflow = data.size();

    // Check the return value of rpc is empty.
    if(data.isEmpty()) {
        this->xmlRpcError();
    }

    for(int i = 0; i < data.size(); ++i) {
        int identify = 0;
        QString dirphotos = QString();
        QString dirphotosid = QString();
        int ddtypemenu = 0;

        // Check type form.
        if(m_typeform == 1) {
            identify = data[i].toMap().value("cd_prato").toInt();
            dirphotos = "images-dynamic/foods";
            dirphotosid = dirphotos + "/id-" + QString::number(identify);
            ddtypemenu = 1;
        } else if(m_typeform == 2) {
            identify = data[i].toMap().value("cd_bebida").toInt();
            dirphotos = "images-dynamic/drinks";
            dirphotosid = dirphotos + "/id-" + QString::number(identify);
            ddtypemenu = 2;
        }

        const QString photoPath = data[i].toMap().value("caminho").toString();

        // Store last image for show in picture flow.
        m_imagepictureflow = dirphotosid + "/" + photoPath;

        // Create dirs.
        Loader::createDir(dirphotos);
        Loader::createDir(dirphotosid);

        // Download image.
        Loader* dd = new Loader;
        dd->download(photoPath, dirphotosid, 1, ddtypemenu);

        // Connect loader.
        QObject::connect(dd, SIGNAL(finishedDownload()),
                         this, SLOT(finishedDownload()));
    }
}

void ListItemDetails::xmlRpcError()
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

void ListItemDetails::finishedDownload()
{
    // Decrement variable.
    this->m_countpictureflow--;

    if(this->m_countpictureflow == 0) {
        // Show pictures.
        this->pictureFlow();
    }
}

void ListItemDetails::pictureFlow()
{
    PictureBrowser *w = new PictureBrowser(this);
    w->setSlideSize(QSize(4*40, 5*40));

    const QStringList files = w->findImages(Loader::printLastDownloadCurrentPath());
    QMap<int,QString> map;

    QImage img;
    for(int i = 0; i < (int)files.count(); i++) {
        if(img.load(files[i])) {
            map.insert(i, files[i]);
            w->addSlide(img, map);
        }
    }

    w->setCenterIndex(w->slideCount()/2);
    w->setBackgroundColor(Qt::black);

    // Signals and slots.
    QObject::connect(w, SIGNAL(slideIsClicked()), this, SLOT(changePicture()));

    // @TODO: Check this, transparent not work.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Base, Qt::transparent);
    w->setPalette(palette);
    w->setAttribute(Qt::WA_OpaquePaintEvent, false);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(w);
    ui->widget->setLayout(gridLayout);

    // Set first image.
    this->setBackgroundImage(m_imagepictureflow, QPixmap());
    this->repaint();
}

void ListItemDetails::changePicture()
{
    QString str = PictureFlow::printNameSlide();
    this->setBackgroundImage(str, QPixmap());
    this->repaint();
}

void ListItemDetails::hidePictureFlow()
{
    this->ui->widget->hide();
    this->ui->pushButtonPictureHideOrShow->setText(QObject::tr("Show Photos"));

    // Disconnect slot.
    QObject::disconnect(ui->pushButtonPictureHideOrShow,
                        SIGNAL(clicked()), this, SLOT(hidePictureFlow()));

    // Connect slot.
    QObject::connect(ui->pushButtonPictureHideOrShow,
                     SIGNAL(clicked()), this, SLOT(showPictureFlow()));
}

void ListItemDetails::showPictureFlow()
{
    this->ui->widget->show();
    this->ui->pushButtonPictureHideOrShow->setText(QObject::tr("Hide Photos"));

    // Disconnect slot.
    QObject::disconnect(ui->pushButtonPictureHideOrShow,
                        SIGNAL(clicked()), this, SLOT(showPictureFlow()));

    // Connect slot.
    QObject::connect(ui->pushButtonPictureHideOrShow,
                     SIGNAL(clicked()), this, SLOT(hidePictureFlow()));
}

void ListItemDetails::add()
{
    ListOrder *w = new ListOrder(0);

    if(m_typeform == 1) {
        w->startListFoods(m_id);
    } else if(m_typeform == 2) {
        w->startListDrinks(m_id);
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

    this->close();
    Q_EMIT addClicked();
}

void ListItemDetails::cancel()
{
    this->close();
    Q_EMIT addClicked();
}

void ListItemDetails::setBackgroundImage(const QString &img, const QPixmap &pix)
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
