/**
 * @file loader.cpp
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

#include "loader.h"
#include "dinerapplication.h"
#include "filedownloader.h"
#include "mainwidget.h"
#include "xmlrpcclient.h"
#include "loading.h"

// Qt QuaZIP API
#include "quazip.h"
#include "quazipfile.h"

#include <QFile>
#include <QDir>

#include <QString>
#include <QSettings>
#include <QTimer>
#include <QDesktopWidget>
#include <QApplication>
#include <QDataStream>

// Initialization of static variables and objects.
static DinerApplication *staticapp;
QString Loader::m_surl = QString();
QString Loader::m_servername = QString();
QString Loader::m_port = QString();
QString Loader::m_path = QString();
QList<QString> Loader::m_downloadreadlist = QList<QString>();
QVariantList Loader::m_restaurantinfo = QVariantList();
bool Loader::m_connection = false;
Loader* Loader::instance = 0;

Loader* Loader::getInstance()
{
    if(instance == 0){
        instance = new Loader;
    }
    return instance;
}

Loader::Loader(QObject *parent)
    : QObject(parent)
{
    // First, read settings.
    this->readSettings();

    // Test connection diner server.
    QHostInfo::lookupHost(Loader::m_servername, this, SLOT(connectionUp(QHostInfo)));
}

Loader::~Loader()
{
}

void Loader::download(const QString namefile, const QString path, int typefile, int typemenu)
{
    if(namefile.isEmpty()) {
        return;
    }

    if(!path.isEmpty()) {
        //Loader::m_path = QDir::currentPath() + "/" + path;
        Loader::m_path = DinerApplication::printPathDirConfig() + "/" + path;

    }

    // Save name image.
    m_downloadnamefile = namefile;

    if(typemenu == 0) {
        QUrl confUrl(m_url + "/assets/tablet/images-dynamic/" + namefile);
        this->m_downloader = new FileDownloader(confUrl, this);
    } else if(typemenu == 1) {
        QUrl confUrl(m_url + "/assets/tablet/images-dynamic/foods/" + namefile);
        this->m_downloader = new FileDownloader(confUrl, this);
    } else if(typemenu == 2) {
        QUrl confUrl(m_url + "/assets/tablet/images-dynamic/drinks/" + namefile);
        this->m_downloader = new FileDownloader(confUrl, this);
    } else if(typemenu == 3) {
        QUrl confUrl(m_url + "/assets/tablet/images-dynamic/wines/" + namefile);
        this->m_downloader = new FileDownloader(confUrl, this);
    }

    if(typefile == 0) {
        QObject::connect(this->m_downloader,
                         SIGNAL(downloaded()), SLOT(readDownload()));
    } else if(typefile == 1) {
        QObject::connect(this->m_downloader,
                         SIGNAL(downloaded()), SLOT(readDownloadPictureFlow()));
    }
}

void Loader::readDownload()
{
    const QString defaultDir = DinerApplication::printPathDirConfig();

    QPixmap image;
    image.loadFromData(this->m_downloader->downloadedData());

    if(!Loader::m_path.isEmpty()) {
        // Change dir app path to save image..
        QDir::setCurrent(Loader::m_path);
        image.save(m_downloadnamefile);
    }

    // Return the default path app.
    QDir::setCurrent(defaultDir);

    if(!m_downloadnamefile.isEmpty()) {
        // Store name image.
        Loader::m_downloadreadlist << "images-dynamic/" + m_downloadnamefile;
        Q_EMIT finishedDownload();
    }
}

void Loader::readDownloadPictureFlow()
{
    //const QString defaultDir = QCoreApplication::applicationDirPath();
    const QString defaultDir = DinerApplication::printPathDirConfig();

    QPixmap image;
    image.loadFromData(this->m_downloader->downloadedData());

    if(!Loader::m_path.isEmpty()) {
        // Change dir app path to save image..
        QDir::setCurrent(Loader::m_path);
        image.save(m_downloadnamefile);
    }

    // Return the default path app.
    QDir::setCurrent(defaultDir);

    if(!m_downloadnamefile.isEmpty()) {
        Q_EMIT finishedDownload();
    }
}

QList<QString> Loader::printListReadDownload()
{
    return Loader::m_downloadreadlist;
}

QString Loader::printLastDownloadCurrentPath()
{
    return Loader::m_path;
}

void Loader::connectionUp(QHostInfo info)
{
    if(info.error() != QHostInfo::NoError) {
        //qDebug() << "Lookup failed:" << info.errorString();
        Loader::m_connection = false;
        return;
    }

    foreach(const QHostAddress &address, info.addresses()) {
        if(address.toString().isEmpty()) {
            //qDebug() << "Found address:" << address.toString();
        }
        Loader::m_connection = true;
    }
}

bool Loader::connectionOk()
{
    return Loader::m_connection;
}

void Loader::start(DinerApplication *app)
{
    // Show loading.
    Loading::getInstance()->showLoading();

    // Copy instance in static app.
    staticapp = app;

    // Remove old download files and images.
    Loader::removeDownloadFiles();

    // Trigger single shot.
    QTimer::singleShot(0, this, SLOT(downloadGlobalConfFile()));
    QTimer::singleShot(1000, this, SLOT(downloadImages()));
}

void Loader::downloadGlobalConfFile()
{
    qDebug() << "Single Shot 1";
    QUrl confUrl(m_url + "/assets/tablet/DinerTabletGlobal.conf");
    this->m_downloader = new FileDownloader(confUrl, this);
    QObject::connect(this->m_downloader, SIGNAL(downloaded()), SLOT(readGlobalConfFile()));

    // Get information restaurant.
    this->xmlRpcGetRestaurantInfo();
}

void Loader::downloadImages()
{
    qDebug() << "Single Shot 2";
    QUrl imageUrl(m_url + "/assets/tablet/images-static.zip");
    this->m_downloader = new FileDownloader(imageUrl, this);
    QObject::connect(this->m_downloader, SIGNAL(downloaded()), SLOT(readDownloadImages()));
}

void Loader::readGlobalConfFile()
{
    QByteArray data = this->m_downloader->downloadedData();

    QFile file("DinerTabletGlobal.conf");
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();
}

void Loader::readDownloadImages()
{
    QByteArray data = this->m_downloader->downloadedData();

    QFile file("images-static.zip");
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();

    QDir dir1("images-static");
    if(!dir1.exists()) {
        dir1.mkpath(".");
    }

    QDir dir2("images-dynamic");
    if(!dir2.exists()) {
        dir2.mkpath(".");
    }

    bool unzip = Loader::unzip("images-static.zip","images-static");

    if(!unzip) {
        qDebug() << "Error zip...";
    }

    // Start main widget.
    this->startMainWidget();
}

bool Loader::createDir(const QString path, const QString dirname)
{
    QString currPath = QDir::currentPath();

    if(!path.isEmpty()) {
        currPath = QDir::currentPath() + "/" + path;
    }

    const QString createDir = currPath + "/" + dirname;
    const QDir dir(createDir);

    if(!dir.exists()) {
        dir.mkdir(createDir);
        return true;
    }

    return false;
}

void Loader::readSettings()
{
    QSettings settings("DinerTabletLocal.conf", QSettings::IniFormat);

    settings.beginGroup("ConfigDialog");

    // Check protocol.
    QString protocolLocalServer = settings.value("protocolLocalServer").toString();
    if(!protocolLocalServer.isEmpty()) {
        if(protocolLocalServer == "http") {
            m_url = "http://";
        } else if(protocolLocalServer == "https") {
            m_url = "https://";
        }
    }

    // Check port.
    QString portLocalServer = settings.value("portLocalServer").toString();
    if(!portLocalServer.isEmpty()) {
        if(portLocalServer == "80") {
            Loader::m_port = "80";
        } else if(portLocalServer == "8080") {
            Loader::m_port = "8080";
        }
    }

    // Check ip server.
    QString ipLocalServer = settings.value("ipLocalServer").toString();
    if(!ipLocalServer.isEmpty() ) {
        Loader::m_servername = ipLocalServer;
        m_url += (ipLocalServer + ":" + m_port);
    }

    settings.endGroup();

    // Store value in static url.
    Loader::m_surl = (this->m_url + ":" + m_port);
}

int Loader::readSettingsAdsIDLE()
{
    QSettings settings("DinerTabletGlobal.conf", QSettings::IniFormat);

    settings.beginGroup("AdvertisingNews");

    // Check time ads IDLE.
    unsigned int timeShowAdsIDLE = settings.value("timeShowAdsIDLE").toInt();

    settings.endGroup();

    return timeShowAdsIDLE;
}

void Loader::startMainWidget()
{
    qDebug() << "Single Shot 3";

    // Create static Main Widget base app.
    static MainWidget *w = new MainWidget;

    // Delete from memory after closing.
    w->setAttribute(Qt::WA_DeleteOnClose);

    QDesktopWidget *desktop = QApplication::desktop();

    DinerApplication::calcCenter(1024, 768, desktop->width(), desktop->height());
    w->resize(DinerApplication::printCalcCenter().value("width"),
                   DinerApplication::printCalcCenter().value("height"));
    w->move(DinerApplication::printCalcCenter().value("x"),
                 DinerApplication::printCalcCenter().value("y"));

    // Check IDLE time.
    if(this->readSettingsAdsIDLE() >= 5000) {
        // Set time IDLE app.
        staticapp->setUserIdle(this->readSettingsAdsIDLE());

        // Connect slot IDLE.
        w->connect(staticapp, SIGNAL(idleCalled()), SLOT(callAdvertisingNews()));
    }

    w->setWindowTitle("Diner Tablet");
    w->show();

    // Hide loading.
    Loading::getInstance()->hideLoading();
}

bool Loader::removeDownloadFiles()
{
    bool imgzip = QFile::remove("images-static.zip");

    if(!imgzip) {
        qDebug() << "Error remove images-static.zip...";
        return false;
    }

    QDir imagesStatic("images-static");

    if(!imagesStatic.removeRecursively()) {
        qDebug() << "Error remove dir images-static...";
        return false;
    }

    QDir imagesDynamic("images-dynamic");

    if(!imagesDynamic.removeRecursively()) {
        qDebug() << "Error remove dir images-dynamic...";
        return false;
    }

    bool conf = QFile::remove("DinerTabletGlobal.conf");

    if(!conf) {
        qDebug() << "Error remove global conf file...";
        return false;
    }

    const QString path = QDir::currentPath();
    QDir dir(path);
    dir.setNameFilters(QStringList() << "*.jpg");
    dir.setFilter(QDir::Files);
    foreach(QString dirFile, dir.entryList()) {
        dir.remove(dirFile);
    }

    return true;
}

QString Loader::printUrl()
{
    return Loader::m_surl;
}

QString Loader::printDinerServerName()
{
    return Loader::m_servername;
}

QString Loader::printDinerServerPort()
{
    return Loader::m_port;
}

QString Loader::printDinerServerNameAndPort()
{
    const QString server = Loader::printDinerServerName() + ":" +
                           Loader::printDinerServerPort();
    return server;
}


bool Loader::serializeRecordData(const QString filename, QMap<int, int> data)
{
    QMap<int, int> localdata = data;

    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite)){
        qDebug() << "Could not open: " << filename;
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_3);

    out << localdata;

    file.flush();
    file.close();

    return true;
}

QMap<int, int> Loader::serializeExtractDataMap(const QString filename)
{
    QMap<int, int> localdata;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open: " << filename;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_3);

    in >> localdata;

    file.flush();
    file.close();

    return localdata;
}

bool Loader::serializeRecordData(const QString filename, QList<QVariant> data)
{
    QList<QVariant> localdata = data;

    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite)){
        qDebug() << "Could not open: " << filename;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_3);

    out << localdata;

    file.flush();
    file.close();

    return true;
}

QList<QVariant> Loader::serializeExtractData(const QString filename)
{
    QList<QVariant> localdata;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open: " << filename;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_3);

    in >> localdata;

    file.flush();
    file.close();

    return localdata;
}

bool Loader::unzip(const QString &filePath, const QString &extDirPath, const QString &singleFileName)
{
    QuaZip zip(filePath);

    if(!zip.open( QuaZip::mdUnzip)) {
      qWarning("testRead(): zip.open(): %d", zip.getZipError());
      return false;
    }

    zip.setFileNameCodec("IBM866");

    QuaZipFileInfo info;
    QuaZipFile file(&zip);

    QFile out;
    QString name;
    char c;

    for(bool more = zip.goToFirstFile(); more; more = zip.goToNextFile()) {

        if(!zip.getCurrentFileInfo(&info)) {
            qWarning("testRead(): getCurrentFileInfo(): %d\n", zip.getZipError());
            return false;
        }

        if(!singleFileName.isEmpty()) {
            if(!info.name.contains(singleFileName)) {
                continue;
            }
        }

        if(!file.open(QIODevice::ReadOnly)) {
            qWarning("testRead(): file.open(): %d", file.getZipError());
            return false;
        }

        name = QString("%1/%2").arg(extDirPath).arg(file.getActualFileName());

        if(file.getZipError() != UNZ_OK) {
            qWarning("testRead(): file.getFileName(): %d", file.getZipError());
            return false;
        }

        out.setFileName(name);

        // This will fail if "name" contains subdirectories, but we don't mind that.
        out.open(QIODevice::WriteOnly);

        // Slow like hell (on GNU/Linux at least), but it is not my fault.
        // Not ZIP/UNZIP package's fault either. The slowest thing here is out.putChar(c).
        while(file.getChar(&c)) {
            out.putChar(c);
        }

        out.close();

        if(file.getZipError() != UNZ_OK) {
            qWarning("testRead(): file.getFileName(): %d", file.getZipError());
            return false;
        }

        if(!file.atEnd()) {
            qWarning("testRead(): read all but not EOF");
            return false;
        }

        file.close();

        if( file.getZipError() != UNZ_OK ) {
            qWarning("testRead(): file.close(): %d", file.getZipError());
            return false;
        }
    }

    zip.close();

    if( zip.getZipError() != UNZ_OK ) {
        qWarning("testRead(): zip.close(): %d", zip.getZipError());
        return false;
    }

    return true;
}

QString Loader::wordwrap(QString text, const unsigned int size)
{
    if(text.length() <= static_cast<signed>(size)) {
        return text;
    }

    QString aux = text;
    aux.truncate(size);

    int break_line_pos = aux.indexOf('\n');

    if(break_line_pos != -1) {
        aux.truncate(break_line_pos + 1);
        text = text.right(text.length() - break_line_pos - 1);
        return aux + wordwrap(text, size);
    }

    int empty_pos = aux.lastIndexOf(' ');

    if(empty_pos != -1) {
        aux.truncate(empty_pos + 1);
        text = text.right(text.length() - empty_pos - 1);
    } else {
        text = text.right(text.length() - size);
    }

    return aux + "\n" + wordwrap(text, size);
}

void Loader::xmlRpcGetRestaurantInfo()
{
    // Call xml rpc server.
    m_xmlrpc = new XmlRpcClient(this, Loader::printDinerServerNameAndPort(),
                                "restaurante", "getRestaurantes");

    // Connect slot category and error.
    QObject::connect(m_xmlrpc, SIGNAL(response()), this, SLOT(xmlRpcCallRestaurant()));
    //QObject::connect(m_xmlrpc, SIGNAL(responseError()), this, SLOT(xmlRpcError()));
}

void Loader::xmlRpcCallRestaurant()
{
    QVariantList data = m_xmlrpc->printValues().toList();
    Loader::m_restaurantinfo = data;
}

QVariantList Loader::printRestaurantInfo()
{
    return Loader::m_restaurantinfo;
}

bool Loader::removeFile(const QString filename)
{
    bool rm = QFile::remove(filename);

    if(!rm) {
        qWarning("Error remove file.");
        return false;
    }

    return true;
}
