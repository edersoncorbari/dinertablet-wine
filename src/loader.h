/**
 * @file loader.h
 *
 * Definitions for an diner-tablet.
 *
 * MOBILE-APP - Project DinerTablet.
 *
 * Copyright (c) 2014 BlueSalute Company Ltda.
 *
 * @author Ederson Moura - <ederson.moura@bluesalute.com.br>
 *
 * $Id: Exp$
 */

#ifndef LOADER_H
#define LOADER_H

#include <QObject>
#include <QHostInfo>
#include <QList>
#include <QVariant>
#include <QDate>
#include <QDateTime>
#include <QTime>

// Override!
class FileDownloader;
class DinerApplication;
class XmlRpcClient;

/**
 * @class Loader
 *
 * @brief Used to make the local configuration of the tablet.
 */
class Loader : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent - Widget object.
     */
    explicit Loader(QObject *parent = 0);

    /// Destructor.
    ~Loader();

    /**
     * @brief Singleton Loader class get instance.
     *
     * @return The static Loader.
     */
    static Loader* getInstance();

    /**
     * @brief You download a file or image.
     * @param namefile - The name file.
     * @param path - The path save files.
     * @param typefile - Type of image file or text.
     * @param typemenu - Is menu foods, drinks, wine, etc.
     */
    void download(const QString namefile = QString(),
                  const QString path = QString(),
                  int typefile = 0,
                  int typemenu = 0);

    /**
     * @brief Print list name file read in download.
     * @return The name files.
     */
    static QList<QString> printListReadDownload();

    /**
     * @brief Start process aplication.
     *
     * @param app - The reference DinerApplication.
     */
    void start(DinerApplication *app);

    /**
     * @brief Checks the connection to the server.
     * @return Returns true if ok false if not.
     */
    static bool connectionOk();

    /**
     * @brief Print the URL diner server.
     * @return Return url server.
     */
    static QString printUrl();

    /**
     * @brief Print diner server name.
     * @return Diner server name.
     */
    static QString printDinerServerName();

    /**
     * @brief Print diner server port.
     * @return
     */
    static QString printDinerServerPort();

    /**
     * @brief Print diner server name and port.
     * @return Diner server name and port.
     */
    static QString printDinerServerNameAndPort();

    /**
     * @brief Remove downloaded file that are not needed.
     * @return Returns true if the files were successfully removed,
     * otherwise it returns false.
     */
    static bool removeDownloadFiles();

    /**
     * @brief Serializes and saves a file in the app directory.
     *
     * @param filename - The name file.
     * @param data - The variant data.
     * @return Returns true on success, otherwise false
     */
    static bool serializeRecordData(const QString filename, QList<QVariant> data);

    /**
     * @brief Extract data from serialized file that was saved.
     *
     * @param filename - The name file.
     * @return Returns the saved data.
     */
    static QList<QVariant> serializeExtractData(const QString filename);

    /**
     * @brief Serializes and saves a file in the app directory.
     *
     * @param filename - The name file.
     * @param data - The map integer data.
     * @return Returns true on success, otherwise false.
     */
    static bool serializeRecordData(const QString filename, QMap<int, int> data);

    /**
     * @brief Extract data map from serialized file that was saved.
     *
     * @param filename - The name file.
     * @return Returns the saved data.
     */
    static QMap<int, int> serializeExtractDataMap(const QString filename);

    /**
     * @brief Decompress a zip file.
     *
     * @param filePath - The file path.
     * @param extDirPath - The dir path.
     * @param singleFileName - The single file name.
     * @return Returns true on success, otherwise it returns false.
     */
    static bool unzip(const QString &filePath, const QString &extDirPath,
                      const QString &singleFileName = QString("") );

    /**
     * Wraps a string to a given number of characters using "\n" as
     * string break character.
     *
     * @param text - The string to be wrapepd.
     * @param size - The number of caracters.
     * @return Returns a string with @a text wrapped at the column number
     * specified by the @a size. The line is broken using the \n character.
     */
    static QString wordwrap(QString text, const unsigned int size);

    /**
     * @brief Create the one directory.
     * @param path - Path where createing directory.
     * @param dirname - The name directory.
     */
    static bool createDir(const QString path = QString(),
                          const QString dirname = QString());

    /**
     * @brief Print the last dir path download.
     * @return Last current path.
     */
    static QString printLastDownloadCurrentPath();

    /**
     * @brief Print restaurant information.
     * @return Restaunt infos.
     */
    static QVariantList printRestaurantInfo();

    /**
     * @brief Remove a file.
     *
     * @param filename - Name file.
     * @return True if remove success, other false.
     */
    static bool removeFile(const QString filename = QString());

Q_SIGNALS:
    /**
     * @brief Sends this signal when the download is finished.
     */
    void finishedDownload();

private Q_SLOTS:
    /**
     * @brief Read slot download.
     */
    void readDownload();

    /**
     * @brief Read slot download for PictureFlow.
     */
    void readDownloadPictureFlow();

    /**
     * @brief Download the file from the global tablet.
     */
    void downloadGlobalConfFile();

    /**
     * @brief Download the file zip images.
     */
    void downloadImages();

    /**
     * @brief Reads the images coming from the download.
     */
    void readDownloadImages();

    /**
     * @brief Used to test if the server is found and
     * connection is okay.
     *
     * @param info - Host info.
     */
    void connectionUp(QHostInfo info);

    /**
     * @brief Read global conf file the tablet.
     */
    void readGlobalConfFile();

    /**
     * @brief Start the Diner MainWidget.
     */
    void startMainWidget();

    /**
     * @brief Call method to get the restaurant
     * RPC Server.
     */
    void xmlRpcCallRestaurant();

protected:
    /**
     * @brief Reading the configuration file of the tablet.
     */
    void readSettings();

    /**
     * @brief Get XML RPC restaurant data.
     */
    void xmlRpcGetRestaurantInfo();

    /**
     * @brief Reading the configuration global Ads IDLE.
     * @return Time IDLE.
     */
    int readSettingsAdsIDLE();

    /// Pointer class for singleton instance.
    static Loader *instance;

private:
    /// Used to download the some file or image.
    FileDownloader *m_downloader;

    /// Store the server name or ip.
    static QString m_servername;

    /// Store the server port.
    static QString m_port;

    /// Store some URL to download.
    QString m_url;

    /// Store static some URL to download.
    static QString m_surl;

    /// Test connection is good or not.
    static bool m_connection;

    /// Store download name file.
    QString m_downloadnamefile;

    /// Store list download files.
    static QList<QString> m_downloadreadlist;

    /// Store list restaurant info.
    static QVariantList m_restaurantinfo;

    /// Store path app.
    static QString m_path;

    /// The XML Rpc Client.
    XmlRpcClient *m_xmlrpc;
};

/**
 * @class DateTime
 *
 * @brief Tablet time and date operations.
 */
class DateTime
{
public:
    /**
     * @brief Print the current date time.
     * @return The current datetime in system.
     */
    static QDateTime currentDateTime() {
        return QDateTime::currentDateTime();
    }

    /**
     * @brief Print the current date.
     * @return The current date in system.
     */
    static QDate currentDate() {
        return QDate::currentDate();
    }

    /**
     * @brief Print the current time.
     * @return The current time in system.
     */
    static QTime currentTime() {
        return QTime::currentTime();
    }

    /**
     * @brief Print the current datetime Format.
     * @return The current datetime format in system.
     */
    static QString currentDateTimeFormat() {
        QDate date = DateTime::currentDate();
        QString dformat;
        dformat.sprintf("%02d/%02d/%04d", date.day(), date.month(), date.year());

        QTime time = DateTime::currentTime();
        QString tformat;
        tformat.sprintf("%.02d:%.02d:%.02d", time.hour(), time.minute(), time.second());

        const QString dok = dformat + " " + tformat;
        return dok;
    }

};

#endif // LOADER_H
