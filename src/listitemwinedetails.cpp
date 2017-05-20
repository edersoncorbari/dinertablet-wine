/**
 * @file listitemwinedetails.cpp
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

#include "listitemwinedetails.h"
#include "ui_listitemwinedetails.h"
#include "xmlrpcclient.h"
#include "overlaydialogbox.h"
#include "picturebrowser.h"
#include "loader.h"
#include "dinerapplication.h"
#include "mainwidget.h"
#include "listorder.h"

#include "thirdpartycodes/imgzoom.h"

ListItemWineDetails::ListItemWineDetails(QWidget *parent) :
    QWidget(parent), ui(new Ui::ListItemWineDetails),
    m_id(0)
{
    // Call ui interface.
    ui->setupUi(this);

    // Set background image.
    this->setBackgroundImage(":/images/wine-details.jpg", QPixmap());

    // Set label style.
    QString style = ( "QLabel { background-color : transparent; "
                      "color : white; }" );
    ui->labelCountry->setStyleSheet(style);
    ui->labelRegion->setStyleSheet(style);
    ui->labelProducer->setStyleSheet(style);
    ui->labelType->setStyleSheet(style);
    ui->labelHarvest->setStyleSheet(style);
    ui->labelVarietals->setStyleSheet(style);
    ui->labelVolume->setStyleSheet(style);
    ui->labelAlcoholContent->setStyleSheet(style);

    // Set read only.
    ui->textBrowser->setReadOnly(true);

    // Signals and slots.
    QObject::connect(ui->pushButtonClose, SIGNAL(clicked()), this, SLOT(cancel()));
    QObject::connect(ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(add()));
}

ListItemWineDetails::~ListItemWineDetails()
{
    delete ui;
}

void ListItemWineDetails::closeEvent(QCloseEvent *event)
{
    this->cancel();
    event->accept();
}

void ListItemWineDetails::startDetailsWine(int id)
{
    // Set variables.
    //m_typeform = 1;
    m_id= id;

    // Call xml rpc server (filter wine).
    const QString param = "cd_vinho = " + QString::number(m_id);

    // Set list parameters.
    QVariantList paraml;
    paraml.append(param);

    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "vinho", "getVinhos", paraml);

    // Connect slot dishes and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallDetailWine()));
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));

}

void ListItemWineDetails::xmlRpcCallDetailWine()
{
    QList<QVariant> data = m_xmlrpc->printValues().toList();

    // Check the return value of rpc is empty.
    if(data.isEmpty()) {
        this->xmlRpcError();
    }

    for(int i = 0; i < data.size(); ++i) {
        const int active = data[i].toMap().value("ativo").toInt();

        if(active == 1) {
           //const int identify = data[i].toMap().value("cd_vinho").toInt();
           const QString name = data[i].toMap().value("nome").toString();
           //const QString price = data[i].toMap().value("preco").toString();
           const QString region = data[i].toMap().value("nome_regiao").toString();
           const QString producer = data[i].toMap().value("nome_produtor").toString();
           const QString harvest = data[i].toMap().value("safra").toString();
           const QString varietals = data[i].toMap().value("nome_uva").toString();
           const QString volume = data[i].toMap().value("volume").toString();
           const QString volumeAc = data[i].toMap().value("volume_sigla").toString();
           const QString alcoholcontent = data[i].toMap().value("graduacao").toString();

           QString descWine = QString();
           QString country = QString();
           QString type = QString();

           // Set font and style name label.
           QFont fontLB("Great Vibes", 40, QFont::Bold);
           ui->labelWineName->setText(name);
           ui->labelWineName->setStyleSheet("QLabel { background-color : transparent; color: white; }");
           ui->labelWineName->setFont(fontLB);

           // Check language.
           if(MainWidget::printLanguage() == "en_US") {
               descWine = data[i].toMap().value("descricao_en").toString();
               country = data[i].toMap().value("pais_en").toString();
               type = data[i].toMap().value("tipo_en").toString();
           } else if(MainWidget::printLanguage() == "pt_BR") {
               descWine = data[i].toMap().value("descricao_br").toString();
               country = data[i].toMap().value("pais_br").toString();
               type = data[i].toMap().value("tipo_br").toString();
           } else if(MainWidget::printLanguage() == "es") {
               descWine = data[i].toMap().value("descricao_es").toString();
               country = data[i].toMap().value("pais_es").toString();
               type = data[i].toMap().value("tipo_es").toString();
           }

           // Label sytle.
           QString style = ("QLabel { background-color : transparent; "
                            "color : white; font: bold 16px; }" );

           ui->labelCountryDesc->setText(country);
           ui->labelCountryDesc->setStyleSheet(style);

           ui->labelRegionDesc->setText(region);
           ui->labelRegionDesc->setStyleSheet(style);

           ui->labelProducerDesc->setText(producer);
           ui->labelProducerDesc->setStyleSheet(style);

           ui->labelTypeDesc->setText(type);
           ui->labelTypeDesc->setStyleSheet(style);

           ui->labelHarvestDesc->setText(harvest);
           ui->labelHarvestDesc->setStyleSheet(style);

           ui->labelVarietalsDesc->setText(varietals);
           ui->labelVarietalsDesc->setStyleSheet(style);

           ui->labelVolumeDesc->setText(volume + volumeAc);
           ui->labelVolumeDesc->setStyleSheet(style);

           ui->labelAlcoholContentDesc->setText(alcoholcontent);
           ui->labelAlcoholContentDesc->setStyleSheet(style);

           QString styleT = ("QTextBrowser { background-color : transparent; "
                             "color : white; font: bold 16px;}");

           ui->textBrowser->setText(descWine);
           ui->textBrowser->setStyleSheet(styleT);
        }
    }

    // Free pointer.
    if(m_xmlrpc) {
        m_xmlrpc = 0;
    }

    // Call xml rpc server (filter photos).
    const QString param = "cd_vinho = " + QString::number(m_id);

    // Set list parameters.
    QVariantList paraml;
    paraml.append(param);

    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "vinho-foto", "getFotos", paraml);

    // Connect slot dishes and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallPhotos()));
    QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
}

void ListItemWineDetails::xmlRpcCallPhotos()
{
    QList<QVariant> data = m_xmlrpc->printValues().toList();

    qDebug() << data;

    // Check the return value of rpc is empty.
    if(data.isEmpty()) {
        this->xmlRpcError();
    }

    for(int i = 0; i < data.size(); ++i) {
        int identify = data[i].toMap().value("cd_vinho").toInt();
        const QString dirphotos = "images-dynamic/wines";
        const QString dirphotosid = dirphotos + "/id-" + QString::number(identify);

        const QString idp = data[i].toMap().value("cd_foto").toString();
        const QString photoExt = data[i].toMap().value("extensao").toString();

        const QString photoName = idp + "." + photoExt;
        m_photo = dirphotosid + "/" + photoName;

        // Create dirs.
        Loader::createDir(dirphotos);
        Loader::createDir(dirphotosid);

        // Download image.
        Loader* dd = new Loader;
        dd->download(photoName, dirphotosid, 1, 3);

        // Connect loader.
        QObject::connect(dd, SIGNAL(finishedDownload()),
                         this, SLOT(finishedDownload()));
    }

}

void ListItemWineDetails::xmlRpcError()
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

void ListItemWineDetails::finishedDownload()
{
    ImgZoom *w = new ImgZoom(m_photo);
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(w);
    ui->widgetImg->setLayout(gridLayout);
}

void ListItemWineDetails::add()
{
    ListOrder *w = new ListOrder(0);

    w->startListWine(m_id);

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

void ListItemWineDetails::cancel()
{
    this->close();
    Q_EMIT addClicked();
}

void ListItemWineDetails::setBackgroundImage(const QString &img, const QPixmap &pix)
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
